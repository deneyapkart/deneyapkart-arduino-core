/*
 *   Adreslenebilir RGB LED ile gökkuşağı renkleri yakma örneği,
 *   Bu örnekte Adreslenelibilir RGB LED dahili olan Deneyap Geliştirme Kartlarındaki RGB LED ile gökkuşağı renkleri yakmaktadır.
 *   
 *   Deneyap Kart ve Deneyap Mini Kart ile çalışması için harici Adreslenelibilir RGB LED bağlanması gerekmektedir.   
*/
#include "RGB5050.h"

RGB5050 rgb;

void setup() {
  rgb.begin(); 
}

void loop() {
  for (int j = 0; j < 255; j += 2) {
    rgb.setLedColorData(0, rgb.Wheel(( 256 / 1 + j) & 255));
    rgb.show();
    delay(100);
  }  
}
