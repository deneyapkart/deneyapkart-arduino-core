/*
 *   DijitalOkuma örneği,
 *   Deneyap Geliştirme Kartlarının yer alan "But" butonuna basıldığında karta bulunan RGB led sırasıyla Kırmızı, Yeşil, Mavi, Sarı, Magenta, 
 *   Cyan, Beyaz renklerinde yanacaktır ve sonraki buton basımında led sönmektedir. 
 *   Bu işlem bir döngü şekilde her butona basımında devam etmektedir.
*/
enum renkler
{
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
  pinMode(GPKEY, INPUT);                                    // Genel amacli buton pini giris olarak ayarlandi
  #if defined (ARDUINO_DYDK) || defined (ARDUINO_DYM)       // DENEYAP KART veya DENEYAP MİNİ kartı kullanılıyorsa
  pinMode(LEDR, OUTPUT);                                    // Kirmizi led cikis olarak ayarlandi
  pinMode(LEDG, OUTPUT);                                    // Yesil led cikis olarak ayarlandi
  pinMode(LEDB, OUTPUT);                                    // Mavi led cikis olarak ayarlandi
  #endif
}

void loop() {
  if(digitalRead(GPKEY) == 0)
  {
    sayici++;
  }
  else
  {
    sayici = 0;
  }

  if(sayici == 50)
  {
    renk_durumu++;
    renk_durumu = renk_durumu % 8;
  }

  switch(renk_durumu)
  {
     #if defined (ARDUINO_DYDK) || defined (ARDUINO_DYM)       // DENEYAP KART veya DENEYAP MİNİ kartı kullanılıyorsa
     case KIRMIZI:
      writeRedLed(HIGH);
      writeGreenLed(LOW);
      writeBlueLed(LOW);
      break;

    case YESIL:
      writeRedLed(LOW);
      writeGreenLed(HIGH);
      writeBlueLed(LOW);
      break;

    case MAVI:
      writeRedLed(LOW);
      writeGreenLed(LOW);
      writeBlueLed(HIGH);
      break;

    case SARI:
      writeRedLed(HIGH);
      writeGreenLed(HIGH);
      writeBlueLed(LOW);
      break;

    case MAGENTA:
      writeRedLed(HIGH);
      writeGreenLed(LOW);
      writeBlueLed(HIGH);
      break;

    case CYAN:
      writeRedLed(LOW);
      writeGreenLed(HIGH);
      writeBlueLed(HIGH);
      break;

    case BEYAZ:
      writeRedLed(HIGH);
      writeGreenLed(HIGH);
      writeBlueLed(HIGH);
      break;

    case RENK_YOK:
      writeRedLed(LOW);
      writeGreenLed(LOW);
      writeBlueLed(LOW);
      break;

    #else                             // Diğer Deneyap Geliştirme Kartları kullanılıyorsa
     case KIRMIZI:
      delay(1);
      neopixelWrite(RGBLED,32,0,0);   // Parlaklık değeri 32 seçilmiştir. 0-255 arası parlaklık değeri verilmektedir.
      break;

    case YESIL:
      delay(1);
      neopixelWrite(RGBLED,0,32,0);
      break;

    case MAVI:
      delay(1);
      neopixelWrite(RGBLED,0,0,32);
      break;

    case SARI:
      delay(1);
      neopixelWrite(RGBLED,32,32,0);
      break;

    case MAGENTA:
      delay(1);
      neopixelWrite(RGBLED,32,0,32);
      break;

    case CYAN:
      delay(1);
      neopixelWrite(RGBLED,0,32,32);
      break;

    case BEYAZ:
      delay(1);
      neopixelWrite(RGBLED,32,32,32);
      break;

    case RENK_YOK:
      delay(1);
      neopixelWrite(RGBLED,0,0,0);
      break;
  #endif
  }
}
