/* 
 *   MagnetikOkumaZamani örneği, 
 *   MagnetikOkumaZamani uygulamasında RTC modülü kullanılmıştır. 
 *    
 *   Bu örnekte Deneyap Kart ve Deneyap Kart 1A kartlarındaki mikrodenetleyiye yaklaştırılan mıknatıs belirlenen değer üstünde mıknatıs değeri okuyunca alınan veriler
 *   seri port ekranına "Magnetik Algılandı: xx:xx xx:xx:xxxx ....." yazdırmaktadır.  
 *   
 *   Bu örnek uygulama diğer Deneyap Geliştirme Kartları kullanılırsa harici magnetik alan sensörü bağlanılmalı ve kodda gerekli değişiklikler yapılmalıdır.   
 *
 *  ==============================================================================
 *    Bu uygulama örneği için "RTClib by Adafruit" kütüphanesi indirilmelidir.  ->https://github.com/adafruit/RTClib<-
 *    Bu uygulama örneği RTClib kütüphanesi 2.0.2 versiyonu ile yazılmıştır.
 *  ==============================================================================
*/
#include <RTClib.h>

RTC_DS3231 rtc;  //RTC icin Class tanimlamasi
char daysOfTheWeek[7][12] = { "Pazar", "Pazartesi", "Sali", "Carsamba", "Persembe", "Cuma", "Cumartesi" };

int MagnetikDegeri = 0;

void setup() {
  Serial.begin(115200);

  rtc.begin();
  //rtc.adjust(DateTime(__DATE__, __TIME__));    //Şimdiki tarih ve zamanı otomatik ayarlanması için bu fonksiyon kullanılmalıdır
  rtc.adjust(DateTime(2015, 3, 3, 14, 27, 0));  //Tarih ve zamanı manuel ayarlanması istiyorsa bu fonksiyon kullanılmalıdır
}

void loop() {
  MagnetikDegeri = hallRead();                             //Magnetik okuma yapıldı
  Serial.printf("\nMagnetik Değeri: %d", MagnetikDegeri);  //MagnetikDegeri seri port ekrane yazıldı
  Serial.println();

  if (MagnetikDegeri > 100) {  //değeri size uygun farklı bir değer değiştirilebilir
    DateTime now = rtc.now();

    /*Magnetik Algılandı: saat:dakika:saniye gün:ay:yıl haftanın günü 
    seri port ekrane yazıldı*/
    Serial.print("Magnetik Algılandı: ");
    Serial.print(now.hour(), DEC);
    Serial.print(":");
    Serial.print(now.minute(), DEC);
    Serial.print(":");
    Serial.print(now.second(), DEC);
    Serial.print("  ");
    Serial.print(now.day(), DEC);
    Serial.print("-");
    Serial.print(now.month(), DEC);
    Serial.print("-");
    Serial.print(now.year(), DEC);
    Serial.print("  ");
    Serial.println(daysOfTheWeek[now.dayOfTheWeek()]);

    delay(5000);
  }
  delay(100);
}
