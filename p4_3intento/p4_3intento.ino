// LIBRERIAS
#include <Controllino.h>
#include "Stone_HMI_Define.h"
#include "Procesar_HMI.h"

// VARIABLES PARA MOTOR Y PWM
const int pin_motor = CONTROLLINO_D0;
const int entrada = CONTROLLINO_IN1;

// PULSOS Y RPM
volatile unsigned long conteo_pulsos = 0;
float rpm = 0;
const uint16_t PULSOS_POR_REV = 36;

// HMI
char label2_text[10];  // Voltaje controlador (0-255)
char label4_text[10];  // RPM actual
int rpm_ref = 0;       // Referencia de RPM

// TIEMPO
unsigned long t_previo = 0;

// PID
const float Ts = 0.05; // 50 ms
const float Kp = 0.5;  // AJUSTA ESTOS VALORES SEGÚN TU SISTEMA
const float Ki = 1.0;
const float Kd = 0.01;

float e_prev = 0;
float integral = 0;
float pwm_out = 0;

void contarPulso();

// ----------------- SETUP -----------------
void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  
  pinMode(entrada, INPUT);
  pinMode(pin_motor, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(entrada), contarPulso, FALLING);

  // Configuración del TIMER1 para 50ms
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= B00000100;  // Prescaler 256
  TIMSK1 |= B00000010;  // Habilitar interrupción por comparación A
  OCR1A = 3125;         // 16 MHz / 256 prescaler = 62.5 kHz -> 3125 cuentas = 50ms
  interrupts();

  HMI_init();
  STONE_push_series("line_series", "line_series1", 0);
  STONE_push_series("line_series", "line_series2", 0);
  STONE_push_series("line_series", "line_series3", 0);
  Stone_HMI_Set_Value("slider", "slider1", NULL, 0);
}

// ----------------- LOOP -----------------
void loop() {
  // Leer referencia desde HMI (cada 100 ms)
  if (millis() - t_previo >= 100) {
    t_previo = millis();
    rpm_ref = HMI_get_value("slider", "slider1");

    // Enviar datos al HMI
    dtostrf(rpm_ref, 7, 2, label2_text);
    dtostrf(rpm, 7, 2, label4_text);
    Stone_HMI_Set_Text("label", "label2", label2_text);
    Stone_HMI_Set_Text("label", "label4", label4_text);

    STONE_push_series("line_series", "line_series1", rpm_ref);
    STONE_push_series("line_series", "line_series2", rpm);
    STONE_push_series("line_series", "line_series3", pwm_out* (100.0 / 255.0));
  }
}

// ----------------- ISR TIMER1 -----------------
ISR(TIMER1_COMPA_vect) {
  TCNT1 = 0;

  // Calcular RPM
  //rpm = (float(conteo_pulsos) * 60) / (PULSOS_POR_REV * (1.0 / Ts));
  rpm = (float(conteo_pulsos)*60)*(1.0/Ts) / (PULSOS_POR_REV);

  conteo_pulsos = 0;

  // PID
  float error = rpm_ref - rpm;

  integral += error * Ts;
  float derivative = (error - e_prev) / Ts;
  e_prev = error;

  pwm_out = Kp * error + Ki * integral + Kd * derivative;

  // Limitar salida
  if (pwm_out > 255) {
    pwm_out = 255;
    integral -= error * Ts; // Anti-windup
  } else if (pwm_out < 0) {
    pwm_out = 0;
    integral -= error * Ts; // Anti-windup
  }

  // Aplicar PWM
  analogWrite(pin_motor, (int)pwm_out);

  // Debug opcional
  Serial.print("RPM: ");
  Serial.print(rpm);
  Serial.print(" | Ref: ");
  Serial.print(rpm_ref);
  Serial.print(" | PWM: ");
  Serial.println(pwm_out);
}

// ----------------- ISR PULSO -----------------
void contarPulso() {
  conteo_pulsos++;
}