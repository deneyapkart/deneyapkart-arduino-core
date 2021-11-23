
#include <Ticker.h>

#define LED_PIN LEDB

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
  digitalWrite(LED_PIN, LOW);  // geçiş yaptıktan (toggling) sonra LED'in açık olduğundan emin olun (pin LOW = led AÇIK)
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  toggler.attach(togglePeriod, toggle);
  changer.once(30, change);
}

void loop() {
  
}
