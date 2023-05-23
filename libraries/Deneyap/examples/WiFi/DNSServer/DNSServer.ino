/*
 *   DNSServer örneği,
 *   Örnek yüklendikten sonra "DNS Sunucu Ornegi" kablosuz ağına bağlanmaya uygun herhangi bir cihaz(mobil, tablet, bilgisayar vb.) kullanılarak bu ağa dahil olunur.
 *   www.DNSSunucuOrnek.com adresine gidilir. 
 * 
*/ 
#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>

WebServer webServer(80);

const byte DNS_PORT = 53;

IPAddress apIP(192, 168, 1, 1);

DNSServer dnsServer;

void setup() {
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("DNS Sunucu Ornegi");

  //alan adıyla ilişkili TTL'yi değiştir (saniye cinsinden)
  //varsayılan 60 saniyedir
  dnsServer.setTTL(300);
  
  //diğer tüm alanlar için hangi dönüş kodunun kullanılacağını ayarlayın 
  //(örn. NonExistentDomain yerine ServerFailure sorgu sayısını azaltacak
  //müşteriler tarafından gönderilir)
  //varsayılan DNSReplyCode::NonExistentDomain
  dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);

  //belirli bir alan adı için DNS sunucusunu başlat
  dnsServer.start(DNS_PORT, "www.DNSSunucuOrnek.com", apIP);

  //DNS sunucusunun çalıştığını görmek için basit HTTP sunucusu
  webServer.onNotFound([]() {
    String message = "Merhaba Dunya!\n\n";
    message += "URI: ";
    message += webServer.uri();
    
    webServer.send(200, "text/plain", message);
  });
  webServer.begin();
}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
}
