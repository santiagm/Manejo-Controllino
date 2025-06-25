#include <Controllino.h>
#include "Stone_HMI_Define.h"
#include "Procesar_HMI.h"

const int led = CONTROLLINO_D0;         // Salida digital D0 
const int ledpractica = CONTROLLINO_D2; // Led D2 de la practica (reto)

const int botonRojo = CONTROLLINO_I16;  // Boton para led D0
const int botonVerde = CONTROLLINO_I18; // Boton para led D2

int       bandera          = 0;         // bandera para no repetir el mensaje de ingresar un valor al HMI
int       pwmValue         = 0;         // valor convertido (0-255)
int       pwmValue2        = 0;

// Estados para los botones 
bool estadoLED1 = false;
bool estadoLED2 = false;

bool boton1Prev = HIGH;
bool boton2Prev = HIGH;

// Valor en porcentaje (0-100)
float dutyCyclePercent = 0;             
float dutyCyclePercent2 = 0;


void setup() {
  Serial.begin(115200);                 // Comunicación serial con el PC
  Serial2.begin(115200);                // Comunicación serial con el HMI

  // Leds de salida
  pinMode(led, OUTPUT);
  pinMode(ledpractica, OUTPUT);

  // Botones
  pinMode(botonRojo, INPUT);
  pinMode(botonVerde, INPUT);

  HMI_init();                           // Inicializa el sistema de colas para las respuestas el HMI
  Stone_HMI_Set_Value("spin_box", "spin_box1", NULL, 0);  // Pone en 0 el valor del spin box en el HMI.
  Stone_HMI_Set_Value("spin_box", "spin_box2", NULL, 0);  // Pone en 0 el valor del spin box en el HMI (reto). 
}

void loop() {
  dutyCyclePercent = HMI_get_value("spin_box", "spin_box1");  // Obtiene el valor del spin_box1
  dutyCyclePercent2 = HMI_get_value("spin_box", "spin_box2"); // Obtiene el valor del spin_box2

  // Leer botón 1 para led D0 - rojo
  bool boton1 = digitalRead(botonRojo);
  if (boton1 == LOW && boton1Prev == HIGH) {  // Transición de HIGH a LOW
    estadoLED1 = !estadoLED1;  // Cambia el estado del LED
  }
  boton1Prev = boton1;

  // Leer botón 2 para led D2 - verde
  bool boton2 = digitalRead(botonVerde);
  if (boton2 == LOW && boton2Prev == HIGH) {
    estadoLED2 = !estadoLED2;
  }
  boton2Prev = boton2;

  // LED 1 PWM
  if (estadoLED1 && dutyCyclePercent >= 0 && dutyCyclePercent <= 100) {
    pwmValue = map(dutyCyclePercent, 0, 100, 0, 255);      // Mapea el valor de duty cycle en porcentaje a valores de 0 a 255
    analogWrite(led, pwmValue);
    Serial.print("Duty cycle 1 (%): ");
    Serial.print(dutyCyclePercent);
    Serial.print(" -> PWM value: ");
    Serial.println(pwmValue);
    int bandera = 0;
  }
  else if (bandera == 0){
    int bandera = 1;
    Serial.println("Ingresa un valor entre 0 y 100 para led1.");
    analogWrite(led, 0);
  }

  // LED 2 PWM
  if (estadoLED2 && dutyCyclePercent2 >= 0 && dutyCyclePercent2 <= 100) {
    pwmValue2 = map(dutyCyclePercent2, 0, 100, 0, 255);      // Mapea el valor de duty cycle en porcentaje a valores de 0 a 255
    analogWrite(ledpractica, pwmValue2);
    Serial.print("Duty cycle 2 (%): ");
    Serial.print(dutyCyclePercent2);
    Serial.print(" -> PWM value: ");
    Serial.println(pwmValue2);
    Serial.println("----------------------");
    int bandera = 0;
  }
  else if (bandera == 0){
    int bandera = 1;
    Serial.println("Ingresa un valor entre 0 y 100 para led2.");
    analogWrite(ledpractica, 0);
  }
}

