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
touch_pad_t touchPin;
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
/*
ESP32'nin kullandığı touchpad yazdırma yöntemi
uykudan uyandı
*/
void print_wakeup_touchpad(){
  touchPin = (touch_pad_t)esp_sleep_get_touchpad_wakeup_status();
#if CONFIG_IDF_TARGET_ESP32

  switch(touchPin)
  {
    case 0  : Serial.println("GPIO 4'te dokunma algılandı"); break;
    case 1  : Serial.println("GPIO 0'te dokunma algılandı"); break;
    case 2  : Serial.println("GPIO 2'te dokunma algılandı"); break;
    case 3  : Serial.println("GPIO 15'te dokunma algılandı"); break;
    case 4  : Serial.println("GPIO 13'te dokunma algılandı"); break;
    case 5  : Serial.println("GPIO 12'te dokunma algılandı"); break;
    case 6  : Serial.println("GPIO 14'te dokunma algılandı"); break;
    case 7  : Serial.println("GPIO 27'te dokunma algılandı"); break;
    case 8  : Serial.println("GPIO 33'te dokunma algılandı"); break;
    case 9  : Serial.println("GPIO 32'te dokunma algılandı"); break;
    default : Serial.println("Touchpad değil uyandırma"); break;
  }
#else
  if (touchPin < TOUCH_PAD_MAX) {
    Serial.printf("GPIO %d'te dokunma algılandı\n", touchPin);
  } else {
    Serial.println("Touchpad değil uyandırma");
  }
#endif
}

void setup(){
  Serial.begin(115200);
  delay(1000); 

  // Önyükleme numarasını artır ve her yeniden başlatmada yazdır
  ++bootCount;
  Serial.println("Önyükleme sayısı: " + String(bootCount));

  //ESP32 ve touchpad uyandırma nedenini de yazdırın
  print_wakeup_reason();
  print_wakeup_touchpad();

  // T2 touch pinini uyandırma kaynağı olarak yapılandır
  touchSleepWakeUpEnable(T2, Threshold);

  Serial.println("Uyku modu başlıyor");
  esp_deep_sleep_start();
}

void loop(){
}
