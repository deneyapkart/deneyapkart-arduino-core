/*
*   PotServoMotorKontrol örneği,
*   A0 pinine bağlanan potansiyonometre değerine göre D9 pinine bağlanan servo motor mili dönmektedir. 
*/
#include <Deneyap_Servo.h>          // Deneyap Servo kütüphanesinin eklenmesi
   
Servo myservo;                      // Servo için class tanımlanması

int potpin = A0;                    // A0 pinine potansiyonometrenin bağlanması
int val; 

void setup() {  
  myservo.attach(D9);               // Servo motorun D9 pinine bağlanması   /*attach(pin, channel=0, freq=50, resolution=12) olarak belirlenmiştir. Kullandığınız motora göre değiştirebilirsiniz */
  pinMode(A0, INPUT);               // A0 pininin giriş olarak tanımlanması
}

void loop() { 
  val = analogRead(potpin);         // Potansiyonometre değerinin okunması
  val = map(val, 0, 4095, 0, 180);  // Potansiyonometre değerinin 0-180 aralığına dönüştürülmesi. Deneyap Mini Kartları için 4095=>8191 olarak değiştirilmelidir.
  myservo.write(val);               // Servo motor milinin dönüştürülen değere göre döndürülmesi
  delay(15);
}