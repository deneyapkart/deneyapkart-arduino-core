/*
 *   BasitBluetooth örneği,
 *   Bu örnek ile harici bluetooth kullanalabilmektedir. 
 *   Bluetooth modülü ile Deneyap Mini kart bağlantı gerçekleştirilmelidir. Bu aşamada şifre istenmesi durumunda “0000” ya da “1234” standart şifrelerden birinin girilmesi gerekmektedir.
 *   Bağlantı gerçekleştikten sonra seri port ekran uygulamasına girilir. Ekranda saniyede bir T3 VAKFI yazısı görülmektedir.  
 * 
*/
HardwareSerial Bluetooth(1);

void setup() {
  Serial.begin(115200);
  Bluetooth.begin(115200, SERIAL_8N1, D3, D2); //RX:DA1 ve TX:DA0
}

void loop() { //Choose Serial1 or Serial2 as required
  Bluetooth.println("T3 VAKFI");
  delay(1000);
}
