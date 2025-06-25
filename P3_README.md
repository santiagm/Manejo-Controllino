# Práctica 3 – Diseño de interfaz gráfica para el control de salidas en Controllino

Esta práctica implementa un sistema interactivo donde una matriz de 9 LEDs es controlada mediante botones físicos o entradas en una **pantalla HMI STONE**, utilizando una **máquina de estados finita (FSM)** y lógica no bloqueante en un **Controllino Mega**. Se utilizan estructuras para representar los LEDs, control por interrupciones y comunicación serie para el intercambio de datos entre el PLC y la HMI.

## Objetivos

- Controlar una secuencia de LEDs a través de botones físicos y una pantalla HMI táctil.
- Aplicar una FSM para gestionar distintos modos de operación (espiral normal, espiral inverso, apagado).
- Utilizar `millis()` para implementar temporización no bloqueante.
- Gestionar eventos de la HMI vía UART y realizar acciones en tiempo real en el PLC.

## Requisitos

- Controllino Mega (24 VDC)
- Pantalla táctil HMI STONE STWI o STVC
- Arduino IDE con las librerías:
  - `Controllino.h`
  - `SoftwareSerial.h` (si se usa segundo puerto serial)
- 9 LEDs conectados a salidas digitales
- 3 botones físicos (opcional)
- Fuente de 24 VDC

## Descripción técnica

- Se define una FSM con tres estados (`APAGADO`, `ESPIRAL_NORMAL`, `ESPIRAL_INVERSO`) y un `struct Led` para manejar los pines.
- El sistema permite cambiar de estado a través de:
  - Botones físicos conectados a `I16`, `I17`, `I18`
  - Eventos generados por la HMI STONE (por ejemplo, botones virtuales)
- La pantalla HMI envía comandos por puerto serie (por ejemplo, `"BTN1"`, `"BTN2"`, `"RST"`) al Controllino, que los interpreta y cambia de estado.
- El programa filtra y ejecuta los comandos de la HMI con condiciones tipo `if (mensaje == "BTN1") { ... }`.
- La secuencia se actualiza con `millis()` para evitar el uso de `delay()`.

## Interfaz HMI, descripción:


Agregar un segundo widget tipo SpinBox a la interfaz gráfica. Este segundo SpinBox permitirá
controlar el duty cycle (porcentaje de ciclo de trabajo PWM) del segundo LED conectado al
tablero.

Configurar dos botones físicos en el tablero:
- El primer botón físico controlará el encendido/apagado del primer LED.
- El segundo botón físico controlará el encendido/apagado del segundo LED.

Cada SpinBox deberá estar asociado de manera independiente a su respectivo LED, de forma
que, al mover el SpinBox, se ajuste la intensidad del brillo del LED correspondiente, sin afectar
al otro LED. La acción de los botones físicos debe ser independiente del valor del SpinBox:

- El botón únicamente habilitará o deshabilitará el encendido del LED, pero el brillo será
determinado por el valor actual del SpinBox asociado.

El sistema debe garantizar que, si un LED está apagado por el botón físico, no se active
aunque se modifique el SpinBox correspondiente (hasta que el botón vuelva a presionarse).

### Archivos
- [`semaforo.ino`](./Practica3.ino): Código completo de la máquina de estados y lógica de temporización.
- [`Interfaz_HMI`](./boton_p3): Interfaz gráfica.
