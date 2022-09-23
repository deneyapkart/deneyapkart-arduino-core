/*
 *   UltrasonikMesafeörneği,
 *   Ultrasonik mesafe sensörü ile mesafe ölçülmektedir. Ölçülen mesafe seri port ekrane yazdırılmaktadır. 
 *    
 */
#include "hcsr04ESP32.h"

#define trigPin D0
#define echoPin D1

UltraSonicDistanceSensor distanceSensor(trigPin, echoPin);  // Ultrasonik sensor pin konfigurasyonu

void setup () {
  Serial.begin(115200);                                     // Seri haberleme baslatildi
}

void loop () {
  Serial.println(distanceSensor.measureDistanceCm());       // Ultrasonik olcum yapiliyor ve seri port ekrane veri gonderiliyor
  delay(500);
}
