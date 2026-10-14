#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

#define USE_SERIAL Serial

WiFiMulti wifiMulti;

void setup() {

  USE_SERIAL.begin(115200);
  delay(1000);

  USE_SERIAL.println();
  USE_SERIAL.println("Program baslatildi.");

  wifiMulti.addAP("wifiadi", "wifisifresi");

  USE_SERIAL.print("WiFi'ye baglaniliyor");

  while (wifiMulti.run() != WL_CONNECTED) {
    USE_SERIAL.print(".");
    delay(500);
  }

  USE_SERIAL.println();
  USE_SERIAL.println("WiFi BAGLANTISI BASARILI!");

  USE_SERIAL.print("IP Adresi: ");
  USE_SERIAL.println(WiFi.localIP());

  WiFiClientSecure client;
  client.setInsecure();

  HTTPClient http;

  USE_SERIAL.println();
  USE_SERIAL.println("[HTTPS] Baglanti baslatiliyor...");

  http.begin(client, "https://deneyapkart.org/");

  USE_SERIAL.println("[HTTPS] GET istegi gonderiliyor...");

  int httpCode = http.GET();

  USE_SERIAL.print("[HTTPS] Donen kod: ");
  USE_SERIAL.println(httpCode);

  if (httpCode > 0) {

    if (httpCode == HTTP_CODE_OK) {

      USE_SERIAL.println();
      USE_SERIAL.println("===== HTML BASLANGIC =====");

      String payload = http.getString();
      USE_SERIAL.println(payload);

      USE_SERIAL.println("===== HTML BITIS =====");

    } else {

      USE_SERIAL.print("Sunucu cevap verdi. HTTP kodu: ");
      USE_SERIAL.println(httpCode);
    }

  } else {

    USE_SERIAL.print("HTTPS HATASI: ");
    USE_SERIAL.println(http.errorToString(httpCode));
  }

  http.end();
}

void loop() {

}