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
    SerialBT.write(Serial.read());                                        // Veri yaziliyor (Seri terminal --> Bluetooth)
  }
  if (SerialBT.available() > 0) 
  {
    Serial.write(SerialBT.read());                                        // Veri yaziliyor (Bluetooth --> Seri terminal)
  }
  delay(20);
}
