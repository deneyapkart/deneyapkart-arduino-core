/*
 *   WatcgdogTimer örneği, 
 * 
*/
#include "esp_system.h"

const int wdtTimeout = 3000;  //watchdog'u tetiklemek için ms cinsinden süre
hw_timer_t *timer = NULL;

void ARDUINO_ISR_ATTR resetModule() {
  ets_printf("reboot\n");
  esp_restart();
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Setup konfigürasyon");

  //Buton gecikmeyi tetiklemek için kullanılacak
  pinMode(GPKEY, INPUT);                            // Genel amacli buton pini giris olarak ayarlandi. 
  
  timer = timerBegin(0, 80, true);                  //timer 0, div 80
  timerAttachInterrupt(timer, &resetModule, true);  //callback ekle
  timerAlarmWrite(timer, wdtTimeout * 1000, false); //zamanı ayarla
  timerAlarmEnable(timer);                          //interrupt etkinleştir
}

void loop() {
  Serial.println("Döngüde");

  timerWrite(timer, 0); //timer sıfırla (watchdog besleme)
  long loopTime = millis();
  //düğmeye basılıyken, Timer'ı tetiklemek için 3 saniyeye kadar gecikme
  while (!digitalRead(GPKEY)) {
    Serial.println("Butona basıldı");
    delay(500);
  }
  delay(1000); //simule et 
  loopTime = millis() - loopTime;
  
  Serial.print("Döngü süresi = ");
  Serial.println(loopTime); //3000 ms'in altında olmalı
}
