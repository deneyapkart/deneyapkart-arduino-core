// Iki farkli Deneyap Kart'in esp-now protokolunu kulanarak birbirleriyle haberlesmesi (akselerometre tarafi)

#include "lsm6dsm.h"
#include "WiFiEsp32.h"
#include "esp_now.h"

//uint8_t broadcastAddress[] = {0xC8, 0x2B, 0x96, 0x8B, 0x94, 0xA8};    // Yayin ya
uint8_t broadcastAddress[] = {0xC8, 0x2B, 0x96, 0x8C, 0x97, 0xB4};    // v1.2

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
