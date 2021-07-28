#if DENEYAP_KART
#include <WiFi.h>

// ---------->>>>>>>>>> YUKLEME YAPILAMDAN DIKKAT EDILMESI GEREKEN HUSUS <<<<<<<<<<----------
// "Araclar->Partition Scheme->Huge APP" secilmeli //
// "Tools->Partition Scheme->Huge APP" secilmeli //

const char* ssid      = "*********";          // Baglanti kurulacak Wi-Fi agi adi
const char* password  = "*********";          // Baglanti kurulacak Wi-Fi agi sifresi

void setup() {
  Serial.begin(115200);                       // Hata ayiklamak icin seri terminal baslatildi
  Serial.setDebugOutput(true);                
  Serial.println();
  
  cameraInit();                               // Kamera konfigurasyonu yapildi

  WiFi.begin(ssid, password);                 // Wi-Fi agina baglaniliyor

  while (WiFi.status() != WL_CONNECTED)       // Baglanti saglanan kadar bekleniyor
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Wi-Fi agina baglanildi ");

  startCameraServer();                        // Kamera server baslatildi 

  Serial.print("Kamera hazir! Baglanmak icin 'http://");  // Baglanti saglandi
  Serial.print(WiFi.localIP());                           // Goruntunun yayinlanacagi IP adresi seri terminale yaziliyor
  Serial.println("' adresini kullaniniz");              
}

void loop() {
  delay(10000);
}
#else
#error Bu uygulama kamera baglantisi olmadigi icin Deneyap Mini ile gerceklestirilemez!
#endif