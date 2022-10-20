/*
*************************************************************************************************
@file         Deneyap_Servo.cpp
@mainpage     Deneyap Servo Arduino library source file
@maintainer   RFtek Electronics <techsupport@rftek.com.tr>
@version      v1.0.0
@date         October 20, 2022
@brief        Includes functions to control servo motor Arduino library 
              for Deneyap Development Boards
*************************************************************************************************
*/

#include "Deneyap_Servo.h"

/**
 * @brief   attaches the given pin, channel, freq, resolution
 * @param   @pin : servo pin
 *          @channel : channel of pwm
 *          @freq : frequency of pwm
 *          @resolution : range is 1-14 bits (1-20 bits for ESP32)
 * @retval  None
**/
void Servo::attach(int pin, int channel, int freq, int resolution) {
  _channel = channel;
  ledcSetup(_channel, freq, resolution);   
  ledcAttachPin(pin, channel);
  ledcWrite(_channel, FIRSTDUTY);
}

/**
 * @brief   writes servo value 0-180 as degree
 * @param   @value: servo value 0-180 as degree
 * @retval  None
**/
void Servo::write(int value) {
  if(value < 0) value = 0;
  if(value > 180) value = 180; 
  int servoValue = (value - SERVOMIN) * (DUTYCYLEMAX - DUTYCYLEMIN) / (SERVOMAX - SERVOMIN) + DUTYCYLEMIN; // mapping to SERVOMIN-SERVOMAX values from DUTYCYLEMIN-DUTYCYLEMAX values
  ledcWrite(_channel, servoValue); // _channel select servoValue(duty) to be set for selected channel
}