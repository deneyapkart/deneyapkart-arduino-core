
// ---------->>>>>>>>>> YÜKLEME YAPILAMDAN DİKKAT EDİLMESİ GEREKEN HUSUS <<<<<<<<<<----------
// "Araçlar > Partition Scheme > Huge APP" seçilmeli
// (EN: "Tools > Partition Scheme > Huge APP" must be chosen)

/*
 *   Deneyap Elektronik Geliştirme Seti'nin kutu açılış uygulamasıdır.
 *
 *   Bu örnek karta yüklendikten sonra kablosuz ağa bağlanmaya uygun herhangi bir cihaz(telefon, tablet, bilgisayar vb.) kullanılarak
 *   kartın ağına bağlanılır (bağlanmanız gereken ağ sizin kendi Wi-Fi ağınız değil aşağıdaki satırlarla oluşturulan yeni ağdır).
 *   Bu ağa bağlandıktan sonra seri port ekranındaki adrese (ör. http://192.168.4.1) tarayıcıdan girilir ve canlı görüntü başlatılır.
 *
 *   Not: Seri port ekranınız boş ise; seri port ekranınız açık iken kartın üzerinde bulunan 'res' butonuna basınız.
 */

#include <WiFi.h>

const char* agAdi = "DeneyapKart Kablosuz Agı";      // Oluşturulacak Wi-Fi ağı adı
const char* sifre = NULL;                            // Oluşturulacak Wi-Fi ağı şifresi

// --- İnce Ayarlar (isteğe bağlı) ---
//IPAddress apip(192,168,1,1);
//IPAddress gateway(192,168,1,1);
//IPAddress subnet(255,255,255,0);

void setup() {
  Serial.begin(115200); // Hata ayıklamak için seri port ekran başlatıldı, iletişim hızı 115200 (EN: Baud rate 115200)
  Serial.setDebugOutput(true); // Wi-Fi hata ayıklama açıldı, olası Wi-Fi hataları seri ekrana yazılır
  Serial.println();

  cameraInit(); // Kamera konfigürasyonu yapıldı

  WiFi.softAP(agAdi, sifre); // Yeni Kablosuz ağ oluşturuldu (AP access point anlamına gelmektedir, Türkçesi erişim noktasıdır(modeme benzer şekilde faaliyet gösteren bir mekanizmadır))
  // --- İnce Ayarlar (isteğe bağlı) ---
  //  WiFi.softAPConfig(apip, gateway, subnet);

  delay(100); // 100 milisaniye bekle

  startCameraServer(); // Kamera sunucusu başlatıldı

  // Canlı Görüntünün yayınlanacağı IP adresi seri port ekrana yazılır
  Serial.println("Kamera hazır! Bağlanmak için yeni oluşturulan Wi-Fi ağına bağlanın ve tarayıcınızın adres çubuğuna 'http://" + WiFi.softAPIP().toString() + "' adresini giriniz");
}

void loop() {
  delay(10000);
}
