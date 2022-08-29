/*
 *   Adreslenebilir RGB LED ile Kırmızı, Yeşil, Mavi, Beyaz renklerini yakma örneği,
 *   
 *   Bu örnekte Deneyap Kart 1A üzerindeki dahili RGB LED sırasıyla Kırmızı, Yeşil, Mavi, Beyaz 
 *   renklerini 1 saniye aralıklarla yakmaktadır.
 *   
 *   Bu uygulama Deneyap Kart 1A ve Deneyap Kart G ile çalışmaktadır. 
 *   Deneyap Kart ve Deneyap Mini Kart ile çalışması için harici Adreslenelibilir RGB LED bağlanması gerekmektedir.
 *   
 */
#include "RGB5050.h"

RGB5050 rgb;

byte renkler[5][3] = { {255, 0, 0},     //kırmızı
                       {0, 255, 0},     //yeşil
                       {0, 0, 255},     //mavi
                       {255, 255, 255}, //beyaz
                       {0, 0, 0} };     //renk yok

void setup() {
  rgb.begin();
  rgb.setBrightness(10);  
}

void loop() {
  for (int i = 0; i < 5; i++) {
    rgb.setLedColorData(0, renkler[i][0], renkler[i][1], renkler[i][2]);
    rgb.show();
    delay(1000);
  }  
}
