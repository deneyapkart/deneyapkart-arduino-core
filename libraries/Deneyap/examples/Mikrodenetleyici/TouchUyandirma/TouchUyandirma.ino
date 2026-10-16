/*
 *  TouchUyandırma örneği,
 *  Deep Sleep Touch ile uyandırma
 *  ====================================================
 *  Bu kod, derin uykunun nasıl kullanılacağını gösterir. Uyandırma kaynağı touch.
 *  Karttaki touch pinlerinden birine dokunulduğunda resetlenerek ön yükleme yapılır.
 *  İşlemleri kaç defa yapıldığı seri port ekranına yazdırılmaktadır. 
 *  Deneyap Kart G touch pinleri bulunmamaktadır. 
*/
#if CONFIG_IDF_TARGET_ESP32
#define Threshold 40   /* Değer arttıkça hassasiyet artar */
#else
#define Threshold 5000 /* ESP32-S2/S3: değer azaldıkça hassasiyet artar */
#endif

RTC_DATA_ATTR int bootCount = 0;
/*
ESP32'nin nedenini yazdırma yöntemi
uykudan uyandı
*/
void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("RTC_IO kullanan harici sinyalin neden olduğu uyandırma"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("RTC_CNTL kullanan harici sinyalin neden olduğu uyandırma"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Timer'ın neden olduğu uyandırma"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Touchpad'ın neden olduğu uyandırma"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("ULP programının neden olduğu uyandırma"); break;
    default : Serial.printf("Uyanma deepsleepten kaynaklanmadı: %d\n",wakeup_reason); break;
  }
}
void setup(){
  Serial.begin(115200);
  delay(1000); 

  // Önyükleme numarasını artır ve her yeniden başlatmada yazdır
  ++bootCount;
  Serial.println("Önyükleme sayısı: " + String(bootCount));

  // Uyandırma nedenini yazdır
  print_wakeup_reason();

  // T2 touch pinini uyandırma kaynağı olarak yapılandır
  touchSleepWakeUpEnable(T2, Threshold);

  Serial.println("Uyku modu başlıyor");
  esp_deep_sleep_start();
}

void loop(){
}
