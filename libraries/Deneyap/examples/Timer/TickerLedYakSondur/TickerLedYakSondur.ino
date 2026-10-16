/*
 *   TickerLedYakSondur örneği,
 *   Bu örnekte Timer ile LED yanıp sönmektedir.
*/
#include <Ticker.h>

#ifdef LEDB
#define LED_PIN   LEDB         // Deneyap Kart ve Deneyap Mini dahili LED pini
#else
#define LED_PIN   LED_BUILTIN  // Dahili RGB LED'i olan kartlar (beyaz yanar)
#endif
//#define LED_PIN   D0  // Harici LED kullanmak için üstteki tanımları silip bu satırı açın

#ifdef ARDUINO_DYDK
#define LED_ACIK  LOW   // Deneyap Kart: dahili LED LOW ile yanar
#else
#define LED_ACIK  HIGH  // Diğer kartlar ve harici LED: HIGH ile yanar
#endif

Ticker blinker;
Ticker toggler;
Ticker changer;
float blinkerPace = 0.1;  //saniye
const float togglePeriod = 5; //saniye

void change() {
  blinkerPace = 0.5;
}

void blink() {
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}

void toggle() {
  static bool isBlinking = false;
  if (isBlinking) {
    blinker.detach();
    isBlinking = false;
  }
  else {
    blinker.attach(blinkerPace, blink);
    isBlinking = true;
  }
  digitalWrite(LED_PIN, LED_ACIK);  // geçiş yaptıktan (toggling) sonra LED'in açık olduğundan emin olun
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  toggler.attach(togglePeriod, toggle);
  changer.once(30, change);
}

void loop() {
  
}
