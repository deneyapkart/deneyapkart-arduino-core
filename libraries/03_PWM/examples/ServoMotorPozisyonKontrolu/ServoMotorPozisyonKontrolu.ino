#include "deneyap.h"
#include "ServoESP32.h"

#define servoPin PWM0                                           // PWM pini tanimlamasi
#define potentiometerPin A0                                     // Analog giris pini tanimlamasi

Servo servo1;                                                   // Class'tan nesne turetimi
int incomingByte = 0;                                           // Gelen veriyi tutacak degisken tanimi

void setup() {
    Serial.begin(115200);                                       // Seri haberlesme baslatildi
    servo1.attach(servoPin);                                    // Servo baglantisi yapilacak pin ile iliski kuruldu
}

void loop() {
  if (Serial.available() > 0)                                   // Seri terminalden veri bekleniyor
  {
    // read the incoming byte:  
    incomingByte = Serial.parseInt();                           // Seri terminalden asagida belirtilen sinir degerler arasi veri girisi yapilir
    int servoPosition = map(incomingByte, 0, 150, 30, 180);
    servo1.write(servoPosition);                                // Pozisyon kontrolu yapliyor
    Serial.println(servoPosition);                              // Motor pozisyonuna iliskin derece bilgisi seri terminale yaziliyor
    delay(20);
  }    
}
