/*
 *   Deneyap Mini Elektronik Geliştirme Kartı'nın kutu açılış uygulamasıdır.
 *   Bu örnek yüklendikten sonra "DeneyapMiniSunucu" ismi ile ağ yayını yapmaya başlar. 
 *   Kablosuz ağa bağlanmaya uygun herhangi bir cihaz(mobil, tablet, bilgisayar vb.) kullanılarak bu ağa dahil olunur. 
 *   seri port ekrane yazılan adrese tarayıcıdan girilir ve RGB LED konrol edilmektedir.
 * 
 */
 
#include <WiFi.h> // Wifi.h kutuphanesi eklendi

const char* ssid     = "DeneyapMiniSunucu"; // Wi-Fi ag adi
const char* password = NULL;                // Wi-Fi ag sifresi

WiFiServer server(80); // Web sunucu port numarasi 80 olarak ayarlandi

String header; // HTTP request'i saklamak için değişken

String yesilDurum   = "kapali";
String kirmiziDurum = "kapali";
String maviDurum    = "kapali";
String cyanDurum    = "kapali";
String sariDurum    = "kapali";
String magentaDurum = "kapali";
String beyazDurum   = "kapali";

const int LED_G = 33;
const int LED_R = 34;
const int LED_B = 35;

void setup() {
  
  Serial.begin(115200);

  // RGB pinleri cikis olarak ayarlandi
  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_B, OUTPUT);

  digitalWrite(LED_G, LOW);
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_B, LOW);

  Serial.print("Erisim Noktasi(Access Point) ayarlanıyor…");
  WiFi.softAP(ssid, password); 
  
  IPAddress IP = WiFi.softAPIP();
  Serial.print("Erisim Noktasi(Access Point) IP adres: ");
  Serial.println(IP);
  
  server.begin(); // Sunucu baslatildi
}

void loop(){
  
  WiFiClient client = server.available();   

  if (client) { // Yeni bir istemci baglanirsa                            
    
    Serial.println("Yeni İstemci");         
    String currentLine = ""; // İstemciden gelen verileri tutmak icin degisken tanımlandi             
    while (client.connected()) { // İstemci bagli iken           
      if (client.available()) { // İstemciden okunacak bayt varsa       
        char c = client.read(); // Bir bayt oku, daha sonra          
        Serial.write(c); // Seri monitore yaz                
        header += c;
        if (c == '\n') { // Eger bayt, '\n' ise           
            
          if (currentLine.length() == 0) {
            
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            if (header.indexOf("GET /yesil/acik") >= 0) {
              Serial.println("Yeşil açık");
              yesilDurum = "acik";
              kirmiziDurum = "kapali";
              maviDurum = "kapali";
              cyanDurum = "kapali";
              sariDurum = "kapali";
              magentaDurum = "kapali";
              beyazDurum = "kapali";
              digitalWrite(LED_G, HIGH);
              digitalWrite(LED_R, LOW);
              digitalWrite(LED_B, LOW);
            } else if (header.indexOf("GET /yesil/kapali") >= 0) {
              Serial.println("Yeşil kapalı");
              yesilDurum = "kapali";
              digitalWrite(LED_G, LOW);
            } else if (header.indexOf("GET /kirmizi/acik") >= 0) {
              Serial.println("Kırmızı açık");
              kirmiziDurum = "acik";
              yesilDurum = "kapali";
              maviDurum = "kapali";
              cyanDurum = "kapali";
              sariDurum = "kapali";
              magentaDurum = "kapali";
              beyazDurum = "kapali";
              digitalWrite(LED_R, HIGH);
              digitalWrite(LED_G, LOW);
              digitalWrite(LED_B, LOW);
            } else if (header.indexOf("GET /kirmizi/kapali") >= 0) {
              Serial.println("Kırmızı kapalı");
              kirmiziDurum = "kapali";
              digitalWrite(LED_R, LOW);
            } else if (header.indexOf("GET /mavi/acik") >= 0) {
              Serial.println("Mavi açık");
              maviDurum = "acik";
              yesilDurum = "kapali";
              kirmiziDurum = "kapali";
              cyanDurum = "kapali";
              sariDurum = "kapali";
              magentaDurum = "kapali";
              beyazDurum = "kapali";
              digitalWrite(LED_B, HIGH);
              digitalWrite(LED_G, LOW);
              digitalWrite(LED_R, LOW);
            } else if (header.indexOf("GET /mavi/kapali") >= 0) {
              Serial.println("Mavi kapalı");
              maviDurum = "kapali";
              digitalWrite(LED_B, LOW);
            } else if (header.indexOf("GET /cyan/acik") >= 0) {
              Serial.println("Cyan açık");
              cyanDurum = "acik";
              yesilDurum = "kapali";
              kirmiziDurum = "kapali";
              maviDurum = "kapali";
              sariDurum = "kapali";
              magentaDurum = "kapali";
              beyazDurum = "kapali";
              digitalWrite(LED_G, HIGH);
              digitalWrite(LED_B, HIGH);
              digitalWrite(LED_R, LOW);
            } else if (header.indexOf("GET /cyan/kapali") >= 0) {
              Serial.println("Cyan kapalı");
              cyanDurum = "kapali";
              digitalWrite(LED_G, LOW);
              digitalWrite(LED_B, LOW);
            } else if (header.indexOf("GET /sari/acik") >= 0) {
              Serial.println("Sarı açık");
              sariDurum = "acik";
              yesilDurum = "kapali";
              kirmiziDurum = "kapali";
              maviDurum = "kapali";
              cyanDurum = "kapali";
              magentaDurum = "kapali";
              beyazDurum = "kapali";
              digitalWrite(LED_G, HIGH);
              digitalWrite(LED_R, HIGH);
              digitalWrite(LED_B, LOW);
            } else if (header.indexOf("GET /sari/kapali") >= 0) {
              Serial.println("Sarı kapalı");
              sariDurum = "kapali";
              digitalWrite(LED_G, LOW);
              digitalWrite(LED_R, LOW);
            } else if (header.indexOf("GET /magenta/acik") >= 0) {
              Serial.println("Magenta açık");
              magentaDurum = "acik";
              yesilDurum = "kapali";
              kirmiziDurum = "kapali";
              maviDurum = "kapali";
              cyanDurum = "kapali";
              sariDurum = "kapali";
              beyazDurum = "kapali";
              digitalWrite(LED_R, HIGH);
              digitalWrite(LED_B, HIGH);
              digitalWrite(LED_G, LOW);
            } else if (header.indexOf("GET /magenta/kapali") >= 0) {
              Serial.println("Magenta kapalı");
              magentaDurum = "kapali";
              digitalWrite(LED_R, LOW);
              digitalWrite(LED_B, LOW);
            } else if (header.indexOf("GET /beyaz/acik") >= 0) {
              Serial.println("Beyaz açık");
              beyazDurum = "acik";
              yesilDurum = "kapali";
              kirmiziDurum = "kapali";
              maviDurum = "kapali";
              cyanDurum = "kapali";
              sariDurum = "kapali";
              magentaDurum = "kapali";
              digitalWrite(LED_G, HIGH);
              digitalWrite(LED_R, HIGH);
              digitalWrite(LED_B, HIGH);
            } else if (header.indexOf("GET /beyaz/kapali") >= 0) {
              Serial.println("Beyaz kapalı");
              beyazDurum = "kapali";
              digitalWrite(LED_G, LOW);
              digitalWrite(LED_R, LOW);
              digitalWrite(LED_B, LOW);
            }

            client.println("<!DOCTYPE html><style>body { background-color:#000000;}</style><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            
            // ACIK/KAPALI butonlarina stil verildi 
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #008000; border: none; color: white; padding: 10px 32px;");
            client.println("text-decoration: none; font-size: 30px; margin: 10px; cursor: pointer;}");
            client.println(".button2 {background-color: #800000;}</style></head>");
            
            // Web Sayfasi Basligi
            client.println("<body><h1><font color=#FFFFFF size=6;>Deneyap Mini RGB LED Kontrol</font></h1>");

           client.println("<p><font color=#008000 size=3;>YESIL</font><font color=#FFFFFF size=3;> - Durum " + yesilDurum + "</font>&emsp;<font color=#FF0000 size=3;>KIRMIZI</font><font color=#FFFFFF size=3;> - Durum " + kirmiziDurum + "</font></p>");           
            if (yesilDurum == "kapali") { 
              client.println("<a href=\"/yesil/acik\"><button class=\"button\">ACIK</button></a>");
            } else {
              client.println("<a href=\"/yesil/kapali\"><button class=\"button button2\">KAPALI</button></a>");
            } 
            if (kirmiziDurum == "kapali") {
              client.println("<a href=\"/kirmizi/acik\"><button class=\"button\">ACIK</button></a>");
            } else {
              client.println("<a href=\"/kirmizi/kapali\"><button class=\"button button2\">KAPALI</button></a>");
            }
               
            client.println("<p><font color=#0000FF size=3;>MAVI</font><font color=#FFFFFF size=3;> - Durum " + maviDurum + "</font>&emsp;<font color=#00FFFF size=3;>CYAN</font><font color=#FFFFFF size=3;> - Durum " + cyanDurum + "</font></p>");  
            if (maviDurum == "kapali") {
              client.println("<a href=\"/mavi/acik\"><button class=\"button\">ACIK</button></a>");
            } else {
              client.println("<a href=\"/mavi/kapali\"><button class=\"button button2\">KAPALI</button></a>");
            }      
    
            if (cyanDurum == "kapali") {
              client.println("<a href=\"/cyan/acik\"><button class=\"button\">ACIK</button></a>");
            } else {
              client.println("<a href=\"/cyan/kapali\"><button class=\"button button2\">KAPALI</button></a>");
            }

            client.println("<p><font color=#FFFF00 size=3;>SARI</font><font color=#FFFFFF size=3;> - Durum " + sariDurum + "</font>&emsp;<font color=#FF00FF size=3;>MAGENTA</font><font color=#FFFFFF size=3;> - Durum " + magentaDurum + "</font></p>");        
            if (sariDurum == "kapali") {
              client.println("<a href=\"/sari/acik\"><button class=\"button\">ACIK</button></a>");
            } else {
              client.println("<a href=\"/sari/kapali\"><button class=\"button button2\">KAPALI</button></a>");
            }
   
            if (magentaDurum == "kapali") {
              client.println("<a href=\"/magenta/acik\"><button class=\"button\">ACIK</button></a></p>");
            } else {
              client.println("<a href=\"/magenta/kapali\"><button class=\"button button2\">KAPALI</button></a>");
            }

            client.println("<p><font color=#FFFFFF size=3;>BEYAZ</font><font color=#FFFFFF size=3;> - Durum " + beyazDurum + "</font></p>");      
            if (beyazDurum == "kapali") {
              client.println("<p><a href=\"/beyaz/acik\"><button class=\"button\">ACIK</button></a></p>");
            } else {
              client.println("<p><a href=\"/beyaz/kapali\"><button class=\"button button2\">KAPALI</button></a></p>");
            }
            
            client.println("</body></html>");
       
            client.println();
            break;
          } else { 
            currentLine = "";
          }
        } else if (c != '\r') { 
          currentLine += c;      
        }
      }
    }
       
    header = ""; // Header degiskeni temizlendi 
    client.stop(); 
    Serial.println("İstemci baglantisi kesildi");
    Serial.println("");
  }
}
