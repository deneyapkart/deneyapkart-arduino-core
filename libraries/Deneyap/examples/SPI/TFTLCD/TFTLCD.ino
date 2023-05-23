/*
 *  TFTLCD örneği,
 *  TFTLCD ekrana yazı ve şekiller yazdırmaktadır.
 *
 *  ==============================================================================
 *   Bu uygulama örneği için "Adafruit ST7735 and ST7789 Library by Adafruit" kütüphanesi indirilmelidir.  ->https://github.com/adafruit/Adafruit-ST7735-Library<-
 *   Bu uygulama örneği Adafruit ST7735 and ST7789 Library kütüphanesi 1.7.3 versiyonu ile yazılmıştır.
 *  ==============================================================================
*/
#include <Adafruit_ST7735.h>   //ST7735 için donanıma özel kütüphane
//#include <Adafruit_ST7789.h> //ST7789 için donanıma özel kütüphane
#include <SPI.h>

  // SDA -> MOSI 
  // SCL -> SCK
  #define TFT_CS         D4
  #define TFT_RST        D0
  #define TFT_DC         D1

// ST7735 ile 1.44" ve 1.8" TFT için:
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

//ST7789 ile 1.14", 1.3", 1.54", 1.69" ve 2.0" TFT için:
//Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

#define TFT_MOSI        MOSI 
#define TFT_SCLK        SCK
  
//ST7735 tabanlı ekranlar için kullanılacak
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

// ST7789 tabanlı ekranlar için kullanılacak
//Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);


void setup(void) {
  Serial.begin(115200);
  Serial.print(F("Merhaba! ST77xx TFT LCD Testi"));

  // 1.8" TFT ekran kullanıyorsanız bu başlatıcıyı kullanın:
  //tft.initR(INITR_BLACKTAB);      // ST7735S çipini başlat, Siyah sekme

  // WaveShare gibi ofsetli bir 1.8" TFT ekran kullanıyorsanız bu başlatıcıyı kullanın:
  // tft.initR(INITR_GREENTAB);     // ST7735S çipini başlat, Yeşil sekme

  // 1.44" TFT kullanıyorsanız bu başlatıcıyı kullanın:
  tft.initR(INITR_144GREENTAB);    // ST7735R çipini başlat, Yeşil sekme

  // 0.96" 160x80 TFT kullanıyorsanız bu başlatıcıyı kullanın:
  //tft.initR(INITR_MINI160x80);   // ST7735S mini ekranını başlat

  // 1.3" or 1.54" 240x240 TFT kullanıyorsanız bu başlatıcıyı kullanın:
  //tft.init(240, 240);            //  ST7789 240x240 başlat

  // 1.69" 280x240 TFT kullanıyorsanız bu başlatıcıyı kullanın:
  //tft.init(240, 280);            //  ST7789 280x240 başlat

  // 2.0" 320x240 TFT kullanıyorsanız bu başlatıcıyı kullanın:
  //tft.init(240, 320);            // ST7789 320x240 başlat

  // 1.14" 240x135 TFT kullanıyorsanız bu başlatıcıyı kullanın:
  //tft.init(135, 240);            // ST7789 240x135 başlat
   
   // SPI hızı varsayılan olarak kitaplıkta tanımlanan SPI_DEFAULT_FREQ değerine ayarlanır, burada geçersiz kılabilirsiniz
   // İzin verilen hızın çipe ve kablolama kalitesine bağlı olduğunu unutmayın, çok hızlı giderseniz, 
   // bazen veya her zaman siyah bir ekranla karşılaşabilirsiniz.
   //tft.setSPISpeed(40000000);

  Serial.println(F("Başlatıldı"));

  tft.fillScreen(ST77XX_BLACK);

  // büyük metin bloğu
  tft.fillScreen(ST77XX_BLACK);
  testdrawtext("DENEYAP KART; guclu islemcisi, dayanikli tasarimi ve cok yonlo giris/cikis pinleri ile kullanicilara Elektronik Programlama, Nesnelerin İnterneti (IoT) ve Yapay Zeka alanlarinda baslangic seviyesinden endüstriyel uygulamalara kadar her seviyede projeyi yapma imkani sunuyor.", ST77XX_WHITE);
  delay(5000);

  tft.drawPixel(tft.width()/2, tft.height()/2, ST77XX_GREEN);  // ekranın ortasında tek bir piksel
  delay(500);

  testlines(ST77XX_YELLOW); 
  delay(500);

  testfastlines(ST77XX_RED, ST77XX_BLUE);
  delay(500);

  testdrawrects(ST77XX_GREEN); 
  delay(500);

  testfillrects(ST77XX_YELLOW, ST77XX_MAGENTA);
  delay(500);

  tft.fillScreen(ST77XX_BLACK);
  testfillcircles(10, ST77XX_BLUE);
  testdrawcircles(10, ST77XX_WHITE);
  delay(500);

  testroundrects();
  delay(500);

  tftPrintTest(); 
  delay(4000);

  testtriangles();
  delay(500);
  
  Serial.println("bitti");
  delay(1000);
}

void loop() {
  tft.invertDisplay(true);   
  delay(500);
  tft.invertDisplay(false);  
  delay(500);
}

void testlines(uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(0, 0, x, tft.height()-1, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(0, 0, tft.width()-1, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1, 0, x, tft.height()-1, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1, 0, 0, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(0, tft.height()-1, x, 0, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(0, tft.height()-1, tft.width()-1, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1, tft.height()-1, x, 0, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1, tft.height()-1, 0, y, color);
    delay(0);
  }
}

void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0,0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void testfastlines(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t y=0; y < tft.height(); y+=5) {
    tft.drawFastHLine(0, y, tft.width(), color1);
  }
  for (int16_t x=0; x < tft.width(); x+=5) {
    tft.drawFastVLine(x, 0, tft.height(), color2);
  }
}

void testdrawrects(uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color);
  }
}

void testfillrects(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=tft.width()-1; x > 6; x-=6) {
    tft.fillRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color1);
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color2);
  }
}

void testfillcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=radius; x < tft.width(); x+=radius*2) {
    for (int16_t y=radius; y < tft.height(); y+=radius*2) {
      tft.fillCircle(x, y, radius, color);
    }
  }
}

void testdrawcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=0; x < tft.width()+radius; x+=radius*2) {
    for (int16_t y=0; y < tft.height()+radius; y+=radius*2) {
      tft.drawCircle(x, y, radius, color);
    }
  }
}

void testtriangles() {
  tft.fillScreen(ST77XX_BLACK);
  uint16_t color = 0xFC00;
  int t;
  int w = tft.width()/2;
  int x = tft.height()-1;
  int y = 0;
  int z = tft.width();
  for(t = 0 ; t <= 15; t++) {
    tft.drawTriangle(w, y, y, x, z, x, color);
    x-=4;
    y+=4;
    z-=4;
    color+=100;
  }
}

void testroundrects() {
  tft.fillScreen(ST77XX_BLACK);
  uint16_t color = 100;
  int i;
  int t;
  for(t = 0 ; t <= 4; t+=1) {
    int x = 0;
    int y = 0;
    int w = tft.width()-2;
    int h = tft.height()-2;
    for(i = 0 ; i <= 16; i+=1) {
      tft.drawRoundRect(x, y, w, h, 5, color);
      x+=2;
      y+=3;
      w-=4;
      h-=6;
      color+=1100;
    }
    color+=100;
  }
}

void tftPrintTest() {
  tft.setTextWrap(false);
  tft.fillScreen(ST77XX_WHITE);
  tft.setCursor(0, 20);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(2);
  tft.println("TURKIYE");
  tft.println("TEKNOLOJI");
  tft.println("VAKFI");
  tft.println("    ");
  tft.println("DENEYAP");
  tft.println("KART");
}
