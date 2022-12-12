/*
 *   Firebase veri tabanına veri gönderme örneği,
 *   Bu örnekte Deneyap Kart ve Deneyap Kart 1A dahili manyetik alan sensöründen veri gönderilmiştir. 
 *   Deneyap Mini ve Deneyap Kart G kartındaki mikrodenetleyicilerinde dahili magnetik alan sensörü yoktur bu yüzden magnetik okuma özelliği bulunmamaktadır.
 *   Bu uygulama Deneyap Kart G kartı ile gerçekleştirilmek istenirse harici magnetik alan sensörü bağlanmalıdır ve gerekli değişiklikler yapılmalıdır.
*/
#include <WiFi.h>
#include <Firebase_ESP_Client.h>

#define WLAN_SSID       "***********"         // Baglanti kurulacak Wi-Fi agi adi
#define WLAN_PASS       "***********"         // Baglanti kurulacak Wi-Fi agi sifresi
#define API_KEY         "***********"         // API anahtarı
#define DATABASE_URL    "***********"         // Gerçek zamanlı veritabı bağlantı linki

/*Firebase veritabanı tanımlamaları */
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

bool signupOK = false;
int manyetikAlan = 0;

void setup(){
  Serial.begin(115200);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  Serial.print("Wi-Fi Baglanıyor...");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Baglandı. IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  config.api_key = API_KEY;   // API anahtarı girilmesi
  
  config.database_url = DATABASE_URL; // Gerçek zamanlı veritabı bağlantı linki girilmesi

  if (Firebase.signUp(&config, &auth, "", "")){  // Veritabanına giriş yapılması
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop(){
  manyetikAlan = hallRead();   // Manyetik alan algılayıcısı veri okunması
  
  if (Firebase.ready() && signupOK){    // Dahili manyetik algılayıcıdan gelen veriler veritabanına göndermesi
    Firebase.RTDB.set(&fbdo, "deneyap/ManyetikAlan", manyetikAlan);
    Serial.println("Veri gonderme başarılıdır.");
  }
  else{
    Serial.println("Veri gonderme basarısızdır.");
  }
}
