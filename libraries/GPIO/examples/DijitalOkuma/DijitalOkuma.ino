/*
 *   DijitalOkuma örneği,
 *   Deneyap Geliştirme Kartlarının yer alan "But" butonuna basıldığında karta bulunan RGB led sırasıyla Kırmızı, Yeşil, Mavi, Sarı, Magenta, 
 *   Cyan, Beyaz renklerinde yanacaktır ve sonraki buton basımında led sönmektedir. 
 *   Bu işlem bir döngü şekilde her butona basımında devam etmektedir.
*/
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
      digitalWrite(LEDR, HIGH);
      digitalWrite(LEDG, LOW);
      digitalWrite(LEDB, LOW);
      break;

    case YESIL:
      digitalWrite(LEDR, LOW);
      digitalWrite(LEDG, HIGH);
      digitalWrite(LEDB, LOW);
      break;

    case MAVI:
      digitalWrite(LEDR, LOW);
      digitalWrite(LEDG, LOW);
      digitalWrite(LEDB, HIGH);
      break;

    case SARI:
      digitalWrite(LEDR, HIGH);
      digitalWrite(LEDG, HIGH);
      digitalWrite(LEDB, LOW);
      break;

    case MAGENTA:
      digitalWrite(LEDR, HIGH);
      digitalWrite(LEDG, LOW);
      digitalWrite(LEDB, HIGH);
      break;

    case CYAN:
      digitalWrite(LEDR, LOW);
      digitalWrite(LEDG, HIGH);
      digitalWrite(LEDB, HIGH);
      break;

    case BEYAZ:
      digitalWrite(LEDR, HIGH);
      digitalWrite(LEDG, HIGH);
      digitalWrite(LEDB, HIGH);
      break;

    case RENK_YOK:
      digitalWrite(LEDR, LOW);
      digitalWrite(LEDG, LOW);
      digitalWrite(LEDB, LOW);
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
