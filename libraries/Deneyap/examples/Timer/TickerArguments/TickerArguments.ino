/*
 *   TickerArguments örneği,
 *   Bu örnekte Timer ile LED yanıp sönmektedir.
*/
#include <Ticker.h>

#ifdef LEDB
#define LED_PIN   LEDB         // Deneyap Kart ve Deneyap Mini dahili LED pini
#else
#define LED_PIN   LED_BUILTIN  // Dahili RGB LED'i olan kartlar (beyaz yanar)
#endif
//#define LED_PIN   D0  // Harici LED kullanmak için üstteki tanımları silip bu satırı açın

Ticker tickerSetHigh;
Ticker tickerSetLow;

void setPin(int state) {
  digitalWrite(LED_PIN, state);
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
  // her 25 ms'de setPin(0) çağır
  tickerSetLow.attach_ms(25, setPin, 0);
  
  // her 26 ms'de setPin(0) çağır
  tickerSetHigh.attach_ms(26, setPin, 1);
}

void loop() {

}
