/*
 *   SicaklikGozlemThingSpeak örneği,
 *   Bu örnekte ThingSpeak web uygulaması kullanılmaktadır.
 *   Deneyap Kart'taki dahili IMU'dan alınan sıcaklık verileri ThingSpeak web uygulamasında gözlenebilmektedir. 
 *   Bu örnek uygulama diğer Deneyap Geliştirme Kartları kullanılırsa harici sıcaklık sensörü bağlanılmalı ve kodda gerekli değişiklikler yapılmalıdır.
*/
#include "WiFi.h"
#include "HTTPClient.h"
#include "lsm6dsm.h" // Deneyap Kart dahili IMU kütüphanesinin eklenmesi

LSM6DSM IMU;  //IMU için Class tanımlaması
float sicaklik;

const char* server   = "api.thingspeak.com";
const char* ssid     = "******";    // Baglanti kurulacak Wi-Fi agi adi
const char* password = "******";    // Baglanti kurulacak Wi-Fi agi sifresi
String apiKey        = "******";    // ThingSpeak Write  API Keys

WiFiClient client;
const int httpPort = 80;

void setup() {
  IMU.begin();           // IMU ayarlari konfigure edilmesi
  Serial.begin(115200);  // Seri haberlesme baslatilmasi

   /* Wi-Fi bağlantısı gerçekleştiriliyor*/
  Serial.print(ssid);
  Serial.print(" kablosuz agina baglaniliyor");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Kablosuz aga baglanildi!");
  Serial.print("IP adresi: "); Serial.println(WiFi.localIP());
}

void loop() {
    /* Sıcaklık değeri alınması ve seri port ekranına yazılması */
    sicaklik = IMU.readTempC();
    Serial.print("Sıcaklık: ");
    Serial.println(sicaklik);
    
    /* Sıcaklık değeri ThingSpeak gönderilmesi */
    client.connect(server, httpPort);
    
    String data_to_send = apiKey;
    data_to_send += "&field1=";
    data_to_send += String(sicaklik);
    data_to_send += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(data_to_send.length());
    client.print("\n\n");
    client.print(data_to_send);

    delay(1000);
}
