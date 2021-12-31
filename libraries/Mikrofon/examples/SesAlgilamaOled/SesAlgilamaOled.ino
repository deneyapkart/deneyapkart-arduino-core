#if DENEYAP_KART

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <driver/i2s.h>

// Örnekleme ve hafıza değerleri
#define I2S_SAMPLE_RATE   16000 
#define SAMPLE_BUFFER_SIZE 512
  
#define I2S_CHANNEL       I2S_NUM_0

#define SCREEN_WIDTH 128  // OLED ekranın piksel olarak genişliği
#define SCREEN_HEIGHT 64  // OLED ekranın piksel olarak  yüksekliği
// OLED Konfigürasyon ayarları
#define OLED_RESET     D4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 _display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const long int MIN_VALUE =  800000;
const long int MAX_VALUE =  2027356160;
const int DELAY_LOOP_MS = 1;  // ne sıklıkta değer okunacağını ve grafikteki değeri yavaşlatmak için
int _xPos = 0;

// FPS ayarı
float _fps = 0;
unsigned long _frameCount = 0;
unsigned long _fpsStartTimeStamp = 0;

// Ekran pixel uzunluğu 
boolean _drawStatusBar = true; 
int _graphHeight = SCREEN_HEIGHT;

bool I2S_Init()
{ 
  //I2S konfigürasyon ayarları
  i2s_config_t i2s_config = {  
    .mode                   = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_PDM),
    .sample_rate            = I2S_SAMPLE_RATE,
    .bits_per_sample        = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format         = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format   = i2s_comm_format_t(I2S_COMM_FORMAT_I2S),
    .intr_alloc_flags       = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count          = 2,
    .dma_buf_len            = 512,
    .use_apll               = false,
    };

    //Kanal seçimi
  i2s_pin_config_t pin_config = {  
    .bck_io_num           = GPIO_NUM_32,
    .ws_io_num            = MICC,
    .data_out_num         = I2S_PIN_NO_CHANGE,
    .data_in_num          = MICD,
  };
  if (i2s_driver_install(I2S_CHANNEL, &i2s_config, 0, NULL) != ESP_OK) {
    Serial.println("i2s_driver_install() hatası");
    return false;
  }

  if (i2s_set_pin(I2S_CHANNEL, &pin_config) != ESP_OK) {
    Serial.println("i2s_set_pin() hatası");
    return false;
  }
  i2s_set_clk(I2S_CHANNEL, I2S_SAMPLE_RATE, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_MONO);
}

void setup() {
  Serial.begin(115200);
  I2S_Init();  //I2S başlatma

  // SSD1306_SWITCHCAPVCC = 3.3V
  if (!_display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); 
  }

  // ara belleği temizle
  _display.clearDisplay();

  _display.setTextSize(1);
  _display.setTextColor(WHITE, BLACK);
  _display.setCursor(0, 0);
  _display.println("Screen initialized!");
  _display.display();
  delay(50);
  _display.clearDisplay();

  if(_drawStatusBar){
    _graphHeight = SCREEN_HEIGHT - 10;
  }

  _fpsStartTimeStamp = millis();
}
int32_t raw_samples[SAMPLE_BUFFER_SIZE];

void loop() {
  // Mikrofondan veri okuma
  size_t bytes_read = 0;
  i2s_read(I2S_NUM_0, raw_samples, sizeof(int32_t) * SAMPLE_BUFFER_SIZE, &bytes_read, portMAX_DELAY);
  int samples_read = bytes_read / sizeof(int32_t);
  if(_drawStatusBar){
    for (int i = 0; i < samples_read; i++)
    { 
      if (_xPos >= _display.width()) {
    _xPos = 0;
    _display.clearDisplay();
    
  }
        if(raw_samples[i] >= 0)
        {
          // Gelen değer pozitif ise ekranda 32 ile 64. pixel aralığına bastırma
          int long lineHeight = map(raw_samples[i], 0, 80000000, 32, 64);
          int  yPos = _display.height() - lineHeight;
          drawStatusBar(raw_samples[i] );
          _display.drawFastVLine(_xPos++, yPos, lineHeight, SSD1306_WHITE);
          _display.display();
          calcFrameRate();
          Serial.println(lineHeight);
          delay(DELAY_LOOP_MS);
        }

        else if(raw_samples[i] < 0)
        {
          //Gelen değer negatif ise ekranda 0 ile 32. pixel aralığına bastırma
          int long lineHeight = map(raw_samples[i], -80000000, 0 , 0, 32);
          lineHeight = 32 - lineHeight; 
          int  yPos = _display.height() - lineHeight;
          drawStatusBar(lineHeight);
          _display.drawFastVLine(_xPos++, yPos, lineHeight, SSD1306_WHITE);
          _display.display();
          calcFrameRate();
          Serial.println(lineHeight);
          delay(DELAY_LOOP_MS);
        }
    }    
  }
}

void calcFrameRate() {    
  unsigned long elapsedTime = millis() - _fpsStartTimeStamp;
  _frameCount++;
  if (elapsedTime > 1000) {
    _fps = _frameCount / (elapsedTime / 1000.0);
    _fpsStartTimeStamp = millis();
    _frameCount = 0;
  }
}

// Mikrofon verisini sayı olarak yazdırma
void drawStatusBar(int t) {  
  _display.fillRect(0, 0, _display.width(), 8, SSD1306_BLACK); 
  _display.setCursor(0, 0);
  _display.print(t);

  // Frame yazdırma
  int16_t x1, y1;
  uint16_t w, h;
  _display.getTextBounds("XX.XX fps", 0, 0, &x1, &y1, &w, &h);
  _display.setCursor(_display.width() - w, 0);
  _display.print(_fps);
  _display.print(" fps");
}

#else
#error Bu uygulama dahili mikrofon olmadigi icin Deneyap Mini ile gerceklestirilemez!
#endif
