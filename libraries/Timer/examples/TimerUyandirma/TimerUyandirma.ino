/*
Timer ile Deep Sleep uyandırma 
====================================
ESP32, etkili güç için Deep Sleep modu sunar
güç olarak tasarruf, IoT uygulamaları için önemli bir faktördür
Bu modda CPU'lar, RAM'in çoğu ve saatli tüm dijital çevre birimleri 
APB_CLK'ten gelenler kapatılır. 
Çipin hala açılabilen parçalar: RTC denetleyicisi, RTC çevre birimleri ve RTC bellekleri

Bu kod, Timer ile en temel Deep Sleep uyandırma örnek uygulaması
yeniden başlatmalarda kullanmak için verilerin 
RTC belleğinde nasıl saklanacağını görüntüler.
*/

#define uS_TO_S_FACTOR 1000000ULL   /* Mikro saniyeyi saniyeye çevirme faktörü */
#define TIME_TO_SLEEP  10           /* ESP32'nin uyku moduna geçeceği süre (saniye cinsinden) */

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

  // ESP32 için uyandırma nedenini yazdır
  print_wakeup_reason();

/*
   İlk önce uyandırma kaynağını yapılandırıyoruz
   ESP32'mizi her 10 saniyede bir uyanacak şekilde ayarladık
   */
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("ESP32'yi her uyku için ayarlayın " + String(TIME_TO_SLEEP) +
  " Saniye");

/*
   Ardından, hangi çevre birimlerinin kapatılacağına/tutulacağına karar veriyoruz
   Varsayılan olarak, ESP32 çevre birimlerini otomatik olarak kapatır
   uyandırma kaynağı tarafından gerekli değildir, ancak güçlü bir kullanıcı olmak istiyorsanız
   Bu sizin için. API belgelerinde ayrıntılı olarak okuyun
   http://esp-idf.readthedocs.io/en/latest/api-reference/system/deep_sleep.html
   Çevre birimlerinin nasıl yapılandırılacağına dair bir örnek olarak yorum satırı bıraktı.
   Aşağıdaki satır, derin uykuda tüm RTC çevre birimlerini kapatır.
   */
  //esp_deep_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_OFF);
  //Serial.println("Tüm RTC Çevre Birimlerinin uyku modunda kapatılacak şekilde yapılandırılması");
  

/*
   Artık bir uyandırma nedeni ayarladık ve gerekirse
   derin uykuda çevre birimleri durumu, şimdi gitmeye başlayabiliriz
   derin uyku.
   Uyandırma kaynaklarının sağlanmaması, ancak derin
   uyku başlatıldı, donanım olmadığı sürece sonsuza kadar uyuyacak
   sıfırlama gerçekleşir.
   */
  Serial.println("Uyku modu başlıyor");
  Serial.flush(); 
  esp_deep_sleep_start();
}

void loop(){

}
