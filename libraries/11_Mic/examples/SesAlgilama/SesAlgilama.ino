#if DENEYAP_KART
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <driver/i2s.h>

// Örnekleme ve hafıza değerleri
#define SAMPLE_BUFFER_SIZE 512
#define SAMPLE_RATE 8000
//Kanal seçimi
#define I2S_MIC_CHANNEL I2S_CHANNEL_FMT_ONLY_LEFT
// either wire your microphone to the same pins or change these to match your wiring
#define I2S_MIC_SERIAL_CLOCK GPIO_NUM_32
#define I2S_MIC_LEFT_RIGHT_CLOCK MICC
#define I2S_MIC_SERIAL_DATA MICD

// I2S konfigürasyon ayarları

i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_PDM),
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 4,
    .dma_buf_len = 1024,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0};


i2s_pin_config_t i2s_mic_pins = {
    .bck_io_num = I2S_MIC_SERIAL_CLOCK,
    .ws_io_num = I2S_MIC_LEFT_RIGHT_CLOCK,
    .data_out_num = I2S_PIN_NO_CHANGE,
    .data_in_num = I2S_MIC_SERIAL_DATA};

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// OLED Konfigürasyon ayarları
#define OLED_RESET     D4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 _display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const long int MIN_VALUE =  800000;
const long int MAX_VALUE =  2027356160;
const int DELAY_LOOP_MS = 5; // change to slow down how often to read and graph value

int _xPos = 0;

// FPS ayarı
float _fps = 0;
unsigned long _frameCount = 0;
unsigned long _fpsStartTimeStamp = 0;

// Ekran pixel uzunluğu 
boolean _drawStatusBar = true; // change to show/hide status bar
int _graphHeight = SCREEN_HEIGHT;

void setup() {
  Serial.begin(9600);
  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &i2s_mic_pins);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!_display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); 
  }

  // Clear the buffer
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

  if (_xPos >= _display.width()) {
    _xPos = 0;
    _display.clearDisplay();
  }

  // Mikrofondan veri okuma
  size_t bytes_read = 0;
  i2s_read(I2S_NUM_0, raw_samples, sizeof(int32_t) * SAMPLE_BUFFER_SIZE, &bytes_read, portMAX_DELAY);
  int samples_read = bytes_read / sizeof(int32_t);
  if(_drawStatusBar){
    for (int i = 0; i < samples_read; i++)
    {
        if(raw_samples[i] >= 0)
        {
          // Gelen değer pozitif ise ekranda 32 ile 64. pixel aralığına bastırma
          int long lineHeight = map(raw_samples[i], 0, 80000000, 32, 64);
          int  yPos = _display.height() - lineHeight;
          drawStatusBar(raw_samples[i] );
          _display.drawFastVLine(_xPos++, yPos, lineHeight, SSD1306_WHITE);
          _display.display();
          calcFrameRate();
          Serial.println(raw_samples[i]);
          delay(DELAY_LOOP_MS);
        }

        else if(raw_samples[i] < 0)
        {
          // // Gelen değer negatif ise ekranda 0 ile 32. pixel aralığına bastırma
          int long lineHeight = map(raw_samples[i], -80000000, 0 , 0, 32);
          lineHeight = 32 - lineHeight; 
          int  yPos = _display.height() - lineHeight;
          drawStatusBar(lineHeight);
          _display.drawFastVLine(_xPos++, yPos, lineHeight, SSD1306_WHITE);
          _display.display();
          calcFrameRate();
          Serial.println(raw_samples[i]);
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
#error Bu uygulama dahili mikrofon olmadigi icin Deneyap Mini ile gerceklesitirilemez!
#endif