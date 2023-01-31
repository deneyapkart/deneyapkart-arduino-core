/*
 *   ImuVeriOkuma örneği,
 *   Uygulamada Deneyap Kart üzerinde dahili olan IMU ile akselerometreden X-eksen, Y-eksen ve Z-eksen değerlerini seri port ekranına yazdırmaktadır.
 *   Jirometreden X-eksen, Y-eksen ve Z-eksen değerlerini seri port ekranına yazdırmaktadır.
 *   ve sıcaklık değerlerini seri port ekranına yazdırmaktadır. 
 *   Bu uygulama diğer Deneyap geliştirme Kartları ile gerçekleştirilmek istenirse harici IMU bağlanmalıdır.
*/
#include "lsm6dsm.h"  // Deneyap Kart dahili IMU kütüphanesinin eklenmesi

#define delayms 700

LSM6DSM IMU;  // IMU için class tanımlanması

void setup() {
  Serial.begin(115200);  // Seri haberleşme başlatılması
  IMU.begin();           // begin(slaveAdress) fonksiyonu ile cihazların haberleşmesi başlatılması
}

void loop() {
  Serial.println("\nAkselerometre degerleri");
  Serial.print("X ekseni: ");  // X-eksen akselerometre verisi okunması
  Serial.print(IMU.readFloatAccelX());
  Serial.print("\tY ekseni: ");  // Y-eksen akselerometre verisi okunması
  Serial.print(IMU.readFloatAccelY());
  Serial.print("\tZ ekseni: ");  // Z-eksen akselerometre verisi okunması
  Serial.println(IMU.readFloatAccelZ());
  delay(delayms);

  Serial.println("\nGyro degerleri");
  Serial.print("X ekseni: ");  // X-eksen gyro verisi okunması
  Serial.print(IMU.readFloatGyroX());
  Serial.print("\tY ekseni: ");  // Y-eksen gyro verisi okunması
  Serial.print(IMU.readFloatGyroY());
  Serial.print("\tZ ekseni: ");  // Z-eksen gyro verisi okunması
  Serial.println(IMU.readFloatGyroZ());
  delay(delayms);

  Serial.println("\nSicaklik degerleri");
  Serial.print("Celsius: ");  // Sicaklik verisi okunması (Celsius)
  Serial.print(IMU.readTempC());
  Serial.print("\tFahrenheit: ");  // Sicaklik verisi okunması (Fahrenheit)
  Serial.println(IMU.readTempF());
  delay(delayms);
}