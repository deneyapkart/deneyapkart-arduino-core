/*
 *   Anolog veri okuma örneği,
 *   Bu örnekte, alınan analog veri seri port ekranına yazdırılmaktadır. 
 *   Alınan analog verinin voltaj dönüşümü yapılıp seri port ekrane yazdırılmıştır.
*/
uint16_t adcHamVeri = 0;                                  // Ham veri icin degisken
float adcVolDeg = 0;                                      // Voltaj donusumu icin degisken

void setup() {
  Serial.begin(115200);                                   // Seri haberlesme baslatildi
  pinMode(A0, INPUT);                                     // A0 pini giris olarak ayarlandi
}

void loop() {
  adcHamVeri = analogRead(A0);                            // Ham veri okundu

  adcVolDeg = (adcHamVeri * 3.05) / 4095;               // DENEYAP KART için Voltaj donusumu yapildi
//  adcVolDeg = (adcHamVeri * 2.6) / 8191;                // DENEYAP MİNİ Kart için voltaj donusumu yapildi
//  adcVolDeg = (adcHamVeri * 3.15) / 4095;               // DENEYAP KART 1A için voltaj donusumu yapildi
//  adcVolDeg = (adcHamVeri * 2.9) / 4095;                // DENEYAP KART G  Kart için voltaj donusumu yapildi

  Serial.printf("\nADC ham veri\t: %d\n", adcHamVeri);    // Ham veri seri port ekranına yazdırıldı
  Serial.printf("Voltaj degeri\t: %.2fV\n", adcVolDeg);   // Voltaj degeri seri port ekranına yazdırıldı
  delay(500);
}