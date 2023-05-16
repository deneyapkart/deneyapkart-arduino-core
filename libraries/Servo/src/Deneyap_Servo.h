/*
*****************************************************************************
@file         Deneyap_Servo.h
@mainpage     Deneyap Servo Arduino library header file
@version      v1.0.0
@date         October 20, 2022
@brief        This file contains all function prototypes and macros
              for servo motor Arduino library for Deneyap Development Boards
*****************************************************************************
*/
#ifndef _DENEYAPSERVO_H
#define _DENEYAPSERVO_H

#include <Arduino.h>

#define DELAYMS 2000

#define PWMFREQ 50
#define PWMCHANNEL 0
#define PWMRESOLUTION 12
#define FIRSTDUTY 0

#define SERVOMIN 0
#define SERVOMAX 180
#define DUTYCYLEMIN 100
#define DUTYCYLEMAX 500

class Servo {
public:
  void attach(int pin, int channel = PWMCHANNEL, int freq = PWMFREQ, int resolution = PWMRESOLUTION);
  void write(int value);
  void writeMicroseconds(int value);
private:
  int _channel;
};

#endif /* _DENEYAPSERVO_H_ */
