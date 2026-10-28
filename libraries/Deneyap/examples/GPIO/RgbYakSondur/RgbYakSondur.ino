/*
 *   RgbYakSondur örneği,
 *   Deneyap Geliştirme Kartlarının üzerinde yer alan RGB led 400 milisaniye arayla Kırmızı, Yeşil, Mavi, Turuncu, Magenta, 
 *   Cyan, Beyaz renkleri yakmaktadır. 
*/
#if defined(ARDUINO_DYDK)  // DENEYAP KART: RGB ledler LOW ile yanar
#define LED_YAK    LOW
#define LED_SONDUR HIGH
#elif defined(ARDUINO_DYM)  // DENEYAP MİNİ: RGB ledler HIGH ile yanar
#define LED_YAK    HIGH
#define LED_SONDUR LOW
#endif
#define gecikme_suresi 400  // milisaniye

void setup() {
#if defined(ARDUINO_DYDK) || defined(ARDUINO_DYM)  // DENEYAP KART veya DENEYAP MİNİ kartı kullanılıyorsa
  pinMode(LEDR, OUTPUT);                           // Kirmizi led cikis olarak ayarlandi
  pinMode(LEDG, OUTPUT);                           // Yesil led cikis olarak ayarlandi
  pinMode(LEDB, OUTPUT);                           // Mavi led cikis olarak ayarlandi
#endif
}

void loop() {
#if defined(ARDUINO_DYDK) || defined(ARDUINO_DYM)  // DENEYAP KART veya DENEYAP MİNİ kartı kullanılıyorsa
  // Mavi
  digitalWrite(LEDR, LED_SONDUR);
  digitalWrite(LEDG, LED_SONDUR);
  digitalWrite(LEDB, LED_YAK);
  delay(gecikme_suresi);

  // Yeşil
  digitalWrite(LEDR, LED_SONDUR);
  digitalWrite(LEDG, LED_YAK);
  digitalWrite(LEDB, LED_SONDUR);
  delay(gecikme_suresi);

  // Kırmızı
  digitalWrite(LEDR, LED_YAK);
  digitalWrite(LEDG, LED_SONDUR);
  digitalWrite(LEDB, LED_SONDUR);
  delay(gecikme_suresi);

  // Beyaz
  digitalWrite(LEDR, LED_YAK);
  digitalWrite(LEDG, LED_YAK);
  digitalWrite(LEDB, LED_YAK);
  delay(gecikme_suresi);

  // Renk yok
  digitalWrite(LEDR, LED_SONDUR);
  digitalWrite(LEDG, LED_SONDUR);
  digitalWrite(LEDB, LED_SONDUR);
  delay(gecikme_suresi);

  // Cyan
  digitalWrite(LEDR, LED_SONDUR);
  digitalWrite(LEDG, LED_YAK);
  digitalWrite(LEDB, LED_YAK);
  delay(gecikme_suresi);

  // Meganta
  digitalWrite(LEDR, LED_YAK);
  digitalWrite(LEDG, LED_SONDUR);
  digitalWrite(LEDB, LED_YAK);
  delay(gecikme_suresi);

  // Sarı
  digitalWrite(LEDR, LED_YAK);
  digitalWrite(LEDG, LED_YAK);
  digitalWrite(LEDB, LED_SONDUR);
  delay(gecikme_suresi);

#else  // Diğer Deneyap Geliştirme Kartları kullanılıyorsa
  // Mavi
  neopixelWrite(RGBLED, 0, 0, 64);  // Parlaklık değeri 64 seçilmiştir. 0-255 arası parlaklık değeri verilmektedir.
  delay(gecikme_suresi);

  // Yeşil
  neopixelWrite(RGBLED, 0, 64, 0);
  delay(gecikme_suresi);

  // Kırmızı
  neopixelWrite(RGBLED, 64, 0, 0);
  delay(gecikme_suresi);

  // Beyaz
  neopixelWrite(RGBLED, 64, 64, 64);
  delay(gecikme_suresi);

  // Renk Yok
  neopixelWrite(RGBLED, 0, 0, 0);
  delay(gecikme_suresi);

  // Cyan
  neopixelWrite(RGBLED, 0, 64, 64);
  delay(gecikme_suresi);

  // Meganta
  neopixelWrite(RGBLED, 64, 0, 64);
  delay(gecikme_suresi);

  // Sarı
  neopixelWrite(RGBLED, 64, 64, 0);
  delay(gecikme_suresi);
#endif
}
