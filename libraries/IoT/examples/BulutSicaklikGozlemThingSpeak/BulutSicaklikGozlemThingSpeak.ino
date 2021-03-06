/*
 *   BulutSicaklikGozlem örneği,
 *   Bu örnekte ThingSpeak web uygulaması kullanılmaktadır. ThingSpeak web uygulamasına Deneyap karttaki IMU ile alınan ortam sıcaklık webde eklenen textte veya grafik ile gözlenebilmektedir. 
 *   Bu uygulama Deneyap Kart 1A veya Deneyap Mini Kartı ile gerçekleştirilmek istenirse harici sıcaklık sensörü bağlanmalıdır ve gerekli değişiklikler yapılmalıdır. 
 *    
 */
#include <WiFi.h>
#include "HTTPClient.h"
#include "lsm6dsm.h"

LSM6DSM IMU;  //IMU için Class tanımlaması
float sicaklik;

const char* server   = "api.thingspeak.com";
const char* ssid     = "******";    // Baglanti kurulacak Wi-Fi agi adi
const char* password = "******";    // Baglanti kurulacak Wi-Fi agi sifresi
String apiKey        = "******";    // ThingSpeak Write  API Keys

WiFiClient client;
const int httpPort = 80;

void setup() {
  IMU.begin();           // IMU ayarlari konfigure edildi
  Serial.begin(115200);  // Seri haberlesme baslatildi

   /*WiFi bağlantısı gerçekleştiriliyor*/
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
    /*Sıcaklık değeri alınıyor ve seri terminale yazılıyor */
    sicaklik = IMU.readTempC();
    Serial.print("Sıcaklık: ");
    Serial.println(sicaklik);
    
    /*Sıcaklık değeri ThingSpeak gönderiliyor */
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
