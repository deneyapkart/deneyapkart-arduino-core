/*
 *   TickerArguments örneği,
 *   Bu örnekte Timer ile LED yanıp sönmektedir.
*/
#include <Ticker.h>

#define LED_PIN   LEDB  // Deneyap Kart ve Deneyap Mini Led pini 
//#define LED_PIN   D0  // Deneyap Kart 1A ve Deneyap Kart G için harici pin takılmalıdır

Ticker tickerSetHigh;
Ticker tickerSetLow;

void setPin(int state) {
  digitalWrite(LED_PIN, state);
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(1, LOW);
  
  // her 25 ms'de setPin(0) çağır
  tickerSetLow.attach_ms(25, setPin, 0);
  
  // her 26 ms'de setPin(0) çağır
  tickerSetHigh.attach_ms(26, setPin, 1);
}

void loop() {

}
