// Basit saksi sulayan su pompasi calistirma uygulamasi

#include <Arduino.h>
#include "deneyap.h"

#define NEM_SENSORU   A0
#define SU_POMPASI    D0
#define SULAMA_ESIGI  450  

uint16_t nem_degeri = 0;

void setup() {
  pinMode(NEM_SENSORU, INPUT);
  pinMode(SU_POMPASI, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  nem_degeri = analogRead(NEM_SENSORU);
  Serial.print("Nem degeri: ");
  Serial.println(nem_degeri);
  delay(250);
  
  if(nem_degeri < SULAMA_ESIGI)
    digitalWrite(SU_POMPASI, LOW);
  else
    digitalWrite(SU_POMPASI, HIGH);
}