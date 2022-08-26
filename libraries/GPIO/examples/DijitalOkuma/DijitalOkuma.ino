/*
 *   Dijital okuma örneği,
 *   Kartın üzerinde yer alan "But" butonuna basıldığında karta bulunan RGB led sırasıyla Kırmızı, Yeşil, Mavi, Turuncu, Magenta, 
 *   Cyan, Beyaz renklerinde yanacaktır ve sonraki buton basımında led sönmektedir. 
 *   Bu işlem bir döngü şekilde her butona basımında devam etmektedir.
 *   
 *   Deneyap Kart 1A ve DENEYAP G ile bu uygulamayı gerçekleştirilmek istenirse harici ledler bağlanmalıdır.
 *   
 */
enum renkler
{
  KIRMIZI,
  YESIL,
  MAVI,
  TURUNCU,
  MAGENTA,
  CYAN,
  BEYAZ,
  RENK_YOK
};

uint32_t sayici = 0;
uint8_t renk_durumu = RENK_YOK;

void setup() {
  pinMode(GPKEY, INPUT);        // Genel amacli buton pini giris olarak ayarlandi
  pinMode(LEDR, OUTPUT);        // Kirmizi led cikis olarak ayarlandi
  pinMode(LEDG, OUTPUT);        // Yesil led cikis olarak ayarlandi
  pinMode(LEDB, OUTPUT);        // Mavi led cikis olarak ayarlandi
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

    case TURUNCU:
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
  }
}
