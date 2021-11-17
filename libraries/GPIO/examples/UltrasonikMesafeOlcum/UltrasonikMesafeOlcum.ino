#include "hcsr04ESP32.h"

#define trigPin D0
#define echoPin D1

UltraSonicDistanceSensor distanceSensor(trigPin, echoPin);  // Ultrasonik sensor pin konfigurasyonu

void setup () {
  Serial.begin(115200);                                     // Seri haberleme baslatildi
}

void loop () {
  Serial.println(distanceSensor.measureDistanceCm());       // Ultrasonik olcum yapiliyor ve seri terminale veri gonderiliyor
  delay(500);
}
