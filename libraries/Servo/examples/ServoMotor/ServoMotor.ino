/*
*   ServoMotor örneği,
*   D9 pinine bağlanan servo motorun mili 60 derece dönmektedir.
*/
#include <Deneyap_Servo.h>      // Deneyap Servo kütüphanesi eklenmesi
 
Servo myservo;                  // Servo için class tanımlanması

void setup() {  
  myservo.attach(D9);           // Servo motorun D9 pinine bağlanması  /*attach(pin, channel=0, freq=50, resolution=12) olarak belirlenmiştir. Kullandığınız motora göre değiştirebilirsiniz */
}

void loop() { 
  myservo.write(60);            // Servo motorun milinin 60 derece dönmesi
}