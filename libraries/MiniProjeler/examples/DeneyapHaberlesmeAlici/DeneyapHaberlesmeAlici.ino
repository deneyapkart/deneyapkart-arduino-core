/*
 *   İki Deneyap kartının haberleşmesi örneği,
 *   Bu örnekte kullandığınız verici karttan gelen buton durumuna göre led yanacaktır.
 * 
 */
#include "WiFi.h"
#include "esp_now.h"
/*  DENEYAP 1A kullanılırsa 
#include "RGB5050.h"
RGB5050 rgb; */

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
  digitalWrite(LEDB,HIGH);
  /*  DENEYAP 1A kullanılırsa 
   rgb.setLedColorData(0, 255, 0, 255);
   rgb.show(); */
 }else{
  digitalWrite(LEDB,LOW);
  /*  DENEYAP 1A kullanılırsa 
   rgb.setLedColorData(0, 0, 0, 0);
   rgb.show();*/
 }
}

void setup() {
  Serial.begin(115200);
  pinMode(LEDB,OUTPUT);
  /*  DENEYAP 1A kullanılırsa
  rgb.begin();
  rgb.setBrightness(10); */
  
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW başlatılamadı");
    return;
  }  
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
}
