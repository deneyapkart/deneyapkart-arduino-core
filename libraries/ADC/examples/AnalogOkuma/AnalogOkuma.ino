uint16_t adcHamVeri = 0;                                // Ham veri icin degisken
float adcVolDeg = 0;                                    // Voltaj donusumu icin degisken

void setup() {
  Serial.begin(115200);                                 // Seri haberlesme baslatildi
  pinMode(A5, INPUT);                                   // AO pini giris olarak ayarlandi
}

void loop() {
  adcHamVeri = analogRead(A5);                          // Ham veri okundu

#if DENEYAP_KART
  adcVolDeg = (adcHamVeri * 3.3) / 4095;                // Voltaj donusumu yapildi
#elif DENEYAP_MINI
  adcVolDeg = (adcHamVeri * 3.3) / 8191;                // Voltaj donusumu yapildi
#endif

  Serial.printf("\nADC ham veri\t: %d\n", adcHamVeri);  // Ham veri seri terminale yazdirildi
  Serial.printf("Voltaj degeri\t: %.2f", adcVolDeg);    // Voltaj degeri seri terminale yazdirildi
  Serial.printf("V\n");            
  delay(500);
}
