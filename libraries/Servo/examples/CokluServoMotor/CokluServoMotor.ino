/*
*   CokluServoMotor örneği,
*   3 adet servo motoru döndürmektedir. 1. servo motor mili 30 derece, 2. servo motor mili 60 derece, 3. servo motor mili 90 derece döndürmektedir.
*   Birden fazla servo motor bağlanıldığında attach(pin, channel) fonksiyonu içinde farklı kanal(channel) ayarlanmalıdır. 
*/
#include <Deneyap_Servo.h>      // Deneyap Servo kütüphanesi eklenmesi 
 
Servo servo1;                   // 1. servo motor için class tanımlanması
Servo servo2;                   // 2. servo motor için class tanımlanması
Servo servo3;                   // 3. servo motor için class tanımlanması

void setup() {  
  servo1.attach(D3);            // 1. servo motorun D3 pinin ve 0 kanal ayarlanması  /*attach(pin, channel=0, freq=50, resolution=12) olarak belirlenmiştir. Kullandığınız motora göre değiştirebilirsiniz */
  servo2.attach(D4,1);          // 2. servo motorun D4 pinin ve 1 kanal ayarlanması
  servo3.attach(D5,2);          // 3. servo motorun D5 pinin ve 3 kanal ayarlanması
}

void loop() { 
  servo1.write(30);             // 1. servo motorun milinin 30 derece dönmesi
  servo2.write(60);             // 2. servo motorun milinin 60 derece dönmesi
  servo3.write(90);             // 3. servo motorun milinin 90 derece dönmesi
}
