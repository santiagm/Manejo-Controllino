// Practica 1: Encender todos los LEDs del tablero secuencialmente

#include <Controllino.h> // Se incluye la libreria especifica para usar las salidas del PLC Controllino

// Variables para control de tiempo
unsigned long t_ant = 0;      // Tiempo anterior para control de temporizacion
const long tau = 500;         // Intervalo de tiempo (500 ms) entre encendidos de LEDs

int i = 0;                    // Indice que representa la posicion actual del LED a encender

// Arreglo con los pines de los LEDs que se van a encender en orden secuencial
const int leds[] = {
  CONTROLLINO_D7, CONTROLLINO_D0, CONTROLLINO_D6,
  CONTROLLINO_D12, CONTROLLINO_D13, CONTROLLINO_D14,
  CONTROLLINO_D8, CONTROLLINO_D2, CONTROLLINO_D1,
  CONTROLLINO_D7 // Repite el primero para poder apagarlo al final del ciclo
};

void setup() {
  // Configurar cada pin como salida digital
  pinMode(CONTROLLINO_D0, OUTPUT);
  pinMode(CONTROLLINO_D1, OUTPUT);
  pinMode(CONTROLLINO_D2, OUTPUT);
  pinMode(CONTROLLINO_D6, OUTPUT);
  pinMode(CONTROLLINO_D7, OUTPUT);
  pinMode(CONTROLLINO_D8, OUTPUT);
  pinMode(CONTROLLINO_D12, OUTPUT);
  pinMode(CONTROLLINO_D13, OUTPUT);
  pinMode(CONTROLLINO_D14, OUTPUT);
}

void loop() {
  // Se obtiene el tiempo actual en milisegundos
  unsigned long t_act = millis();

  // Se evalua si ha pasado el intervalo definido (tau)
  if (t_act - t_ant >= tau) {
    t_ant = t_act; // Se actualiza el tiempo anterior

    // Apagar el LED anterior
    digitalWrite(leds[i], LOW);

    // Encender el siguiente LED
    digitalWrite(leds[i+1], HIGH);

    // Avanzar al siguiente indice del arreglo
    i = i + 1;
  }

  // Si se ha llegado al final de la secuencia, reiniciar el indice
  if (i == 9){
    i = 0;
  }
}