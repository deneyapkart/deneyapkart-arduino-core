/*
 *  Bluetooth SeriTerminalBle örneği,
 *  Bu uygulama örneği için telefona  Serial Bluetooth Terminal programı indirilmesi gerekmektedir.
 *  Yazılım karta yüklendikten sonra hem seri port ekrandan telefon uygulamasına hem de telefon uygulamasından seri port ekrane karakter verisi gönderilebilmektedir.
 *  Bu kütüphane sadece Deneyap Kart ve Deneyap Kart 1A desteklemektedir.
 *  Deneyap Mini Kartında dahili Bluetooth haberleşme özelliği bulunmamaktadır.  
*/
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;                                                 // Bluetooth icin class tanimlama

void setup() {            
  Serial.begin(115200);                                                   // Seri haberlesme baslatildi
  SerialBT.begin("DeneyapKart"); // Bluetooth yayin ismi                  // Bluetooth haberlesme kanali acildi
  Serial.println("\nCihaz yayin yapmaya basladi, eslesme yapilabilir!");  
}

void loop() {
  while(Serial.available() == 0 && SerialBT.available() == 0);            // Veri bekleniyor 
  if (Serial.available() > 0) 
  {
    SerialBT.write(Serial.read());                                        // Veri yaziliyor (seri port ekran --> Bluetooth)
  }
  if (SerialBT.available() > 0) 
  {
    Serial.write(SerialBT.read());                                        // Veri yaziliyor (Bluetooth --> seri port ekran)
  }
  delay(20);
}
