/*
 *   DijitalOkuma örneği,
 *   Deneyap Geliştirme Kartlarının yer alan "But" butonuna basıldığında karta bulunan RGB led sırasıyla Kırmızı, Yeşil, Mavi, Sarı, Magenta, 
 *   Cyan, Beyaz renklerinde yanacaktır ve sonraki buton basımında led sönmektedir. 
 *   Bu işlem bir döngü şekilde her butona basımında devam etmektedir.
*/
#if defined(ARDUINO_DYDK)  // DENEYAP KART: RGB ledler LOW ile yanar
#define LED_YAK    LOW
#define LED_SONDUR HIGH
#elif defined(ARDUINO_DYM)  // DENEYAP MİNİ: RGB ledler HIGH ile yanar
#define LED_YAK    HIGH
#define LED_SONDUR LOW
#endif
enum renkler {
  KIRMIZI,
  YESIL,
  MAVI,
  SARI,
  MAGENTA,
  CYAN,
  BEYAZ,
  RENK_YOK
};

uint32_t sayici = 0;
uint8_t renk_durumu = RENK_YOK;

void setup() {
  pinMode(GPKEY, INPUT);                           // Genel amacli buton pini giris olarak ayarlandi
#if defined(ARDUINO_DYDK) || defined(ARDUINO_DYM)  // DENEYAP KART veya DENEYAP MİNİ kartı kullanılıyorsa
  pinMode(LEDR, OUTPUT);                           // Kirmizi led cikis olarak ayarlandi
  pinMode(LEDG, OUTPUT);                           // Yesil led cikis olarak ayarlandi
  pinMode(LEDB, OUTPUT);                           // Mavi led cikis olarak ayarlandi
#endif
}

void loop() {
  if (digitalRead(GPKEY) == 0) {
    sayici++;
  } else {
    sayici = 0;
  }

  if (sayici == 50) {
    renk_durumu++;
    renk_durumu = renk_durumu % 8;
  }

  switch (renk_durumu) {
#if defined(ARDUINO_DYDK) || defined(ARDUINO_DYM)  // DENEYAP KART veya DENEYAP MİNİ kartı kullanılıyorsa
    case KIRMIZI:
      digitalWrite(LEDR, LED_YAK);
      digitalWrite(LEDG, LED_SONDUR);
      digitalWrite(LEDB, LED_SONDUR);
      break;

    case YESIL:
      digitalWrite(LEDR, LED_SONDUR);
      digitalWrite(LEDG, LED_YAK);
      digitalWrite(LEDB, LED_SONDUR);
      break;

    case MAVI:
      digitalWrite(LEDR, LED_SONDUR);
      digitalWrite(LEDG, LED_SONDUR);
      digitalWrite(LEDB, LED_YAK);
      break;

    case SARI:
      digitalWrite(LEDR, LED_YAK);
      digitalWrite(LEDG, LED_YAK);
      digitalWrite(LEDB, LED_SONDUR);
      break;

    case MAGENTA:
      digitalWrite(LEDR, LED_YAK);
      digitalWrite(LEDG, LED_SONDUR);
      digitalWrite(LEDB, LED_YAK);
      break;

    case CYAN:
      digitalWrite(LEDR, LED_SONDUR);
      digitalWrite(LEDG, LED_YAK);
      digitalWrite(LEDB, LED_YAK);
      break;

    case BEYAZ:
      digitalWrite(LEDR, LED_YAK);
      digitalWrite(LEDG, LED_YAK);
      digitalWrite(LEDB, LED_YAK);
      break;

    case RENK_YOK:
      digitalWrite(LEDR, LED_SONDUR);
      digitalWrite(LEDG, LED_SONDUR);
      digitalWrite(LEDB, LED_SONDUR);
      break;

#else  // Diğer Deneyap Geliştirme Kartları kullanılıyorsa
    case KIRMIZI:
      delay(1);
      neopixelWrite(RGBLED, 250, 0, 0);  // Parlaklık değeri 250 seçilmiştir. 0-255 arası parlaklık değeri verilmektedir.
      break;

    case YESIL:
      delay(1);
      neopixelWrite(RGBLED, 0, 250, 0);
      break;

    case MAVI:
      delay(1);
      neopixelWrite(RGBLED, 0, 0, 250);
      break;

    case SARI:
      delay(1);
      neopixelWrite(RGBLED, 250, 250, 0);
      break;

    case MAGENTA:
      delay(1);
      neopixelWrite(RGBLED, 250, 0, 250);
      break;

    case CYAN:
      delay(1);
      neopixelWrite(RGBLED, 0, 250, 250);
      break;

    case BEYAZ:
      delay(1);
      neopixelWrite(RGBLED, 250, 250, 250);
      break;

    case RENK_YOK:
      delay(1);
      neopixelWrite(RGBLED, 0, 0, 0);
      break;
#endif
  }
}
