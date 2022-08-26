/*
 *   ImuVeriOkuma örneği,
 *   Uygulamada Deneyap kart üzerinde yer alan IMU ile Ortamın sıcaklığı Derece ve Fahrenhayt cinsinde seri terminale yazdırmaktadır. 
 *   Daha sonra IMU'daki akselerometre ile X-eksen, Y-eksen ve Z-eksen verileri seri terminale yazdırmaktadır.
 *   IMU'daki Jirometre (Gyrometer) ile X-eksen, Y-eksen ve Z-eksen bilgileri seri terminale yazdırmaktadır.
 *   
 *   Bu uygulama Deneyap Kart 1A, Deneyap Mini ve DENEYAP G Kartları ile gerçekleştirilmek istenirse harici IMU bağlanmalıdır ve gerekli bağlantı bilgileri değiştirilmelidir.
 *   
 */
#include "lsm6dsm.h"

#define delayms 700

LSM6DSM IMU;                                    // IMU icin Class tanimlamasi

void setup() {
  Serial.begin(115200);                         // Seri haberlesme baslatildi
  IMU.begin();                                  // IMU ayarlari konfigure edildi
}

void loop() {
  Serial.println("\nAkselerometre degerleri\n");
  Serial.print("X ekseni\t: ");
  Serial.println(IMU.readFloatAccelX());        // X-eksen akselerometre verisi okuma
  delay(delayms);
  Serial.print("Y ekseni\t: ");
  Serial.println(IMU.readFloatAccelY());        // Y-eksen akselerometre verisi okuma
  delay(delayms);
  Serial.print("Z ekseni\t: ");
  Serial.println(IMU.readFloatAccelZ());        // Z-eksen akselerometre verisi okuma
  delay(delayms);

  Serial.println("\nGyro degerleri\n");
  Serial.print("X ekseni\t: ");
  Serial.println(IMU.readFloatGyroX());         // X-eksen gyro verisi okuma
  delay(delayms);
  Serial.print("Y ekseni\t: ");
  Serial.println(IMU.readFloatGyroY());         // Y-eksen gyro verisi okuma
  delay(delayms);
  Serial.print("Z ekseni\t: ");
  Serial.println(IMU.readFloatGyroZ());         // Z-eksen gyro verisi okuma
  delay(delayms);

  Serial.println("\nSicaklik degerleri\n");
  Serial.print("Celsius \t: ");
  Serial.println(IMU.readTempC());              // Sicaklik verisi okuma (Celsius)
  delay(delayms);
  Serial.print("Fahrenheit \t: ");
  Serial.println(IMU.readTempF());              // Sicaklik verisi okuma (Fahrenheit)
  delay(delayms);
}
