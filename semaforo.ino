#include <Controllino.h>

// Enum para estados 
enum EstadoSem { A_VERDE, A_AMARILLO, B_VERDE, B_AMARILLO };
EstadoSem estado = A_VERDE;

// estructura del semáforo
struct Semaforo {
  int rojo;
  int amarillo;
  int verde;
};

// Semáforo A: tráfico vertical
Semaforo A = {CONTROLLINO_D0, CONTROLLINO_D1, CONTROLLINO_D2};

// Semáforo B: tráfico horizontal
Semaforo B = {CONTROLLINO_D12, CONTROLLINO_D13, CONTROLLINO_D14};

// Temporización
unsigned long tiempoEstado = 0;
const unsigned long DURACION_VERDE = 5000;
const unsigned long DURACION_AMARILLO = 2000;

void setup() {
  // Configurar pines como salidas
  pinMode(A.rojo, OUTPUT);
  pinMode(A.amarillo, OUTPUT);
  pinMode(A.verde, OUTPUT);
  
  pinMode(B.rojo, OUTPUT);
  pinMode(B.amarillo, OUTPUT);
  pinMode(B.verde, OUTPUT);

  // Iniciar en estado A_VERDE
  tiempoEstado = millis();
  actualizarSemaforos();
}

void loop() {
  unsigned long tiempoActual = millis();

  switch (estado) {
    case A_VERDE:
      if (tiempoActual - tiempoEstado >= DURACION_VERDE) {
        estado = A_AMARILLO;
        tiempoEstado = tiempoActual;
        actualizarSemaforos();
      }
      break;

    case A_AMARILLO:
      if (tiempoActual - tiempoEstado >= DURACION_AMARILLO) {
        estado = B_VERDE;
        tiempoEstado = tiempoActual;
        actualizarSemaforos();
      }
      break;

    case B_VERDE:
      if (tiempoActual - tiempoEstado >= DURACION_VERDE) {
        estado = B_AMARILLO;
        tiempoEstado = tiempoActual;
        actualizarSemaforos();
      }
      break;

    case B_AMARILLO:
      if (tiempoActual - tiempoEstado >= DURACION_AMARILLO) {
        estado = A_VERDE;
        tiempoEstado = tiempoActual;
        actualizarSemaforos();
      }
      break;
  }
}

// Actualiza los semáforos según el estado actual
void actualizarSemaforos() {
  switch (estado) {
    case A_VERDE:
      setSemaforo(A, LOW, LOW, HIGH);    // A verde
      setSemaforo(B, HIGH, LOW, LOW);    // B rojo
      break;

    case A_AMARILLO:
      setSemaforo(A, LOW, HIGH, LOW);    // A amarillo
      setSemaforo(B, HIGH, LOW, LOW);    // B rojo
      break;

    case B_VERDE:
      setSemaforo(A, HIGH, LOW, LOW);    // A rojo
      setSemaforo(B, LOW, LOW, HIGH);    // B verde
      break;

    case B_AMARILLO:
      setSemaforo(A, HIGH, LOW, LOW);    // A rojo
      setSemaforo(B, LOW, HIGH, LOW);    // B amarillo
      break;
  }
}

// Enciende el semáforo con los valores dados
void setSemaforo(Semaforo s, bool r, bool a, bool v) {
  digitalWrite(s.rojo, r);
  digitalWrite(s.amarillo, a);
  digitalWrite(s.verde, v);
}
