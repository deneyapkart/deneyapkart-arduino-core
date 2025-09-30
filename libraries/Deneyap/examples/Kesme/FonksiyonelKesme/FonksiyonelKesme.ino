/*
 *  FonksiyonelKesme (interrupt) örneği,
 *  Örnekte karttaki butona veya harici bağlanan bir botuna basıldığında interrupt ile butona kaç defa basıldığı bilgisi seri port ekranına yazdırmaktadır. 
 */
#include <Arduino.h>

#define BUTTON1 12
#define BUTTON2 0

const uint32_t debounceDelay = 50;

#ifndef CORE_DK_VERSION
  #define CORE_DK_VERSION 0
#endif

#if CORE_DK_VERSION > 103013
// --- YENİ ÇEKİRDEK: LAMBDA İLE FONKSİYONEL INTERRUPT ---

volatile bool pressed1Flag = false;
volatile bool pressed2Flag = false;

uint32_t lastPressTime1 = 0;
uint32_t lastPressTime2 = 0;
uint32_t count1 = 0;
uint32_t count2 = 0;

bool waitingRelease1 = false;
bool waitingRelease2 = false;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);

  attachInterrupt(BUTTON1, []() {
    pressed1Flag = true;
  }, FALLING);

  attachInterrupt(BUTTON2, []() {
    pressed2Flag = true;
  }, FALLING);
}

void loop() {
  // BUTTON1
  if (pressed1Flag && !waitingRelease1) {
    pressed1Flag = false;
    uint32_t now = millis();
    if ((now - lastPressTime1) > debounceDelay) {
      count1++;
      Serial.printf("GPIO%u pinine bağlı butona %u kez basıldı\n", BUTTON1, count1);
      lastPressTime1 = now;
      waitingRelease1 = true;
    }
  }
  // Release bekle, tekrar basıma izin verme!
  if (waitingRelease1 && digitalRead(BUTTON1) == HIGH) {
    waitingRelease1 = false;
  }

  // BUTTON2
  if (pressed2Flag && !waitingRelease2) {
    pressed2Flag = false;
    uint32_t now = millis();
    if ((now - lastPressTime2) > debounceDelay) {
      count2++;
      Serial.printf("GPIO%u pinine bağlı butona %u kez basıldı\n", BUTTON2, count2);
      lastPressTime2 = now;
      waitingRelease2 = true;
    }
  }
  if (waitingRelease2 && digitalRead(BUTTON2) == HIGH) {
    waitingRelease2 = false;
  }
}

#else
// --- ESKİ ÇEKİRDEK: GÜVENLİ CLASS TABANLI ISR + DEBOUNCE + BASIM YÖNETİMİ ---

class Button {
public:
  Button(uint8_t reqPin) : PIN(reqPin) {
    pinMode(PIN, INPUT_PULLUP);
    lastButtonState = digitalRead(PIN);
  }
  void begin(void (*isr)()) {
    attachInterrupt(PIN, isr, FALLING);
  }
  void checkPressed() {
    if (pressedFlag && !waitingRelease) {
      pressedFlag = false;
      uint32_t now = millis();
      if ((now - lastPressTime) > debounceDelay) {
        numberKeyPresses++;
        Serial.printf("GPIO%u pinine bağlı butona %u kez basıldı\n", PIN, numberKeyPresses);
        lastPressTime = now;
        waitingRelease = true;
      }
    }
    // Release bekle, tekrar basıma izin verme!
    if (waitingRelease && digitalRead(PIN) == HIGH) {
      waitingRelease = false;
    }
  }
  void setPressedFlag() {
    pressedFlag = true;
  }
private:
  const uint8_t PIN;
  volatile uint32_t numberKeyPresses = 0;
  volatile bool pressedFlag = false;
  bool waitingRelease = false;
  uint32_t lastPressTime = 0;
  int lastButtonState;
public:
  static Button* instance1;
  static Button* instance2;
};

Button* Button::instance1 = nullptr;
Button* Button::instance2 = nullptr;

void IRAM_ATTR isr1() {
  if(Button::instance1) Button::instance1->setPressedFlag();
}
void IRAM_ATTR isr2() {
  if(Button::instance2) Button::instance2->setPressedFlag();
}

Button button1(BUTTON1);
Button button2(BUTTON2);

void setup() {
  Serial.begin(115200);
  Button::instance1 = &button1;
  Button::instance2 = &button2;
  button1.begin(isr1);
  button2.begin(isr2);
}

void loop() {
  button1.checkPressed();
  button2.checkPressed();
}
#endif
