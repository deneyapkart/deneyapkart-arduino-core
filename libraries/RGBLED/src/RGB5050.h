#ifndef _RGB5050_h
#define _RGB5050_h

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "Arduino.h"
#include <stdint.h>

#include "esp32-hal.h"
#include "deneyap.h"

enum LED_TYPE
{           //G  R  B
  TYPE_GRB = 0x12,  //01 00 10
};

class RGB5050
{
protected:
  
  uint16_t ledCounts;
  uint8_t pin;
  uint8_t br;
  uint8_t rmt_chn;
  
  uint8_t rOffset;
  uint8_t gOffset;
  uint8_t bOffset;
  
  float realTick;
  rmt_reserve_memsize_t rmt_mem;
  rmt_data_t *led_data;
  rmt_obj_t* rmt_send = NULL;

public:
  RGB5050(uint16_t n = 1, uint8_t pin_gpio = RGBLED, uint8_t chn = 0, LED_TYPE t = TYPE_GRB);

    ~RGB5050();

    esp_err_t  random();

  bool begin();
  void setLedCount(uint16_t n);
  void setLedType(LED_TYPE t);
  void setBrightness(uint8_t brightness);

  esp_err_t set_pixel(int index, uint8_t r, uint8_t g, uint8_t b);
  
  esp_err_t setLedColorData(int index, uint32_t rgb);
  esp_err_t setLedColorData(int index, uint8_t r, uint8_t g, uint8_t b);

  esp_err_t setLedColor(int index, uint32_t rgb);
  esp_err_t setLedColor(int index, uint8_t r, uint8_t g, uint8_t b);

  esp_err_t setAllLedsColorData(uint32_t rgb);
  esp_err_t setAllLedsColorData(uint8_t r, uint8_t g, uint8_t b);

  esp_err_t setAllLedsColor(uint32_t rgb);
  esp_err_t setAllLedsColor(uint8_t r, uint8_t g, uint8_t b);

  esp_err_t show();

  uint32_t Wheel(byte pos);
  uint32_t hsv2rgb(uint32_t h, uint32_t s, uint32_t v);
};

#endif 
