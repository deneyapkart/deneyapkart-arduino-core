/*
 *   UltrasonikMesafeörneği,
 *   Ultrasonik mesafe sensörü ile mesafe ölçülmektedir. Ölçülen mesafe seri port ekrane yazdırılmaktadır.
 *
 *  ==============================================================================
 *    Bu uygulama örneği için "HCSR04 by Martin Sosic" kütüphanesi indirilmelidir.  ->https://github.com/Martinsos/arduino-lib-hc-sr04<-
 *    Bu uygulama örneği HCSR04 kütüphanesi 2.0.0 versiyonu ile yazılmıştır.
 *  ==============================================================================
*/
#include <HCSR04.h>

#define trigPin D0
#define echoPin D1

UltraSonicDistanceSensor distanceSensor(trigPin, echoPin);  // Ultrasonik sensor pin konfigurasyonu

void setup() {
  Serial.begin(115200);  // Seri haberleme baslatildi
}

void loop() {
  Serial.println(distanceSensor.measureDistanceCm());  // Ultrasonik olcum yapiliyor ve seri port ekrane veri gonderiliyor
  delay(500);
}
