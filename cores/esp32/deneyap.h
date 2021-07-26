#ifndef DENEYAP_H
#define DENEYAP_H

#include <stdint.h>
#include "esp_camera.h"

#define DENEYAP_KART CONFIG_IDF_TARGET_ESP32			
#define DENEYAP_MINI CONFIG_IDF_TARGET_ESP32S2		

/* PIN DEFINITIONS */
// All pins
#if DENEYAP_KART
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
#elif DENEYAP_MINI
#define GPIO0 			(uint8_t)(0)
#define GPIO8 			(uint8_t)(8)
#define GPIO9 			(uint8_t)(9)
#define GPIO10 			(uint8_t)(10)
#define GPIO11 			(uint8_t)(11)
#define GPIO12 			(uint8_t)(12)
#define GPIO13 			(uint8_t)(13)
#define GPIO16 			(uint8_t)(16)
#define GPIO17 			(uint8_t)(17)
#define GPIO18 			(uint8_t)(18)
#define GPIO21 			(uint8_t)(21)
#define GPIO26 			(uint8_t)(26)
#define GPIO33 			(uint8_t)(33)
#define GPIO34			(uint8_t)(34)
#define GPIO35			(uint8_t)(35)
#define GPIO36 			(uint8_t)(36)
#define GPIO37 			(uint8_t)(37)
#define GPIO38 			(uint8_t)(38)
#define GPIO39 			(uint8_t)(39)
#define GPIO40 			(uint8_t)(40)
#define GPIO41 			(uint8_t)(41)
#define GPIO42 			(uint8_t)(42)
#define GPIO43			(uint8_t)(43)
#define GPIO44			(uint8_t)(44)
#define TX 					GPIO43
#define RX 					GPIO44
#endif

// Digital pins
#if DENEYAP_KART
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
#elif DENEYAP_MINI
#define D0 					GPIO44
#define D1 					GPIO43
#define D2 					GPIO42
#define D3 					GPIO41
#define D4 					GPIO40
#define D5 					GPIO39
#define D6 					GPIO38
#define D7 					GPIO37
#define D8 					GPIO36
#define D9 					GPIO26
#define D10 				GPIO21
#define D11 				GPIO18
#define D12 				GPIO17
#define D13 				GPIO0
#endif
// Analog input pins
#if DENEYAP_KART
#define A0 			  	GPIO1
#define A1			  	GPIO2
#define A2			  	GPIO3
#define A3			  	GPIO4
#define A4			  	GPIO5
#define A5			  	GPIO6
#elif DENEYAP_MINI
#define A0 			  	GPIO8
#define A1			  	GPIO9
#define A2			  	GPIO10
#define A3			  	GPIO11
#define A4			  	GPIO12
#define A5			  	GPIO13
#define A6 			  	GPIO16
#endif 
// Analog output pins
#if DENEYAP_KART
#define DAC1			  GPIO7
#define DAC2			  GPIO8
#elif DENEYAP_MINI
#define DA0			  	GPIO17
#define DA1			  	GPIO18
#endif
// I2C pins
#if DENEYAP_KART
#define COMMON_SDA  (uint8_t)(4)
#define COMMON_SCL  (uint8_t)(15)
#define SDA 			  COMMON_SDA
#define SCL 			  COMMON_SCL
#elif DENEYAP_MINI
#define SD 					GPIO36		
#define SC 					GPIO37
#endif
// SPI pins
#if DENEYAP_KART
#define MOSI			  GPIO18
#define MISO			  GPIO17
#define SCK				  GPIO16
#define CS 				  GPIO15
#elif DENEYAP_MINI
#define MO 					GPIO40
#define MI 					GPIO39
#define MC 					GPIO38
#endif
// UART pins
#if DENEYAP_KART
#define TX 				  USB_TX
#define RX 				  USB_RX
#elif DENEYAP_MINI
#define TX 					GPIO43
#define RX 					GPIO44
#endif
// PWM pins
#if DENEYAP_KART
#define PWM0			  D0
#define PWM1			  D1
#elif DENEYAP_MINI
#define P0			  	GPIO42
#define P1			  	GPIO41
#endif
#if DENEYAP_KART
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
#endif
// Built-in leds and button
#if DENEYAP_KART
#define LEDR				USB_RX
#define LEDG				USB_TX
#define LEDB				COMMON_SDA
#define BUILTIN_KEY	GPIO19
#elif DENEYAP_MINI
#define LEDR				GPIO34
#define LEDG				GPIO33
#define LEDB				GPIO35
#define BUILTIN_KEY	GPIO0
#endif
#define GPKEY				BUILTIN_KEY

/* GPIO MODES */
#define GPIO_INPUT      (0x01)
#define GPIO_OUTPUT     (0x00)
#define PIN_HIGH        (0x01)
#define PIN_LOW         (0x00)
#define BUTTON_PRESSED  (0x00)

/* FUNCTION PROTOTYPES */
//uint8_t digitalRead(uint16_t pinNumber);
void writeRedLed(uint8_t state);
void writeGreenLed(uint8_t state);
void writeBlueLed(uint8_t state);
uint8_t readGenPurButton(void);
#if DENEYAP_KART
void cameraInit(void);
// Function declaration for CameraStream sketch defined in "app_httpd.cpp"
void startCameraServer();
#endif

#endif /* DENEYAP_H */
