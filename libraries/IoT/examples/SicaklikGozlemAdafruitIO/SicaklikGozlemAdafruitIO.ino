/*
 *   SicaklikGozlemAdafruitIO örneği,
 *   Bu örnekte AdafruitIO web uygulaması kullanılmaktadır.
 *   Deneyap Kart'taki dahili IMU'dan alınan sıcaklık verileri AdafruitIO bulut web uygulamasıda gözlenmektedir.
 *   Bununla birlikte AdafruitIO bulut web uygulamasına eklenen buton ile karttaki dahili LED kontrol edilebilmektedir.
 *   Bu örnek uygulama diğer Deneyap Geliştirme Kartları kullanılırsa harici sıcaklık sensörü bağlanılmalı ve kodda gerekli değişiklikler yapılmalıdır.   
 *
 *  ==============================================================================
 *    Bu uygulama örneği için "Adafruit_MQTT by Adafruit" kütüphanesi indirilmelidir.  ->https://github.com/adafruit/Adafruit_MQTT_Library<-
 *    Bu uygulama örneği Adafruit_MQTT kütüphanesi 2.4.3 versiyonu ile yazılmıştır.
 *  ==============================================================================
*/
#include "lsm6dsm.h"  // Deneyap Kart dahili IMU kütüphanesinin eklenmesi
#include "WiFi.h"
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

#define WLAN_SSID "***********"  // Baglanti kurulacak Wi-Fi agi adi
#define WLAN_PASS "***********"  // Baglanti kurulacak Wi-Fi agi sifresi
#define AIO_SERVER "io.adafruit.com"
#define AIO_SERVERPORT 1883
#define AIO_USERNAME "***********"  // Adafruit IO kullanici ismi
#define AIO_KEY "***********"       // Adafruit IO kullanici anahtari

LSM6DSM imu;  //IMU için Class tanımlaması

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish sicaklik = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/sicaklik");
Adafruit_MQTT_Subscribe buton_durumu = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/buton-durumu");
float sicaklik_degeri = 0.0;

/*MQTT bağlatısı gerçekleştirilmesi */
void MQTT_connect() {
  int8_t ret;
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Bulut sistemine baglaniliyor... ");
  uint8_t count = 3;

  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("3 saniye icinde tekrar baglanti denemesi gerceklesecek...");
    mqtt.disconnect();
    delay(3000);
    count = count - 1;

    if (count == 0) {
      esp_restart();
    }
  }

  Serial.println("Bulut sistemine baglanildi!");
}

void setup() {
  pinMode(LEDB, OUTPUT);
  imu.begin();
  Serial.begin(115200);
  delay(10);

  /*WiFi bağlatısı gerçekleştirilmesi*/
  Serial.println();
  Serial.println();
  Serial.print(WLAN_SSID);
  Serial.print(" kablosuz agina baglaniliyor");
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Kablosuz aga baglanildi!");
  Serial.print("IP adresi: ");
  Serial.println(WiFi.localIP());

  mqtt.subscribe(&buton_durumu);
}

void loop() {
  MQTT_connect();
  Adafruit_MQTT_Subscribe *subscription;

  while ((subscription = mqtt.readSubscription(2000))) {
    /*Buton değeri alınıyor ve ona göre led yanıp söndürülüyor */
    if (subscription == &buton_durumu) {
      Serial.println();
      Serial.print(F("Gelen mesaj: "));
      Serial.println((char *)buton_durumu.lastread);

      if (!strcmp((char *)buton_durumu.lastread, "AÇIK")) {
        writeBlueLed(HIGH);
      } else {
        writeBlueLed(LOW);
      }
    }
  }

  /*Sıcaklık değeri alınması, seri port ekranına yazılması, AdafruitIO'ya gönderilmesi*/
  sicaklik_degeri = imu.readTempC();
  Serial.print(F("\nSicaklik degeri gonderiliyor "));
  Serial.print(sicaklik_degeri);
  Serial.print("...");

  /*Sıcaklık değeri Adafruit-io gönderildi */
  if (!sicaklik.publish(sicaklik_degeri)) {
    Serial.println(F(" Gonderilemedi!"));
  } else {
    Serial.println(F(" Gonderildi"));
  }
  delay(250);
}
