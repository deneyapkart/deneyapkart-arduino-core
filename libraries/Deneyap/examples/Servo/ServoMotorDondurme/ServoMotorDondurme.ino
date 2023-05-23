/*
*   ServoMotorDondurme örneği, 
*   D9 pinine bağlanan servo motorun milinin 0-180 derece aralığında 15 derecelik adımlarla ileri geri dönmektedir. 
*/
#include <Deneyap_Servo.h>  // Deneyap Servo kütüphanesi eklenmesi

Servo myservo;  // Servo için class tanımlanması

void setup() {
  myservo.attach(D9);  // Servo motorun D9 pinine bağlanması   /*attach(pin, channel=0, freq=50, resolution=12) olarak belirlenmiştir. Kullandığınız motora göre değiştirebilirsiniz */
}

void loop() {
  for (int pos = 0; pos <= 180; pos += 15) {  // 0'dan 180 dereceye 15 derece ile gitmesi
    myservo.write(pos);                   // servo motor milinin pos değerindeki dereceye gitmesi
    delay(1000);
  }
  for (int pos = 180; pos >= 0; pos -= 15) {  // 180'dan 0 dereceye 15 derece ile gitmesi
    myservo.write(pos);                   // servo motor milinin pos değerindeki dereceye gitmesi
    delay(1000);
  }
}