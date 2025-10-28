#include <BleGamepad.h>

BleGamepad bleGamepad("Mini ETS2 Wheel", "ESP32", 100);
const int potPin = 34;
int potValue = 0;

void setup() {
  Serial.begin(115200);
  bleGamepad.begin();  
} 

void loop() {
  if(bleGamepad.isConnected()){
    potValue = analogRead(potPin);
    int steering = map(potValue, 0, 4096, 0, 32767);
    // Serial.println(steering);
    bleGamepad.setAxes(steering, 16384, 0, 0, 0, 0);
  }
  delay(10);
}
