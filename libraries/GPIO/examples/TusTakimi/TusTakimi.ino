/*
 *   TusTakimi örneği,
 *   TusTakımı uygulamasında 4x3 tuş takımı kullanılmıştır. Tuş takımında basılan tuşu seri port ekranına yazdırmaktadır. 
 *
 *  ==============================================================================
 *    Bu uygulama örneği için "Keypad by Mark Stanley, Alexander Brevig" kütüphanesi indirilmelidir.  ->https://github.com/Chris--A/Keypad<-
 *    Bu uygulama örneği Keypad kütüphanesi 3.1.1 versiyonu ile yazılmıştır.
 *  ==============================================================================
*/
#include <Keypad.h>

const int satir = 4;
const int sutun = 3;

char tuslar[satir][sutun] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};

byte satir_pinleri[satir] = { D9, D7, D6, D5 };
byte sutun_pinleri[sutun] = { D4, D1, D0 };

Keypad keypad = Keypad(makeKeymap(tuslar), satir_pinleri, sutun_pinleri, satir, sutun);

void setup() {
  Serial.begin(115200);
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.println(key);
  }
}
