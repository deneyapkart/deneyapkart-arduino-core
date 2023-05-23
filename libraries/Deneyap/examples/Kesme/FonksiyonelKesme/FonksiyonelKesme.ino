/*
 *  FonksiyonelKesme (interrupt) örneği,
 *  Bu uygulamada FunctionalInterrupt kütüphanesi kullanarak kesme işlemleri gerçekleştirilmiştir. 
 *  Örnekte karttaki butona veya harici bağlanan bir botuna basıldığında interrupt ile butona kaç defa basıldığı bilgisi seri port ekranına yazdırmaktadır. 
 */
#include <FunctionalInterrupt.h>

#define BUTTON1 12
#define BUTTON2 GPKEY   // Genel amacli buton "BUT"  tanımlandı.

class Button
{
public:
  Button(uint8_t reqPin) : PIN(reqPin){
     pinMode(PIN, INPUT_PULLUP);
     attachInterrupt(PIN, std::bind(&Button::isr,this), FALLING);
  };
  ~Button() {
    detachInterrupt(PIN);
  }

  void ARDUINO_ISR_ATTR isr() {
    numberKeyPresses += 1;
    pressed = true;
  }

  void checkPressed() {
    if (pressed) {
      Serial.printf("GPIO%u pinine bağlı butona %u kez basıldı\n", PIN, numberKeyPresses);
      pressed = false;
    }
  }

private:
   const uint8_t PIN;
     volatile uint32_t numberKeyPresses;
     volatile bool pressed;
};

Button button1(BUTTON1);
Button button2(BUTTON2);

void setup() {
     Serial.begin(115200);
}

void loop() {
   button1.checkPressed();
   button2.checkPressed();
}
