#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>

const byte DNS_PORT = 53;

IPAddress apIP(192, 168, 1, 1);

DNSServer dnsServer;
WebServer webServer(80);

void setup() {

  Serial.begin(115200);
  delay(3000);

  Serial.println();
  Serial.println("DNS SUNUCU TESTI");

  // Access Point modu
  WiFi.mode(WIFI_AP);

  // Kartin IP adresini 192.168.1.1 yap
  WiFi.softAPConfig(
    apIP,
    apIP,
    IPAddress(255, 255, 255, 0)
  );

  // WiFi agini olustur
  bool sonuc = WiFi.softAP("DNS Sunucu Ornegi");

  if (sonuc) {
    Serial.println("WiFi agi olusturuldu!");
  } else {
    Serial.println("WiFi agi olusturulamadi!");
  }

  Serial.print("AP IP adresi: ");
  Serial.println(WiFi.softAPIP());

  // DNS ayarlari
  dnsServer.setTTL(300);

  dnsServer.setErrorReplyCode(
    DNSReplyCode::ServerFailure
  );

  bool dnsSonuc = dnsServer.start(
    DNS_PORT,
    "www.DNSSunucuOrnek.com",
    apIP
  );

  if (dnsSonuc) {
    Serial.println("DNS sunucusu baslatildi!");
  } else {
    Serial.println("DNS sunucusu BASLATILAMADI!");
  }

  // Web sunucusuna gelen istekleri yakala
  webServer.onNotFound([]() {

    String message = "Merhaba Dunya!\n\n";
    message += "URI: ";
    message += webServer.uri();

    webServer.send(
      200,
      "text/plain",
      message
    );

    Serial.print("Web istegi geldi: ");
    Serial.println(webServer.uri());
  });

  webServer.begin();

  Serial.println("Web sunucusu baslatildi!");
  Serial.println();
  Serial.println("TEST HAZIR");
  Serial.println("WiFi: DNS Sunucu Ornegi");
  Serial.println("Adres: http://www.DNSSunucuOrnek.com");
}

void loop() {

  dnsServer.processNextRequest();
  webServer.handleClient();

}