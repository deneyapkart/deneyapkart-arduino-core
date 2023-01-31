/* 
 *   SDmaynetikOkumaZamani örneği, 
 *   SDmaynetikOkumaZamani uygulamasında RTC ve SD Kart modülleri kullanılmıştır. 
 *   
 *   Bu örnekte Deneyap Kart ve Deneyap Kart 1A dahili manyetik alan sensöründen alınan maynetik alan verileri seri port ekranına yazdırmaktadır. 
 *   Alınan bu veriler aynı zamanda SD karttaki YeniDosya.txt içine "Magnetik Algılandı: xx:xx xx:xx:xxxx ....." yazdırmaktadır.
 *   Bu örnek uygulama diğer Deneyap Geliştirme Kartları kullanılırsa harici magnetik alan sensörü bağlanılmalı ve kodda gerekli değişiklikler yapılmalıdır.   
 *
 *  ==============================================================================
 *    Bu uygulama örneği için "RTClib by Adafruit" kütüphanesi indirilmelidir.  ->https://github.com/adafruit/RTClib<-
 *    Bu uygulama örneği RTClib kütüphanesi 2.0.2 versiyonu ile yazılmıştır.
 *  ==============================================================================
*/
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "Wire.h"
#include <RTClib.h>

RTC_DS3231 rtc;  //RTC icin Class tanimlamasi
char daysOfTheWeek[7][12] = { "Pazar", "Pazartesi", "Sali", "Carsamba", "Persembe", "Cuma", "Cumartesi" };

int MagnetikDegeri = 0;

/*Dosya yazma fonksiyonu */
void writeFile(fs::FS &fs, const char *path, const char *message) {
  Serial.printf("Dosya yaziliyor: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Yazma islemi icin dosya acilamadi");
    return;
  }
  if (file.print(message)) {
    Serial.println("Dosya yazildi");
  } else {
    Serial.println("Dosya yazma islemi basarisiz");
  }
  file.close();
}

/*Dosyaya ekleme yapma fonksiyonu */
void appendFile(fs::FS &fs, const char *path, const char *message) {
  Serial.printf("Dosyaya eklendi: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if (!file) {
    Serial.println("Ekleme islemi icin dosya acilamadi");
    return;
  }
  if (file.print(message)) {
    Serial.println("Ekleme islemi basarili");
  } else {
    Serial.println("Ekleme islemi basarisiz");
  }
  file.close();
}

void setup() {
  Serial.begin(115200);

  rtc.begin();
  rtc.adjust(DateTime(__DATE__, __TIME__));  //Şimdiki tarih ve zamanı otomatik ayarlanması için bu fonksiyon kullanılmalıdır
  //rtc.adjust(DateTime(2015, 3, 3, 14, 27, 0));   //Tarih ve zamanı manuel ayarlanması istiyorsa bu fonksiyon kullanılmalıdır

  if (!SD.begin()) {
    Serial.println("Kart okuma basarisiz");
    return;
  }
  writeFile(SD, "/YeniDosya.txt", "Magnetik ne zaman algılandı ? \r\n");  //YeniDosya.txt uzantılı dosya oluşturuldu.
}

void loop() {
  MagnetikDegeri = hallRead();                             //Magnetik okuma yapıldı
  Serial.printf("\nMagnetik Değeri: %d", MagnetikDegeri);  //MagnetikDegeri seri port ekrane yazıldı

  if (MagnetikDegeri > 100) {  //değer değiştirilebilir
    String dataString = "";

    /*Magnetik Algılandı: saat:dakika:saniye gün:ay:yıl haftanın günü 
    YeniDosya.txt dosyasına yazıldı*/
    DateTime now = rtc.now();

    dataString += "Magnetik Algılandı: ";
    dataString += String(now.hour());
    dataString += ":";
    dataString += String(now.minute());
    dataString += ":";
    dataString += String(now.second());
    dataString += "  ";
    dataString += String(now.day());
    dataString += ":";
    dataString += String(now.month());
    dataString += ":";
    dataString += String(now.year());
    dataString += " ";
    dataString += String(daysOfTheWeek[now.dayOfTheWeek()]);
    dataString += "\r\n";

    appendFile(SD, "/YeniDosya.txt", dataString.c_str());

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
