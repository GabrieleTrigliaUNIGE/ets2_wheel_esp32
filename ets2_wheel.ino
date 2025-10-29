#include <BleGamepad.h>

BleGamepad bleGamepad("Mini ETS2 Wheel", "ESP32", 100);

// CONFIGURAZIONE PIN
const int potPin = 34;     // Pin collegato al potenziometro
const int numReadings = 8; // Numero di campioni per filtro

// VARIABILI FILTRO
int readings[numReadings];
int readIndex = 0;
long total = 0;
int average = 0;

// CALIBRAZIONE E SCALA
int centerValue = 0;  // centro automatico
int minValue = 0;   // valore minimo reale del pot
int maxValue = 4096;  // valore massimo reale del pot

void setup() {
  Serial.begin(115200);
  bleGamepad.begin();

  // Inizializza il buffer del filtro
  for (int i = 0; i < numReadings; i++) readings[i] = 0;

  delay(1000); // stabilizza tensione
  centerValue = analogRead(potPin);
  Serial.print("Centro iniziale: ");
  Serial.println(centerValue);
}

void loop() {
  // FILTRO MEDIA MOBILE
  total -= readings[readIndex];
  readings[readIndex] = analogRead(potPin);
  total += readings[readIndex];
  readIndex = (readIndex + 1) % numReadings;
  average = total / numReadings;

  // LIMITA AI VALORI REALI DEL POTENZIOMETRO
  // average = constrain(average, minValue, maxValue);

  // MAPPATURA LINEARE
  int steering = map(average, minValue, maxValue, 0, 32767);

  // INVIA L’ASSE X (STERZO), MANTENENDO GLI ALTRI CENTRATI
  if (bleGamepad.isConnected()) {
    bleGamepad.setAxes(steering, 16784, 0, 0, 0, 0);
  }

  delay(10);
}
