/*
 *   İki Deneyap kartının haberleşmesi örneği,
 *   Bu örnekte kullandığınız Deneyap kartlardan kullandığınız Deneyap kartının butonuna basıldığında alıcı Deneyap kartın ledi yanacaktır.
*/
#include "WiFi.h"
#include "esp_now.h"

/* Alıcı kartın MAC adresi bulmak için;
Examples > Mikrodenetleyici > MacAdresiBulma
Örnekler > Mikrodenetleyici > MacAdresiBulma
seri port ekranına yazılan adres 44:17:93:4C:58:00 */ 
uint8_t broadcastAddress[] = {0x44, 0x17, 0x93, 0x4C, 0x58, 0x00}; // ALICI kartın MAC adresi

typedef struct struct_message {
  bool button;
} struct_message;

struct_message myData;

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Veri gönderme başarılı" : "Veri gönderme başarısız");
}

void setup() {
  Serial.begin(115200);
  pinMode(GPKEY, INPUT);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW başlatılamadı");
    return; 
  }

  esp_now_register_send_cb(OnDataSent);

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Eşleşme başarısız");
    return;
  }
}

void loop() {
  
  if (digitalRead(GPKEY) == 1) {
    myData.button = 1;
    Serial.print("Buton durumu: ");
    Serial.println(myData.button);
  }else {
    myData.button = 0;
    Serial.print("Buton durumu: ");
    Serial.println(myData.button);
  }

  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

  delay(2000);
}
