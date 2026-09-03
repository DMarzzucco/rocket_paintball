
Para lograr esto de forma segura y económica, usaremos 4 cables conectados a pines digitales de Arduino en modo INPUT_PULLUP. Al desconectarlos (cortarlos o desenchufarlos), el pin pasará de detectar un estado BAJO (LOW) a un estado ALTO (HIGH).
------------------------------
## Esquema de Conexión

* Cable 1: Del pin Digital 2 a GND.
* Cable 2: Del pin Digital 3 a GND.
* Cable 3: Del pin Digital 4 a GND.
* Cable 4: Del pin Digital 5 a GND.
* Zumbador (Buzzer): Del pin Digital 8 a GND (a través de una resistencia de 220 ohmios).

------------------------------
## Código Base 
Este código evalúa constantemente el orden de desconexión. Si el jugador se equivoca de cable o desconecta varios al mismo tiempo, la bomba explota de inmediato.

```cpp
// Configuración de Pines para los 4 cablesconst int pinCable[] = {2, 3, 4, 5}; 
// EL PATRÓN CORRECTO: Define aquí el orden de los pines que deben desconectarse.// Por ejemplo, el orden de pines: 4, 2, 5, y al final el 3.const int patronCorrecto[] = {4, 2, 5, 3}; 
const int pinBuzzer = 8;int progreso = 0; // Lleva la cuenta de cuántos cables correctos se han retiradobool juegoActivo = true;
// Estado previo de los cables (true = conectado, false = desconectado)bool estadoAnterior[] = {true, true, true, true}; 
void setup() {
  Serial.begin(9600);
  pinMode(pinBuzzer, OUTPUT);
  
  // Configurar pines de cables con resistencia pull-up interna
  for (int i = 0; i < 4; i++) {
    pinMode(pinCable[i], INPUT_PULLUP);
  }
  
  Serial.println("Bomba activada. Desconecta los cables en el orden correcto...");
}
void loop() {
  if (!juegoActivo) return;

  int cablesDesconectadosSimultaneamente = 0;
  int cableDetectado = -1;

  // 1. Escanear el estado de todos los cables
  for (int i = 0; i < 4; i++) {
    // INPUT_PULLUP lee HIGH cuando el cable se desconecta de GND
    bool estadoActual = (digitalRead(pinCable[i]) == HIGH); 

    // Detectar si el cable cambió de conectado a desconectado en este instante
    if (estadoActual && estadoAnterior[i]) {
      cablesDesconectadosSimultaneamente++;
      cableDetectado = pinCable[i]; // Guarda el pin físico del cable desconectado
      estadoAnterior[i] = false;   // Actualiza el estado para no volver a contarlo
    }
  }

  // 2. Evaluar las acciones del jugador
  if (cablesDesconectadosSimultaneamente > 0) {
    
    // CASO DE ERROR 1: Desconectar más de un cable al mismo tiempo
    if (cablesDesconectadosSimultaneamente > 1) {
      detonarBomba("¡Trampa! Desconectaste varios cables a la vez.");
      return;
    }

    // CASO DE EVALUACIÓN: Se desconectó un solo cable de forma limpia
    if (cableDetectado == patronCorrecto[progreso]) {
      progreso++;
      Serial.print("Cable correcto retirado. Progreso: ");
      Serial.concat(progreso, "/4\n");
      tonalidadAcierto();

      // VICTORIA: Si completó los 4 pasos del patrón con éxito
      if (progreso == 4) {
        desactivarBomba();
      }
    } 
    // CASO DE ERROR 2: Se desconectó el cable equivocado según el patrón
    else {
      detonarBomba("¡Orden incorrecto!");
    }
  }
  
  delay(50); // Pequeña pausa anti-rebote
}
// --- FUNCIONES DE EFECTOS DE SONIDO Y ESTADOS ---
void tonalidadAcierto() {
  tone(pinBuzzer, 1500, 150);
}
void desactivarBomba() {
  juegoActivo = false;
  Serial.println("¡BOMBA DESACTIVADA! Felicidades.");
  // Sonido de victoria
  for(int i = 0; i < 3; i++) {
    tone(pinBuzzer, 2000, 100); delay(150);
    tone(pinBuzzer, 2500, 100); delay(150);
  }
}
void detonarBomba(String motivo) {
  juegoActivo = false;
  Serial.print("BOOM!!! Bomba detonada. Motivo: ");
  Serial.println(motivo);
  // Sonido de explosión continuo
  tone(pinBuzzer, 150, 2000); 
}
```

------------------------------
## Cómo funciona la lógica anti-trampas

* Detección simultánea: El bucle for revisa los 4 pines en microsegundos. Si el código detecta que la variable cablesDesconectadosSimultaneamente es mayor a 1, asumirá que se soltaron juntos o se cortó una faja completa y activará la detonación inmediata.
* Validación de secuencia: El arreglo patronCorrecto guarda los pines en la secuencia exacta que exiges. Si el jugador retira un cable fuera de su turno, el sistema lo detecta como un fallo y explota.
