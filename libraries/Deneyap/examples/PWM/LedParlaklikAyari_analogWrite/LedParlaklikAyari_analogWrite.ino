/*
 *  LedParlaklikAyari_analogWrite örneği,
 *  Bu örnekte kartın üzerinde yer alan led parlaklığı bir döngü içinde sürekli olarak artıp azalmaktadır.
*/
#ifdef LEDB
#define LED_PIN   LEDB                              // Deneyap Kart ve Deneyap Mini Led pini (PWM cikis pini)
#endif
//#define LED_PIN   D0                              // Harici LED kullanmak için üstteki tanımı silip bu satırı açın
                                                    // LED_PIN tanımlı değilse dahili RGB LED kullanılır

uint8_t brightness = 0;                             // Ledin parlaklik ayari (0-255)
uint8_t brightStep = 5;                             // Parlaklik degisim adimi

void setup() {
}

void loop() {
  brightness += brightStep;                         // Parlaklik kademesi degistiriliyor

  if ( brightness == 0 || brightness == 255 )       // Sinir degerlerde parlaklik yonu degistiriliyor
  {
    brightStep = -brightStep;
  }

#ifdef LED_PIN
  analogWrite(LED_PIN, brightness);                 // Parlaklik degeri pin ile iliskilendiriliyor
#else
  rgbLedWrite(RGB_BUILTIN, brightness, brightness, brightness);  // Dahili RGB LED'in parlakligi (beyaz)
#endif
  
  delay(50);
}