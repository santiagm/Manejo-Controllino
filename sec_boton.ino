#include <Controllino.h>

// ====== ENUMERACIÓN DE ESTADOS =======
enum EstadoSistema { APAGADO, ESPIRAL_NORMAL, ESPIRAL_INVERSO };
EstadoSistema estadoActual = APAGADO;

// ====== STRUCT PARA LEDS ============
struct Led {
  int pin;
  bool estado;
};

// ====== MATRIZ DE LEDS ===============
Led matriz[9] = {
  {CONTROLLINO_D0, false}, {CONTROLLINO_D6, false}, {CONTROLLINO_D12, false},
  {CONTROLLINO_D13, false}, {CONTROLLINO_D14, false}, {CONTROLLINO_D8, false},
  {CONTROLLINO_D2, false}, {CONTROLLINO_D1, false}, {CONTROLLINO_D7, false}
};

// ====== BOTONES ======================
const int BTN_ESPIRAL_NORMAL = CONTROLLINO_I16;
const int BTN_ESPIRAL_INVERSO = CONTROLLINO_I17;
const int BTN_RESET = CONTROLLINO_I18;

// ====== VARIABLES DE TIEMPO =========
unsigned long tiempoAnterior = 0;
const unsigned long intervalo = 250;  // milisegundos
int indice = 0;

void setup() {
  // Configurar pines de LEDs como salidas
  for (int i = 0; i < 9; i++) {
    pinMode(matriz[i].pin, OUTPUT);
    digitalWrite(matriz[i].pin, LOW);
  }

  // Configurar botones como entradas
  pinMode(BTN_ESPIRAL_NORMAL, INPUT);
  pinMode(BTN_ESPIRAL_INVERSO, INPUT);
  pinMode(BTN_RESET, INPUT);
}

void loop() {
  leerBotones();
  actualizarPatron();
}

// ====== LECTURA DE BOTONES ==========
void leerBotones() {
  if (digitalRead(BTN_ESPIRAL_NORMAL) == HIGH) {
    estadoActual = ESPIRAL_NORMAL;
    indice = 0;
    apagarTodos();
  } 
  else if (digitalRead(BTN_ESPIRAL_INVERSO) == HIGH) {
    estadoActual = ESPIRAL_INVERSO;
    indice = 9;
    apagarTodos();
  } 
  else if (digitalRead(BTN_RESET) == HIGH) {
    estadoActual = APAGADO;
    apagarTodos();
  }
}

// ====== ACTUALIZACIÓN NO BLOQUEANTE ======
void actualizarPatron() {
  unsigned long tiempoActual = millis();
  if (tiempoActual - tiempoAnterior < intervalo) return;
  tiempoAnterior = tiempoActual;

  if (estadoActual == ESPIRAL_NORMAL) {
    // Apaga el LED anterior (si índice=0, apaga el 8)
    if (indice > 0) apagarLed(indice - 1);
    else           apagarLed(8);

    // Enciende el actual
    encenderLed(indice);

    // Avanza índice: si <8 sube, si =8 vuelve a 0
    if (indice < 8) indice++;
    else            indice = 0;
  }
  else if (estadoActual == ESPIRAL_INVERSO) {
    // Apaga el “siguiente” en la espiral inversa
    if (indice < 8) apagarLed(indice + 1);
    else            apagarLed(0);

    // Enciende el actual
    encenderLed(indice);

    // Retrocede índice: si >0 baja, si =0 va a 8
    if (indice > 0) indice--;
    else            indice = 8;
  }
}


// ====== ENCENDER LED INDIVIDUAL ======
void encenderLed(int indice) {
  matriz[indice].estado = true;
  digitalWrite(matriz[indice].pin, HIGH);
}

// ====== APAGAR LED INDIVIDUAL ======
void apagarLed(int indice) {
  matriz[indice].estado = false;
  digitalWrite(matriz[indice].pin, LOW);
}

// ====== APAGAR TODOS LOS LEDS ========
void apagarTodos() {
  for (int i = 0; i < 9; i++) {
    matriz[i].estado = false;
    digitalWrite(matriz[i].pin, LOW);
  }
}
