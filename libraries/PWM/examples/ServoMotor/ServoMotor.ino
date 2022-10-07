/*
 *   ServoMotor örneği, 
 *   Bu örnekte D8 pinine bağlı olan servo motoru 180 derecelik bir açıyla açıyla ileri geri hareket etmektedir.
 *   "ServoESP32S2" kütüphanesi Deneyap Mini Kartı için yazılmıştır.
 * 
 */
#include "ServoESP32S2.h"

#define servoPin D8 // SD pini
Servo_ESP32S2 servo ={-1, servoPin};
int position = 0;

void setup(){
  delay(200);  
  ServoESP32S2.useTimer(USE_ESP32_TIMER_NO);
  servo.servoIndex = ServoESP32S2.setupServo(servo.servo_Pins, MIN_MICROS, MAX_MICROS);
}

void loop(){   
  for (position = 0; position <= 180; position += 30){
    ServoESP32S2.setPosition(servo.servoIndex, position);
    delay(50);
  }
  for (position = 180; position >= 0; position -= 30){
    ServoESP32S2.setPosition(servo.servoIndex, position);
    delay(50);
  }
  delay(100);
}
