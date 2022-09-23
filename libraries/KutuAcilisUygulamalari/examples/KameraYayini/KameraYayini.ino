
// ---------->>>>>>>>>> YUKLEME YAPILAMDAN DIKKAT EDILMESI GEREKEN HUSUS <<<<<<<<<<----------
// "Araclar->Partition Scheme->Huge APP" secilmeli //
// "Tools->Partition Scheme->Huge APP" secilmeli //

/*
 *   Deneyap Elektronik Geliştirme Seti'nin kutu açılış uygulamasıdır.
 *   Bu örnek yüklendikten sonra kablosuz ağa bağlanmaya uygun herhangi bir cihaz(mobil, tablet, bilgisayar vb.) kullanılarak bu ağa dahil olunur. 
 *   seri port ekrane yazılan adrese tarayıcıdan girilir ve görüntü başlatılır.
 * 
 */
#include <WiFi.h>

const char* ssidAP      = "DeneyapKart";      // Wi-Fi ag adi
const char* passwordAP  = NULL;               // Wi-Fi ag sifresi

//IPAddress apip(192,168,1,1);
//IPAddress gateway(192,168,1,1);
//IPAddress subnet(255,255,255,0);

void setup() {
  Serial.begin(115200);                       // Hata ayiklamak icin seri port ekran baslatildi
  Serial.setDebugOutput(true);                
  Serial.println();
  
  cameraInit();                               // Kamera konfigurasyonu yapildi

  WiFi.softAP(ssidAP, passwordAP);
//  WiFi.softAPConfig(apip, gateway, subnet);
  delay(100);

  startCameraServer();                        // Kamera server baslatildi 

  Serial.print("Kamera hazir! Baglanmak icin 'http://");  // Baglanti saglandi
  Serial.print(WiFi.softAPIP());                          // Goruntunun yayinlanacagi IP adresi seri port ekrane yaziliyor
  Serial.println("' adresini kullaniniz");      
}       

void loop() {
  delay(10000);
}
