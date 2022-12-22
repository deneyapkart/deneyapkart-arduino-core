/*
 *    LedKontrolBlynk örneği,
 *    Bu örnekte Blynk 2 uygulaması kullanılmıştır. 
 *    Blynk web tabanlı bulut(https://blynk.cloud/) ve mobil uygulamasında(Blynk IoT) Deneyap Geliştirme Kartlarındaki dahili LED kontrol edilmektedir.
 *    Aynı zamanda Deneyap Geliştirme Kartlarınadaki dahili buton durumu Blynk web tabanlı bulut ve mobil uygulamalarında gözlemlenmektedir.
 *    
 *    Bu uygulama örneği için "Blynk by Volodymyr Shymanskyy" kütüphanesi indirilmelidir.  ->https://github.com/blynkkk/blynk-library <-
 *    Bu uygulama örneği Blynk kütüphanesi 1.0.1 versiyonu ile yazılmıştır.
*/
#define BLYNK_TEMPLATE_ID   "*******"  // blynk.cloud web tabanlı bulut ekranında Device Info'da konfigurasyon ayarları yer almaktadır
#define BLYNK_DEVICE_NAME   "*******"  // blynk.cloud web tabanlı bulut ekranında Device Info'da konfigurasyon ayarları yer almaktadır
#define BLYNK_AUTH_TOKEN    "*******"  // blynk.cloud web tabanlı bulut ekranında Device Info'da konfigurasyon ayarları yer almaktadır

#include "WiFi.h"
#include "WiFiClient.h"
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "*******";      // Bağlantı kurulacak Wi-Fi ağı adı
char pass[] = "*******";      // Bağlantı kurulacak Wi-Fi ağı şifresi

BlynkTimer timer;

/* Blynk uygulamasında Widget Box'da Button seçildi ve Switch Control(V0) virtual pinine bağlandı */
BLYNK_WRITE(V0) {                     // Blynk web tabanlı bulut ya da mobil uygulamasında V0 bağlı butona basıldığında
  int LedState = param.asInt();
  if(LedState == 1) {
    digitalWrite(LED_BUILTIN, HIGH);  // V0 virtual pinine bağlı butona basıldığında Deneyap Geliştirme Kartlarındaki LED'in yanması
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}

/* Blynk uygulamasında Widget Box'da Value Display seçildi ve Switch Value(V1) virtual pinine bağlandı */
void BlynkButtonRead() {
  /* İstediğiniz herhangi bir değeri gönderebilirsiniz
     Saniyede 10'dan fazla değer göndermeyin*/
  int ButtonValue = digitalRead(GPKEY);  // Deneyap Geliştirme kartlarındaki butuna basıldığında, 
  Blynk.virtualWrite(V1, ButtonValue);   // Buton durumunun Blynk web tabanlı bulut ya da mobil uygulamalarında V1 virtual pinine bağlı ekranda gözlemlenmesi
}

void setup() {
  Serial.begin(115200);           // Seri haberleşme baslatılması
  Blynk.begin(auth, ssid, pass);  // Deneyap Geliştirme kartı ile Blynk bulutunun bağlanması
  pinMode(LED_BUILTIN,OUTPUT);    // Deneyap Geliştirme Kartlarındaki dahili LED çıkış olarak ayarlanması
  pinMode(GPKEY,INPUT);           // Deneyap Geliştirme Kartlarındaki dahili Genel amaçlı buton pini giriş olarak ayarlanması
}

void loop() {
  Blynk.run(); // Blynk başlatılması
  timer.run(); // BlynkTimer başlatılması
  timer.setInterval(1000L, BlynkButtonRead); // Deneyap Geliştirme Kartlarındaki buton durumunun okunması
}