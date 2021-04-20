#include "deneyap.h"

#define PWM_FREQ  5000                                  // PWM frekansi
#define PWM_CH    0                                     // PWM kanal secimi (0-15)
#define LED_PIN   PWM0                                  // Led pini (PWM cikis pini) (PWM0-PWM1)
#define PWM_RES   8                                     // PWM cozunurlugu (1-16 bit) 

uint8_t ledBrightness = 0;                              // Ledin parlaklik ayari (0-255)
uint8_t fadeAmount    = 5;                              // Parlaklik degisim adimi

void setup() {
  ledcSetup(PWM_CH, PWM_FREQ, PWM_RES);                 // PWM zamanlayicisi ayarlandi 
  ledcAttachPin(LED_PIN, PWM_CH);                       // Zamanlayici led pini ile iliskilendirildi
}

void loop() {
  ledcWrite(PWM_CH, ledBrightness);                     // Parlaklik degeri set ediliyor
  ledBrightness = ledBrightness + fadeAmount;           // Parlaklik kademesi degistiriliyor

  if (ledBrightness <= 0 || ledBrightness >= 255)       // Sinir degerlerde parlaklik yonu degistiriliyor
  {
    fadeAmount = -fadeAmount;
  }
  delay(50);                                            
}
