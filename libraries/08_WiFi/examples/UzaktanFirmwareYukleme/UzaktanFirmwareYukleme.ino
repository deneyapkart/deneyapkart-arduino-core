#include <WiFiESP32.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

const char* ssid = "..........";
const char* password = "..........";

void setup() {
  Serial.begin(115200);
  Serial.println("Onyukleme");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi baglantisi basarisiz! Yeniden baslatiliyor...");
    delay(5000);
    ESP.restart();
  }

  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Yukleme baslatiliyor " + type);
    })
    .onEnd([]() {
      Serial.println("\nTamamlandi");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Ilerleme durumu: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Hata[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Dogrulama basarisiz");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Baslatilamadi");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Baglanti basarisiz");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Alma basarisiz");
      else if (error == OTA_END_ERROR) Serial.println("Bitirme basarisiz");
    });

  ArduinoOTA.begin();

  Serial.println("Hazir");
  Serial.print("IP adres: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  ArduinoOTA.handle();
}