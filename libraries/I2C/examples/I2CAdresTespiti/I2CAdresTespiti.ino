/*
 *   I2CAdresTespiti örneği,
 *   Bu örnekte, karta bağlanan I2C ile haberleşen modül veya sensörlerin adresinin tespit edilmektedir. 
 *   Tespit adres seri port ekrane yazdırılmaktadır. 
 */
#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(115200);
  Serial.println("\nI2C bulucu");
}

void loop() {
  byte error, address;
  int nDevices;

  Serial.println("taranıyor...");
  nDevices = 0;
  for (address = 1; address <= 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C bulundu adres 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");
      nDevices++;
    } else if (error == 4) {
      Serial.print("Bilinmeyen hata ile karsilasildi. 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("I2C bulunamadı \n");
  else
    Serial.println("bitti\n");
  delay(1000);
}
