/*
 *  LedParlaklikAyari_analogWrite örneği,
 *  Bu örnekte kartın üzerinde yer alan led parlaklığı bir döngü içinde sürekli olarak artıp azalmaktadır.
*/
#include "analogWrite.h"

#define LED_PIN   LEDB                              // Deneyap Kart ve Deneyap Mini Led pini (PWM cikis pini) 
//#define LED_PIN   D0                              // Deneyap Kart 1A ve Deneyap Kart G için harici pin takılmalıdır

uint8_t brightness = 0;                             // Ledin parlaklik ayari (0-255)
uint8_t brightStep = 5;                             // Parlaklik degisim adimi

void setup() {
  analogWriteChannel(LED_PIN);                      // PWM pin ayari   
}

void loop() {
  brightness += brightStep;                         // Parlaklik kademesi degistiriliyor

  if ( brightness == 0 || brightness == 255 )       // Sinir degerlerde parlaklik yonu degistiriliyor
  {
    brightStep = -brightStep;
  }

  analogWrite(LED_PIN, brightness);                 // Parlaklik degeri pin ile iliskilendiriliyor
  
  delay(50);
}
