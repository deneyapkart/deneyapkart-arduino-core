/*
 *   İki Deneyap kartının haberleşmesi örneği,
 *   Bu örnekte kullandığınız verici karttan gelen buton durumuna göre led yanacaktır.
*/
#include "WiFi.h"
#include "esp_now.h"

typedef struct struct_message {
  bool button;
} struct_message;

struct_message myData;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Buton Durumu: ");
  Serial.println(myData.button);
  Serial.println();
  if (myData.button == 0) {
  digitalWrite(LEDB,HIGH); // DENEYAP KART veya DENEYAP MİNİ kartı kullanılıyorsa
  // neopixelWrite(RGBLED,0,0,32); // DENEYAP KART 1A ve DENEYAP KART G kartı kullanılıyorsa
 }else{
  digitalWrite(LEDB,LOW); // DENEYAP KART veya DENEYAP MİNİ kartı kullanılıyorsa
  //neopixelWrite(RGBLED,0,0,0);// DENEYAP KART 1A ve DENEYAP KART G kartı kullanılıyorsa
 }
}

void setup() {
  Serial.begin(115200);
  pinMode(LEDB,OUTPUT);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW başlatılamadı");
    return;
  }  
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
}
