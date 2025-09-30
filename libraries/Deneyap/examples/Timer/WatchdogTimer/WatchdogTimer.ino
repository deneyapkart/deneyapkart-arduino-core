/*
 *   WatcgdogTimer örneği, 
 * 
*/
#include <esp_task_wdt.h>

const int wdtTimeout = 3;

#ifndef CORE_DK_VERSION
  #define CORE_DK_VERSION 0
#endif


void setup() {
  Serial.begin(115200);
  pinMode(GPKEY, INPUT);

  #if CORE_DK_VERSION > 103013
    esp_task_wdt_config_t wdt_config = {
      .timeout_ms = wdtTimeout * 1000,
      .idle_core_mask = 0x1,
      .trigger_panic = true
    };
    esp_task_wdt_init(&wdt_config);
    esp_task_wdt_add(NULL);
  #else
    esp_task_wdt_init(wdtTimeout, true);
    esp_task_wdt_add(NULL);
  #endif
}

void loop() {
  Serial.println("Döngüde");
  long loopTime = millis();

  esp_task_wdt_reset();

  while (!digitalRead(GPKEY)) {
    Serial.println("Butona basıldı");
    delay(500);
  }
  delay(1000);

  loopTime = millis() - loopTime;
  Serial.print("Döngü süresi = ");
  Serial.println(loopTime);
}
