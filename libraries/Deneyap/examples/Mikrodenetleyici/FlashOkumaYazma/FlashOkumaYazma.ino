/*
 * FlashOkumaYazma örneği
 * Bu örnekte kaç kez depolamak için Prefence kütüphanesinin kullanıldığını göstermektedir.
 * 
 */

#include <Preferences.h>

Preferences preferences;

void setup() {
  Serial.begin(115200);
  Serial.println();

   // Prefence'i uygulamam ad alanıyla açın. Her uygulama modülü, kitaplık vb.
   // anahtar adı çakışmalarını önlemek için bir ad alanı adı kullanmalıdır. Depo açacağız
   // RW modu (ikinci parametre yanlış olmalıdır).
   // Not: Ad alanı adı 15 karakterle sınırlıdır.
  preferences.begin("benim-uygulamam", false);

  // Açılan ad alanı altındaki tüm Prefences kaldır
  //preferences.clear();

  // veya yalnızca sayaç anahtarını kaldırın
  //preferences.remove("sayac");

   // Sayaç değerini al, eğer anahtar yoksa, varsayılan bir 0 değeri döndür
   // Not: Anahtar adı 15 karakterle sınırlıdır.
  unsigned int sayac = preferences.getUInt("sayac", 0);

  // Sayacı 1 artır
  sayac++;

  // Sayacı seri port ekrane yazdır
  Serial.printf("Sayac degeri: %u\n", sayac);

  // Sayacı Prefence kaydet
  preferences.putUInt("sayac", sayac);

  // Prefences Kapat
  preferences.end();
  
  // 10 saniye bekle
  Serial.println("10 saniye içinde yeniden başlatılıyor...");
  delay(10000);

  // Yeniden başlat
  ESP.restart();
}

void loop() {}
