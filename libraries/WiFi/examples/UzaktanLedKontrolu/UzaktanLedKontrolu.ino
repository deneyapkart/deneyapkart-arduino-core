/*
 *   UzaktanLedKontrolu örneği,
 *   Bu örnekte bilgisayarınız veya telefonunuzun WiFi ayarlarından DeneyapKart bağlanılması ve "dydkmpv10" şifresini girilmesi gerekmektedir. 
 *   Daha sonra tarayıcıdan "192.168.4.1" bu adrese girilmesi gerekmektedir. 
 *   Açılan ekrandaki butonlar ile Deneyap Kartlardaki dahili led yanıp ve söndürme işlemlerinin kontrolü sağlanmaktadır.
*/
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

const char *ssid = "DeneyapKart";    // DeneyapKart Erisim Noktasi (AP) ismi
const char *password = "dydkmpv10";  // DeneyapKart Erisim Noktasi (AP) sifresi

WiFiServer server(80);  // WiFi sunucusu icin class tanimlama

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);     // Dahili mavi led cikis olarak ayarlandi
  digitalWrite(LED_BUILTIN, HIGH);  // Ledin ilk durumu ayarlandi

  Serial.begin(115200);  // Seri haberlesme baslatildi
  Serial.println();
  Serial.println("Erisim Noktasi (AP) konfigure ediliyor...");

  WiFi.softAP(ssid, password);  // Cihaz Erisim Noktasi (AP) olarak baslatildi
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("Erisim noktasi IP adresi: ");  // Baglanti IP adresi seri port ekrane yazdiriliyor
  Serial.println(myIP);
  server.begin();
  Serial.println("Server baslatildi");
}

void loop() {
  WiFiClient client = server.available();  // Baglanti talepleri dinleniyor

  if (client) {  // Istemci varligi kontrol ediliyor
    Serial.println("Yeni istemci talebi geldi.");
    String currentLine = "";  // Istemciden gelen veriyi tutmak icin String degiskeni tanimlaniyor
    while (client.connected()) {
      if (client.available()) {                        // Istemciden veri kontrolu yapiliyor
        char c = client.read();                        // Veri okunuyor
        Serial.write(c);                               // seri port ekrane veri yaz
        if (c == '\n') {                               // "Yeni Satir" karakteri geldi mi
          if (currentLine.length() == 0) {             // Satirda bulunan veri sayisi sifir mi (istemci talepte bulunmus)
            client.println("HTTP/1.1 200 OK");         // Yanit kodu (e.g. HTTP/1.1 200 OK)
            client.println("Content-type:text/html");  // Istemciye icerik turu ile ilgili bilgi gonderiliyor
            client.println();
            client.print("Ledi <a href=\"/H\">YAK</a> <br>");     // Icerik gonderiliyor
            client.print("Ledi <a href=\"/L\">SONDUR</a> <br>");  // Icerik gonderiliyor
            client.println();                                     //
            break;
          } else {  // Satirdaki veri sayisi sifir degilse, satir temizleniyor
            currentLine = "";
          }
        } else if (c != '\r') {  // Veri "Satir Basi" harici baska bir karakter mi
          currentLine += c;      // Gelen veriyi satir sonuna ekle
        }
        if (currentLine.endsWith("GET /H")) {  // Istemciden gelen talebi kontrol et, "GET /H" ya da "GET /L":
          digitalWrite(LED_BUILTIN, LOW);             // GET /H ledi yakar
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(LED_BUILTIN, HIGH);  // GET /L ledi sondurur
        }
      }
    }
    client.stop();  // Yanittan sonra http baglantisi durdurulur ve yeni istemci talebi beklenir
    Serial.println("Client Disconnected.");
  }
}
