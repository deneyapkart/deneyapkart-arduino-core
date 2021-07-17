/******************************************************************************
deneyap.cpp
Main Deneyap DevKit Library

Main functions used for read, write, pin mode etc. operations

Ozgur BOSTAN @ RFtek Electronics
ozgur.bostan@rftek.com.tr
April 08, 2020

2020 Copyright (c) RFtek Electronics Ltd.  All right reserved.
******************************************************************************/

#include <Arduino.h>
#include "deneyap.h"

// /**
//   * @brief  Pin mode selection controlled by io-expander
//   * @param  Pin number (GPIO21-GPIO24), direction (INPUT/GPIO_INPUT, OUTPUT/GPIO_OUTPUT)
//   * @retval None
//   */
// void pinMode(uint16_t pinNumber, uint16_t pinMode)
// {
// 	if(pinMode == INPUT)
// 		pinDirConfig(pinNumber, GPIO_INPUT);
// 	else if(pinMode == OUTPUT)
// 		pinDirConfig(pinNumber, GPIO_OUTPUT);
// 	else
// 		pinDirConfig(pinNumber, pinMode);
// }

// /**
//   * @brief  Change output pin state controlled by io-expander
//   * @param  Pin number (GPIO21-GPIO24), pin state (HIGH/PIN_HIGH, LOW/PIN_LOW)
//   * @retval None
//   */
// void digitalWrite(uint16_t pinNumber, uint16_t pinState)
// {
//   writePin((uint8_t)pinNumber, (uint8_t)pinState);
// }

// /**
//   * @brief  Read input pin state controlled by io-expander
//   * @param  Pin number (GPIO21-GPIO24)
//   * @retval None
//   */
// uint8_t digitalRead(uint16_t pinNumber)
// {
//   return readPin((uint8_t)pinNumber);
// }

/**
  * @brief  Change built-in red led (RGB) state
  * @param  Pin state (HIGH/PIN_HIGH, LOW/PIN_LOW)
  * @retval None
  */
void writeRedLed(uint8_t state)
{
	if(state == HIGH || state == PIN_HIGH)
		digitalWrite(LEDR, PIN_LOW);
	else if(state == LOW || state == PIN_LOW)
		digitalWrite(LEDR, PIN_HIGH);
}

/**
  * @brief  Change built-in green led (RGB) state
  * @param  Pin state (HIGH/PIN_HIGH, LOW/PIN_LOW)
  * @retval None
  */
void writeGreenLed(uint8_t state)
{
	if(state == HIGH || state == PIN_HIGH)
		digitalWrite(LEDG, PIN_LOW);
	else if(state == LOW || state == PIN_LOW)
		digitalWrite(LEDG, PIN_HIGH);
}

/**
  * @brief  Change built-in blue led (RGB) state
  * @param  Pin state (HIGH/PIN_HIGH, LOW/PIN_LOW)
  * @retval None
  */
void writeBlueLed(uint8_t state)
{
	if(state == HIGH || state == PIN_HIGH)
		digitalWrite(LEDB, PIN_LOW);
	else if(state == LOW || state == PIN_LOW)
		digitalWrite(LEDB, PIN_HIGH);
}

/**
  * @brief  Read built-in general purpose button state
  * @param  None
  * @retval State of the pin
  */
uint8_t readGenPurButton(void)
{
  return digitalRead(BUILTIN_KEY);
}

// /**
//   * @brief  Enable built-in 1.2VDC regulator for camera module
//   * @param  Pin state (REG_ENABLE, REG_DISABLE)
//   * @retval None
//   */
// void regulator1Enable(uint8_t state)
// {
//   writePin(EXP_REG_EN1, state);
// }

// /**
//   * @brief  Enable built-in 2.8VDC regulator for camera module
//   * @param  Pin state (REG_ENABLE, REG_DISABLE)
//   * @retval None
//   */
// void regulator2Enable(uint8_t state)
// {
//   writePin(EXP_REG_EN2, state);
// }

// /**
//   * @brief  Enable built-in camera module
//   * @param  Pin state (CAM_ENABLE, CAM_DISABLE)
//   * @retval None
//   */
// void cameraEnable(uint8_t state)
// {
//   writePin(EXP_CAM_PWDN, state);
// }

// /**
//   * @brief  Change GPIO21 pin state
//   * @param  Pin state (HIGH/PIN_HIGH, LOW/PIN_LOW)
//   * @retval None
//   */
// void writeGPIO21(uint8_t state)
// {
//   writePin(GPIO21, state);
// }

// /**
//   * @brief  Change GPIO22 pin state
//   * @param  Pin state (HIGH/PIN_HIGH, LOW/PIN_LOW)
//   * @retval None
//   */
// void writeGPIO22(uint8_t state)
// {
//   writePin(GPIO22, state);
// }

// /**
//   * @brief  Change GPIO23 pin state
//   * @param  Pin state (HIGH/PIN_HIGH, LOW/PIN_LOW)
//   * @retval None
//   */
// void writeGPIO23(uint8_t state)
// {
//   writePin(GPIO23, state);
// }

// /**
//   * @brief  Change GPIO24 pin state
//   * @param  Pin state (HIGH/PIN_HIGH, LOW/PIN_LOW)
//   * @retval None
//   */
// void writeGPIO24(uint8_t state)
// {
//   writePin(GPIO24, state);
// }

// /**
//   * @brief  Read GPIO21 pin state
//   * @param  None
//   * @retval Pin state
//   */
// uint8_t readGPIO21(void)
// {
//   return readPin(GPIO21);
// }

// /**
//   * @brief  Read GPIO22 pin state
//   * @param  None
//   * @retval Pin state
//   */
// uint8_t readGPIO22(void)
// {
//   return readPin(GPIO22);
// }

// /**
//   * @brief  Read GPIO23 pin state
//   * @param  None
//   * @retval Pin state
//   */
// uint8_t readGPIO23(void)
// {
//   return readPin(GPIO23);
// }

// /**
//   * @brief  Read GPIO24 pin state
//   * @param  None
//   * @retval Pin state
//   */
// uint8_t readGPIO24(void)
// {
//   return readPin(GPIO24);
// }

/**
  * @brief  Configure and initialize camera
  * @param  None
  * @retval Pin state
  */
void cameraInit(void)
{
  camera_config_t config;
  config.ledc_channel   = LEDC_CHANNEL_0;
  config.ledc_timer     = LEDC_TIMER_0;
  config.pin_d0         = CAMD2;
  config.pin_d1         = CAMD3;
  config.pin_d2         = CAMD4;
  config.pin_d3         = CAMD5;
  config.pin_d4         = CAMD6;
  config.pin_d5         = CAMD7;
  config.pin_d6         = CAMD8;
  config.pin_d7         = CAMD9;
  config.pin_xclk       = CAMXC;
  config.pin_pclk       = CAMPC;
  config.pin_vsync      = CAMV;
  config.pin_href       = CAMH;
  config.pin_sscb_sda   = CAMSD;
  config.pin_sscb_scl   = CAMSC;
  config.pin_pwdn       = -1;
  config.pin_reset      = -1;
  config.xclk_freq_hz   = 15000000;
  config.pixel_format   = PIXFORMAT_JPEG;
  //init with high specs to pre-allocate larger buffers
  if(psramFound()){
    config.frame_size   = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count     = 2;
  } else {
    config.frame_size   = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count     = 1;
  }

  // Camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  sensor_t * s = esp_camera_sensor_get();
  // Drop down frame size for higher initial frame rate
  s->set_framesize(s, FRAMESIZE_QVGA);
}
