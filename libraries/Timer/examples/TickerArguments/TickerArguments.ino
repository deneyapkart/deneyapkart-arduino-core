#include <Ticker.h>

#define LED_PIN LEDG

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
  
  // her 25 ms'de setPin(0) çağır
  tickerSetHigh.attach_ms(25, setPin, 1);
}

void loop() {

}
