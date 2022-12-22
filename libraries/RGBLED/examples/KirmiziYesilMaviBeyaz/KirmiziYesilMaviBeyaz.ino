/*
 *   Adreslenebilir RGB LED ile Kırmızı, Yeşil, Mavi, Beyaz renklerini yakma örneği,
 *   
 *   Bu örnekte Adreslenelibilir RGB LED dahili olan Deneyap Geliştirme Kartlarındaki RGB LED sırasıyla Kırmızı, Yeşil, Mavi, Beyaz 
 *   renklerini 1 saniye aralıklarla yakmaktadır.
 *   
 *   Deneyap Kart ve Deneyap Mini Kart ile çalışması için harici Adreslenelibilir RGB LED bağlanması gerekmektedir.
*/
#include "RGB5050.h"

RGB5050 rgb;

byte renkler[5][3] = { {128, 0, 0},     //kırmızı   Parlaklık değeri 128 seçilmiştir. 0-255 arası parlaklık değeri verilmektedir. 
                       {0, 128, 0},     //yeşil
                       {0, 0, 128},     //mavi
                       {128, 128, 128}, //beyaz
                       {0, 0, 0} };     //renk yok

void setup() {
  rgb.begin();
}

void loop() {
  for (int i = 0; i < 5; i++) {
    rgb.setLedColorData(0, renkler[i][0], renkler[i][1], renkler[i][2]);
    rgb.show();
    delay(1000);
  }  
}
