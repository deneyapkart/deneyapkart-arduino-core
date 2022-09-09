#ifndef DENEYAP_H
#define DENEYAP_H

#include <stdint.h>
#include "esp_camera.h"

/* PIN DEFINITIONS */

// Digital pins
#if defined (ARDUINO_DYDK) || defined (ARDUINO_DYDK1A)
#define D0	(uint8_t)(23)
#define D1	(uint8_t)(22)
#define D2	(uint8_t)(1)
#define D3	(uint8_t)(3)
#define D4	(uint8_t)(21)
#define D5	(uint8_t)(19)
#define D6	(uint8_t)(18)
#define D7	(uint8_t)(5)
#define D8	(uint8_t)(0)
#define D9	(uint8_t)(2)
#define D10	(uint8_t)(4)
#define D11	(uint8_t)(15)
#define D12	(uint8_t)(13)
#define D13	(uint8_t)(12)
#define D14	(uint8_t)(14)
#define D15	(uint8_t)(27)
#elif defined (ARDUINO_DYM)
#define D0	(uint8_t)(44)
#define D1	(uint8_t)(43)
#define D2	(uint8_t)(42)
#define D3	(uint8_t)(41)
#define D4	(uint8_t)(40)
#define D5	(uint8_t)(39)
#define D6	(uint8_t)(38)
#define D7	(uint8_t)(37)
#define D8	(uint8_t)(36)
#define D9	(uint8_t)(26)
#define D10	(uint8_t)(21)
#define D11	(uint8_t)(18)
#define D12	(uint8_t)(17)
#define D13	(uint8_t)(0)
#define D14	(uint8_t)(35)
#define D15	(uint8_t)(34)
#define D16	(uint8_t)(33)
#elif defined (ARDUINO_DYG)
#define D0	(uint8_t)(21)
#define D1	(uint8_t)(20)
#define D2	(uint8_t)(9)
#define D3	(uint8_t)(10)
#define D4	(uint8_t)(8)
#define D5	(uint8_t)(7)
#define D6	(uint8_t)(2)
#endif

// Analog input pins
#if defined (ARDUINO_DYDK) || defined (ARDUINO_DYDK1A)
#define A0	(uint8_t)(36)
#define A1	(uint8_t)(39)
#define A2	(uint8_t)(34)
#define A3	(uint8_t)(35)
#define A4	(uint8_t)(32)
#define A5	(uint8_t)(33)
#elif defined (ARDUINO_DYM)
#define A0	(uint8_t)(8)
#define A1	(uint8_t)(9)
#define A2	(uint8_t)(10)
#define A3	(uint8_t)(11)
#define A4	(uint8_t)(12)
#define A5	(uint8_t)(13)
#define A6	(uint8_t)(16)
#elif defined (ARDUINO_DYG)
#define A0	(uint8_t)(0)
#define A1	(uint8_t)(1)
#define A2	(uint8_t)(3)
#define A3	(uint8_t)(4)
#define A4	(uint8_t)(5)
#define A5	(uint8_t)(6)
#endif

// Analog output pins
#if defined (ARDUINO_DYDK) || defined (ARDUINO_DYDK1A)
#define DAC1	(uint8_t)(25)
#define DAC2	(uint8_t)(26)
#elif defined (ARDUINO_DYM)
#define DA0	D12
#define DA1	D11
#endif

// I2C pins
#if defined (ARDUINO_DYDK) || defined (ARDUINO_DYDK1A)
#define SDA	D10
#define SCL	D11
#elif defined (ARDUINO_DYM)
#define SD	D8
#define SC	D7
#elif defined (ARDUINO_DYG)
#define SDA	D4
#define SCL	D6
#endif

// SPI pins
#if defined (ARDUINO_DYDK) || defined (ARDUINO_DYDK1A)
#define MOSI	D7
#define MISO	D6
#define SCK	D5
#define SS	D4
#elif defined (ARDUINO_DYM)
#define MO	D4
#define MI	D5
#define MC	D6
#define SS	D10
#elif defined (ARDUINO_DYG)
#define MO	A5
#define MI	A4
#define MC	A3
#define SS	D5
#endif

// UART pins
#if defined (ARDUINO_DYDK) || defined (ARDUINO_DYDK1A)
#define TX	D2
#define RX	D3
#elif defined (ARDUINO_DYM)
#define TX	D0
#define RX	D1
#elif defined (ARDUINO_DYG)
#define TX	D1
#define RX	D0
#endif

// PWM pins
#if defined (ARDUINO_DYDK) || defined (ARDUINO_DYDK1A)
#define PWM0	D0
#define PWM1	D1
#elif defined (ARDUINO_DYM)
#define P0	D2
#define P1	D3
#elif defined (ARDUINO_DYG)
#define PWM0	A0
#define PWM1	A1
#define PWM2	A2
#endif

// Capacitive-Sensing pins
#if defined (ARDUINO_DYDK) || defined (ARDUINO_DYDK1A)
#define T0	A4
#define T1	A5
#define T2	D15
#define T3	D14
#define T4	D13
#define T5	D12
#elif defined (ARDUINO_DYM)
#define T0	A0
#define T1	A1
#define T2	A2
#define T3	A3
#define T4	A4
#define T5	A5
#endif

// Camera pins
#if defined (ARDUINO_DYDK) || defined (ARDUINO_DYDK1A)
#define CAMSD	A5
#define CAMSC	DAC1
#define CAMD2	D5
#define CAMD3	D1
#define CAMD4	D0
#define CAMD5	D4
#define CAMD6	D6
#define CAMD7	DAC2
#define CAMD8	A3
#define CAMD9	A2
#define CAMPC	D7
#define CAMXC	A4
#define CAMH	A1
#define CAMV	A0
#endif

#if defined (ARDUINO_DYDK)
// Microphone pins
#define MICD	D13
#define MICC	D12

// IMU pins
#define IMUSD	D10
#define IMUSC	D11
#endif

#if defined (ARDUINO_DYDK1A)
//SD Card pins
#define SDMI	D9
#define SDMO	D14
#define SDCS	D13
#define SDCK	D15
#endif

// Built-in leds and button
#if defined (ARDUINO_DYDK)
#define LEDR	D3
#define LEDG	D2
#define LEDB	D10
#define GPKEY	(uint8_t)(0)
#define BOOT	(uint8_t)(0)
#elif defined (ARDUINO_DYDK1A)
#define RGBLED	(uint8_t)(13)
#define GPKEY	(uint8_t)(0)
#define BOOT	(uint8_t)(0)
#elif defined (ARDUINO_DYM)
#define LEDR	(uint8_t)(34)
#define LEDG	(uint8_t)(33)
#define LEDB	(uint8_t)(35)
#define GPKEY	(uint8_t)(0)
#define BT	(uint8_t)(0)
#elif defined (ARDUINO_DYG)
#define RGBLED	(uint8_t)(10)
#define GPKEY	(uint8_t)(9)
#define BT	(uint8_t)(9)
#endif
#define BUILTIN_KEY	GPKEY

/* GPIO MODES */
#define GPIO_INPUT	(0x01)
#define GPIO_OUTPUT	(0x00)
#define PIN_HIGH	(0x01)
#define PIN_LOW	(0x00)
#define BUTTON_PRESSED	(0x00)

/* FUNCTION PROTOTYPES */
//uint8_t digitalRead(uint16_t pinNumber);
void writeRedLed(uint8_t state);
void writeGreenLed(uint8_t state);
void writeBlueLed(uint8_t state);
uint8_t readGenPurButton(void);

#if defined (ARDUINO_DYDK) || defined (ARDUINO_DYDK1A)
void cameraInit(void);
// Function declaration for CameraStream sketch defined in "app_httpd.cpp"
void startCameraServer();
#endif

#endif /* DENEYAP_H */
