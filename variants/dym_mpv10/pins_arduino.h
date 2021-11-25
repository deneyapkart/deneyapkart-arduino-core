#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <stdint.h>

#define EXTERNAL_NUM_INTERRUPTS 21
#define NUM_DIGITAL_PINS        21
#define NUM_ANALOG_INPUTS       9
#define NUM_CAPACITIVE_INPUTS   14

#define analogInputToDigitalPin(p)  (((p)<20)?(esp32_adc2gpio[(p)]):-1)
#define digitalPinToInterrupt(p)    (((p)<48)?(p):-1)
#define digitalPinHasPWM(p)         (p < 46)

static const uint8_t KEY_BUILTIN = 0;

static const uint8_t TX = 43;
static const uint8_t RX = 44;

static const uint8_t SDA = 36;
static const uint8_t SCL = 37;

static const uint8_t SS    = 21;
static const uint8_t MOSI  = 40;
static const uint8_t MISO  = 39;
static const uint8_t SCK   = 38;

static const uint8_t D0 = 44;
static const uint8_t D1 = 43;
static const uint8_t D2 = 42;
static const uint8_t D3 = 41;
static const uint8_t D4 = 40;
static const uint8_t D5 = 39;
static const uint8_t D6 = 38;
static const uint8_t D7 = 37;
static const uint8_t D8 = 36;
static const uint8_t D9 = 26;
static const uint8_t D10 = 21;
static const uint8_t D11 = 18;
static const uint8_t D12 = 17;
static const uint8_t D13 = 0;
static const uint8_t D14 = 16;
static const uint8_t D15 = 13;
static const uint8_t D16 = 12;
static const uint8_t D17 = 11;
static const uint8_t D18 = 10;
static const uint8_t D19 = 9;
static const uint8_t D20 = 8;

static const uint8_t A0 = 8;
static const uint8_t A1 = 9;
static const uint8_t A2 = 10;
static const uint8_t A3 = 11;
static const uint8_t A4 = 12;
static const uint8_t A5 = 13;
static const uint8_t A6 = 16;
static const uint8_t A7 = 17;
static const uint8_t A8 = 18;

static const uint8_t T0 = 8;
static const uint8_t T1 = 9;
static const uint8_t T2 = 10;
static const uint8_t T3 = 11;
static const uint8_t T4 = 12;
static const uint8_t T5 = 13;
static const uint8_t T6 = 14;
static const uint8_t T7 = 1;
static const uint8_t T8 = 2;
static const uint8_t T9 = 3;
static const uint8_t T10 = 4;
static const uint8_t T11 = 5;
static const uint8_t T12 = 6;
static const uint8_t T13 = 7;

static const uint8_t DAC1 = 17;
static const uint8_t DAC2 = 18;

static const uint8_t PWM0 = 42;
static const uint8_t PWM1 = 41;
static const uint8_t PWM2 = 40;
static const uint8_t PWM3 = 39;
static const uint8_t PWM4 = 38;
static const uint8_t PWM5 = 37;
static const uint8_t PWM6 = 36;
static const uint8_t PWM7 = 26;
static const uint8_t PWM8 = 21;
static const uint8_t PWM9 = 18;
static const uint8_t PWM10 = 17;
static const uint8_t PWM11 = 0;
static const uint8_t PWM12 = 16;
static const uint8_t PWM13 = 13;
static const uint8_t PWM14 = 12;
static const uint8_t PWM15 = 11;
static const uint8_t PWM16 = 10;
static const uint8_t PWM17 = 9;
static const uint8_t PWM18 = 8;
static const uint8_t PWM19 = 44;
static const uint8_t PWM20 = 43;

static const uint8_t LEDR = 34;
static const uint8_t LEDG = 33;
static const uint8_t LEDB = 35;
static const uint8_t GPKEY = 0;

#endif /* Pins_Arduino_h */
