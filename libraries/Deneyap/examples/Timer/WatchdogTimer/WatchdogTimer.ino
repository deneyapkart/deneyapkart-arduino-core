#include <Arduino.h>
#include "esp_system.h"
#include "rom/ets_sys.h"

// Buton pini
const int button = GPKEY;

// Watchdog süresi: 3000 ms = 3 saniye
const int wdtTimeout = 3000;

// Timer nesnesi
hw_timer_t *timer = NULL;


// Timer süresi dolduğunda çalışacak fonksiyon
void ARDUINO_ISR_ATTR resetModule() {
  ets_printf("Watchdog tetiklendi! Kart yeniden baslatiliyor...\n");
  esp_restart();
}


void setup() {

  Serial.begin(115200);

  Serial.println();
  Serial.println("Program baslatildi");

  // Butonu giriş olarak ayarla
  pinMode(button, INPUT_PULLUP);

  // Timer frekansı: 1 MHz
  // 1 tick = 1 mikrosaniye
  timer = timerBegin(1000000);

  // Timer interrupt fonksiyonunu bağla
  timerAttachInterrupt(timer, &resetModule);

  // 3 saniye sonra interrupt oluştur
  // wdtTimeout = 3000 ms
  // 3000 * 1000 = 3.000.000 mikrosaniye
  timerAlarm(timer, wdtTimeout * 1000, false, 0);

  Serial.println("Watchdog timer hazir.");
}


void loop() {

  Serial.println("Ana dongu calisiyor");

  // Watchdog'u besle
  // Timer sayacını tekrar sıfırla
  timerWrite(timer, 0);

  long loopTime = millis();


  // Butona basılı tutulduğunda
  // program burada bekleyecek.
  // 3 saniyeden uzun tutulursa watchdog devreye girer.
  while (!digitalRead(button)) {

    Serial.println("Butona basiliyor...");

    delay(500);
  }
  delay(1000);


  loopTime = millis() - loopTime;

  Serial.print("Dongu suresi = ");
  Serial.print(loopTime);
  Serial.println(" ms");
}