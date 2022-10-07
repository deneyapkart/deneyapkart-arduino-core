/*
 *  ServoMotorPozisyonKontrolu örneği,
 *  Bu örnekte 180 derece açıyla çalışan servo motor seri port ekranına yazılan derece açısı kadar motor dönüş yapmaktadır.
 *  "ServoESP32" kütüphanesi Deneyap Kart ve Deneyap Kart 1A ile çalışmaktadır. 
*/
#include "ServoESP32.h"

#define servoPin PWM0                                           // DENAYAP KART ve DENEYAP KART 1A için PWM pini tanimlamasi

Servo servo1;                                                   // Class'tan nesne turetimi
int incomingByte = 0;                                           // Gelen veriyi tutacak degisken tanimi

void setup() {
    Serial.begin(115200);                                       // Seri haberlesme baslatildi
    servo1.attach(servoPin);                                    // Servo baglantisi yapilacak pin ile iliski kuruldu
}

void loop() {
  if (Serial.available() > 0)                                   // seri port ekranden veri bekleniyor
  {
    // read the incoming byte:  
    incomingByte = Serial.parseInt();                           // seri port ekranden asagida belirtilen sinir degerler arasi veri girisi yapilir
    int servoPosition = map(incomingByte, 0, 150, 30, 180);
    servo1.write(servoPosition);                                // Pozisyon kontrolu yapliyor
    Serial.println(servoPosition);                              // Motor pozisyonuna iliskin derece bilgisi seri port ekrane yaziliyor
    delay(20);
  }    
}
