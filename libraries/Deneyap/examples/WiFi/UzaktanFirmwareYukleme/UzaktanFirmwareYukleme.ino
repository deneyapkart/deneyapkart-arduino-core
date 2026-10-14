#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

const char* ssid = "WIFIADI";
const char* password = "WIFISIFRESI";

void setup() {

  Serial.begin(115200);
  delay(2000);

  Serial.println();
  Serial.println("=== OTA TESTI ===");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("WiFi'ye baglaniliyor");

  int sayac = 0;

  while (WiFi.status() != WL_CONNECTED && sayac < 30) {
    delay(500);
    Serial.print(".");
    sayac++;
  }

  Serial.println();

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi BAGLANTISI BASARISIZ!");
    Serial.print("WiFi durum kodu: ");
    Serial.println(WiFi.status());
    return;
  }

  Serial.println("WiFi BAGLANTISI BASARILI!");

  Serial.print("IP adresi: ");
  Serial.println(WiFi.localIP());

  ArduinoOTA.setHostname("deneyap-ota");

  ArduinoOTA.onStart([]() {

    String type;

    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
    else
      type = "filesystem";

    Serial.println("Yukleme baslatiliyor: " + type);
  });

  ArduinoOTA.onEnd([]() {
    Serial.println();
    Serial.println("Yukleme tamamlandi!");
  });

  ArduinoOTA.onProgress([](unsigned int progress,
                           unsigned int total) {

    Serial.printf(
      "Ilerleme: %u%%\r",
      (progress * 100) / total
    );
  });

  ArduinoOTA.onError([](ota_error_t error) {

    Serial.printf("OTA Hata [%u]: ", error);

    if (error == OTA_AUTH_ERROR)
      Serial.println("Dogrulama basarisiz");

    else if (error == OTA_BEGIN_ERROR)
      Serial.println("Baslatma hatasi");

    else if (error == OTA_CONNECT_ERROR)
      Serial.println("Baglanti hatasi");

    else if (error == OTA_RECEIVE_ERROR)
      Serial.println("Veri alma hatasi");

    else if (error == OTA_END_ERROR)
      Serial.println("Bitirme hatasi");
  });

  ArduinoOTA.begin();

  Serial.println();
  Serial.println("==========");
  Serial.println("OTA HAZIR!");
  Serial.print("OTA IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("OTA adi: deneyap-ota");
  Serial.println("==========");
}

void loop() {

  ArduinoOTA.handle();
}