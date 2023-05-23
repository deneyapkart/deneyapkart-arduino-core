/*
 *   Anolog veri okuma örneği,
 *   Bu örnekte, alınan analog veri seri port ekranına yazdırılmaktadır. 
 *   Alınan analog verinin voltaj dönüşümü yapılıp seri port ekranına yazdırılmıştır.
*/
uint16_t adcHamVeri = 0;                                   // Ham veri icin degisken
float adcVolDeg = 0;                                       // Voltaj donusumu icin degisken

void setup() {
  Serial.begin(115200);                                    // Seri haberlesme baslatildi
  pinMode(A0, INPUT);                                      // A0 pini giris olarak ayarlandi
}

void loop() {
  adcHamVeri = analogRead(A0);                             // Ham veri okundu

  adcVolDeg = (adcHamVeri * 3.05) / 4095;               // Deneyap Kart için voltaj donusumu yapildi. 12 bit olduğu içim 0-4095 arası değer okuyor
//  adcVolDeg = (adcHamVeri * 2.6)  / 8191;                // Deneyap Mini Kart için voltaj donusumu yapildi. 13 bit olduğu içim 0-8191 arası değer okuyor
//  adcVolDeg = (adcHamVeri * 3.15) / 4095;                // Deneyap Kart 1A için voltaj donusumu yapildi. 12 bit olduğu içim 0-4095 arası değer okuyor
//  adcVolDeg = (adcHamVeri * 2.9)  / 4095;                // Deneyap Kart G  Kart için voltaj donusumu yapildi. 12 bit olduğu içim 0-4095 arası değer okuyor

  Serial.printf("\nADC ham veri\t: %d\n", adcHamVeri);     // Ham veri seri port ekranına yazdırıldı
  Serial.printf("Voltaj degeri\t: %.2fV\n", adcVolDeg);    // Voltaj degeri seri port ekranına yazdırıldı
  delay(500);
}