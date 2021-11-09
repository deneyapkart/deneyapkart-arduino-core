#ifndef DENEYAP_H
#define DENEYAP_H

#include <stdint.h>
#include "esp_camera.h"

/* PIN DEFINITIONS */
// All pins
#define	GPIO1 			(uint8_t)(36)
#define	GPIO2 			(uint8_t)(39)
#define	GPIO3			  (uint8_t)(34)
#define	GPIO4			  (uint8_t)(35)
#define	GPIO5			  (uint8_t)(32)
#define	GPIO6			  (uint8_t)(33)
#define	GPIO7			  (uint8_t)(25)
#define	GPIO8			  (uint8_t)(26)
#define	GPIO9			  (uint8_t)(27)
#define	GPIO10			(uint8_t)(14)
#define	GPIO11			(uint8_t)(12)
#define	GPIO12			(uint8_t)(13)
#define	GPIO13			(uint8_t)(23)
#define	GPIO14			(uint8_t)(22)
#define	GPIO15			(uint8_t)(21)
#define	GPIO16			(uint8_t)(19)
#define	GPIO17			(uint8_t)(18)
#define	GPIO18			(uint8_t)(5)
#define	GPIO19			(uint8_t)(0)
#define	GPIO20			(uint8_t)(2)
#define USB_TX			(uint8_t)(1)
#define USB_RX			(uint8_t)(3)
// Digital pins
#define D0 					GPIO13
#define D1 			  	GPIO14
#define D2 			  	USB_TX
#define D3 			  	USB_RX
#define D4  		 		GPIO15
#define D5 			  	GPIO16
#define D6 			  	GPIO17
#define D7 			  	GPIO18
#define D8 			  	GPIO19
#define D9 			  	GPIO20
#define D10			  	(uint8_t)(4)
#define D11			  	(uint8_t)(15)
#define D12 				GPIO12
#define D13			  	GPIO11
#define D14 				GPIO10
#define D15			  	GPIO9
// Analog input pins
#define A0 			  	GPIO1
#define A1			  	GPIO2
#define A2			  	GPIO3
#define A3			  	GPIO4
#define A4			  	GPIO5
#define A5			  	GPIO6
// Analog output pins
#define DAC1			  GPIO7
#define DAC2			  GPIO8
// I2C pins
#define COMMON_SDA  (uint8_t)(4)
#define COMMON_SCL  (uint8_t)(15)
#define SDA 			  COMMON_SDA
#define SCL 			  COMMON_SCL
// SPI pins
#define MOSI			  GPIO18
#define MISO			  GPIO17
#define SCK				  GPIO16
#define CS 				  GPIO15
// UART pins
#define TX 				  USB_TX
#define RX 				  USB_RX
// PWM pins
#define PWM0			  D0
#define PWM1			  D1
// Microphone pins
#define MICD				GPIO11
#define MICC				GPIO12
// IMU pins
#define IMUSD				COMMON_SDA
#define IMUSC				COMMON_SCL
// Camera pins
#define CAMSD 			GPIO6
#define CAMSC				GPIO7
#define CAMD2				GPIO16
#define CAMD3				GPIO14
#define CAMD4				GPIO13
#define CAMD5				GPIO15
#define CAMD6				GPIO17
#define CAMD7				GPIO8
#define CAMD8				GPIO4
#define CAMD9				GPIO3
#define CAMPC				GPIO18
#define CAMXC				GPIO5
#define CAMH				GPIO2
#define CAMV				GPIO1
// Built-in leds and button
#define LEDR				USB_RX
#define LEDG				USB_TX
#define LEDB				COMMON_SDA
#define BUILTIN_KEY	GPIO19
#define GPKEY				BUILTIN_KEY

/* GPIO MODES */
#define GPIO_INPUT      (0x01)
#define GPIO_OUTPUT     (0x00)
#define PIN_HIGH        (0x01)
#define PIN_LOW         (0x00)
#define BUTTON_PRESSED  (0x00)

/* FUNCTION PROTOTYPES */
uint8_t digitalRead(uint16_t pinNumber);
void writeRedLed(uint8_t state);
void writeGreenLed(uint8_t state);
void writeBlueLed(uint8_t state);
uint8_t readGenPurButton(void);
void cameraInit(void);
// Function declaration for CameraStream sketch defined in "app_httpd.cpp"
void startCameraServer();

#endif /* DENEYAP_H */
