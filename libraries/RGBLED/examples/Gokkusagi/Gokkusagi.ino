/*
 *   Adreslenebilir RGB LED ile gökkuşağı renkleri yakma örneği,
 *   Bu örnekte Deneyap Kart 1A üzerindeki dahili RGB LED ile gökkuşağı renklerini yakılmaktadır.
 *   
 *   Bu uygulama Deneyap Kart 1A ile çalışmaktadır. 
 *   Deneyap Kart ve Deneyap Mini Kart ile çalışması için harici Adreslenelibilir RGB LED bağlanması gerekmektedir.
 *     
 */
#include "RGB5050.h"

RGB5050 rgb;

void setup() {
  rgb.begin();
  rgb.setBrightness(20); 
}

void loop() {
  for (int j = 0; j < 255; j += 2) {
    rgb.setLedColorData(0, rgb.Wheel(( 256 / 1 + j) & 255));
    rgb.show();
    delay(100);
  }  
}
