/*
 *  MobilRobotKontrolAkselerometre örneği
 *  Bu örnek uygulama ile MobilRobotSurucu örneği ile iki Deneyap geliştirme kartı haberleşmektedir.
 *  Deneyap Karttaki dahili IMU'dan alınan Akselerometre verisi diğer Deneyap geliştirme kartına gönderilmektedir.
 *  Bu uygulama Deneyap Kart 1A ve Deneyap Kart G Kartları ile gerçekleştirilmek istenirse harici imu sensörü bağlanmalıdır ve kodda gerekli değişiklikler yapılmalıdır.
*/
#include "lsm6dsm.h"  // Deneyap Kart dahili IMU kütüphanesinin eklenmesi
#include "WiFi.h"
#include "esp_now.h"

/* Alıcı kartın MAC adresi bulmak için;
Examples > Mikrodenetleyici > MacAdresiBulma
Örnekler > Mikrodenetleyici > MacAdresiBulma
seri port ekrane yazılan adres 44:17:93:4C:58:00 */ 
uint8_t broadcastAddress[] = {0x44, 0x17, 0x93, 0x4C, 0x58, 0x00}; // ALICI kartın MAC adresi

typedef struct struct_message {
    float accel_x;
    float accel_y;
    float accel_z;
} struct_message;

LSM6DSM IMU;
struct_message imuData;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  Serial.begin(115200);
  IMU.begin();
  WiFi.mode(WIFI_MODE_STA);
  
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  imuData.accel_x = IMU.readFloatAccelX();
  Serial.print("accel_x: ");
  Serial.println(imuData.accel_x);
  delay(50);
  imuData.accel_y = IMU.readFloatAccelY();
  Serial.print("accel_y: ");
  Serial.println(imuData.accel_y);
  delay(50);
  imuData.accel_z = IMU.readFloatAccelZ();
  Serial.print("accel_z: ");
  Serial.println(imuData.accel_z);
  delay(50);

  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &imuData, sizeof(imuData));

  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }

  delay(200);
}
