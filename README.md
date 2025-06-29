# Prácticas de Control Digital con Controllino Mega

Este repositorio agrupa las prácticas desarrolladas en el curso de **Control Digital**, utilizando el PLC industrial **Controllino Mega** y el entorno **Arduino IDE**. Cada práctica aborda un caso distinto de automatización mediante salidas digitales, temporización no bloqueante y máquinas de estados finitas (FSM).

## ¿Qué es el Controllino?

El **Controllino** es un PLC programable compatible con Arduino, diseñado para aplicaciones industriales. Combina la flexibilidad del desarrollo en C++ con entradas y salidas digitales/analógicas típicas de la automatización. En este proyecto se utiliza el modelo **Controllino Mega**, que trabaja a 24 VDC y ofrece múltiples puertos de expansión.

---

## Prácticas incluidas

### Práctica 1 – Secuencia de LEDs
Se implementa una secuencia automática de encendido de 9 LEDs. La lógica se basa en un ciclo controlado por temporización no bloqueante (`millis()`), encendiendo un LED a la vez en forma secuencial.

🔗 [`Ver README`](./P1_README.md)

---

### Práctica 2 – Control de semáforo con FSM
Se simula un cruce de dos vías con semáforos, alternando entre 4 estados (`A_VERDE`, `A_AMARILLO`, `B_VERDE`, `B_AMARILLO`). Se emplea una máquina de estados finita y temporización no bloqueante para alternar entre luces con lógica segura.

🔗 [`Ver README`](./P2_README.md)

---

### Práctica 3 – Secuencia controlada por botones
Una matriz de 9 LEDs es controlada por botones físicos. Dependiendo del botón presionado, se activa una secuencia en espiral normal o inversa. Se utiliza FSM para el cambio de estados y se gestiona con `millis()`.

🔗 [`Ver README`](./P3_README.md)

---

### Práctica 4 – Secuencia controlada por botones
El usuario regula la intensidad (duty cycle PWM) mediante un slider en la HMI, y el sistema mide y muestra la velocidad actual en revoluciones por minuto (RPM) a través de conteo de pulsos de un motor DC.

🔗 [`Ver README`](./P4_README.md)

---

### Informe
Las decripciones descripciones y resultados obtenidos se muestra en: [`P4_1_conDig.pdf`](./P4_1_conDig.pdf)

---

## Autores

E. Bermeo & S. Guillén – Estudiantes de Ingeniería en Telecomunicaciones  
Universidad De Cuenca – Junio 2025
