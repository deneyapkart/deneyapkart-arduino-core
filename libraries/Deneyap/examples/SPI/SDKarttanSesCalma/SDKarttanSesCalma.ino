/*
 *  SD Karttan .wav uzantılı ses dosyasını DAC pinleri ile çalma örneği.
 *  Örnekte çalınan ses dosyaları örneğin yer aldığı klasörün içinde yer almaktadır. 
 *  seri port ekrane yazılan sayıya karşılık gelen ses dosyasını çalmaktadır.
 *  Oynatılan seslerin khz, sample değerleri farklıdır. 
 *  
 *  Deneyap Kart ve Deneyap Kart 1A kartlarını desteklemektedir. 
 *
 *  ==============================================================================
 *    Bu uygulama örneği için "AutoAnalogAudio by TMRh20" kütüphanesi indirilmelidir.  ->https://github.com/TMRh20/AutoAnalogAudio<-
 *    Bu uygulama örneği AutoAnalogAudio kütüphanesi 1.43 versiyonu ile yazılmıştır.
 *  ==============================================================================
*/
#include <SPI.h>
#include <SD.h>
#include <AutoAnalogAudio.h>

#define AUDIO_DEBUG
uint32_t adcReadings = MAX_BUFFER_SIZE;
bool doADC = false;
bool firstADC = false;

AutoAnalog aaAudio;
File myFile;

#include "WAV.h"

void setup() {
  Serial.begin(115200);
  SPI.begin();

  /* SPI.begin(D15, D9, D14, D13);  //DENEYAP KART'ta bu pinler ile kullanın
   pinMode(D9,INPUT_PULLUP);      // SCK: D15, MISO: D9, MOSI: D14, SS: D13  */

#if defined(ARDUINO_DYDK1A) || defined(ARDUINO_DYDK1Av2)
  SPI.begin(SDCK, SDMI, SDMO, SDCS);
  pinMode(SDMI, INPUT_PULLUP);
#endif

  if (!SD.begin()) {
    Serial.println("SD bağlantısı başarısız!");
  } else
    Serial.println("SD bağlantısı başarılı");
  aaAudio.begin(1, 1);
  aaAudio.autoAdjust = 0;
  aaAudio.setSampleRate(80000);
  aaAudio.dacBitsPerSample = 8;
}

uint8_t count = 0;
uint32_t printTimer = millis();

uint32_t adcTimer = 0;
bool doExtADC = false;
bool doSine = false;

uint32_t testCounter = 0;

void loop() {
  if (doADC) {
    aaAudio.getADC(adcReadings);
    if (!firstADC) {
      for (int i = 0; i < adcReadings; i++) {
        int16_t tmpVar = (int16_t)aaAudio.adcBuffer16[i] - 0x800;
        //aaAudio.dacBuffer[i] = aaAudio.adcBuffer16[i];
      }
      aaAudio.feedDAC(0, adcReadings);
    } else {
      firstADC = false;
      memset(aaAudio.dacBuffer, 0, MAX_BUFFER_SIZE);
      aaAudio.feedDAC(0, MAX_BUFFER_SIZE);
      aaAudio.feedDAC(0, MAX_BUFFER_SIZE);
    }
  }
  if (doSine) {
    aaAudio.feedDAC(0, 32);
  }
  if (Serial.available()) {
    char input = Serial.read();
    switch (input) {
      /*Ses dosyaları: https://github.com/deneyapkart/deneyapkart-arduino-core/tree/master/libraries/SPI/examples/SDKarttanSesCalma */
      case '1': playAudio("/M8b24kM.wav"); break;   // 8bit, 24khz, Mono
      case '2': playAudio("/M8b24kS.wav"); break;   // 8bit, 24khz, Stereo
      case '3': playAudio("/M8b44kST.wav"); break;  // 8bit, 44khz, Mono
      case '4': Serial.println("Tamam"); break;
    }
  }
  if (!useTasks) {
    DACC_Handler();
  }
  if (millis() - printTimer > 500) {
    printTimer = millis();
    Serial.print(".");
    count++;
    if (count >= 50) {
      count = 0;
      Serial.println("");
    }
  }
}