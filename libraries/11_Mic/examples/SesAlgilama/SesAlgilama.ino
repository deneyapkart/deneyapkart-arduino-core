#if DENEYAP_KART
#include <deneyap.h>
#include <driver\i2s.h>

// Örnekleme ve hafıza değerleri
#define SAMPLE_BUFFER_SIZE 512
#define SAMPLE_RATE 8000
//Kanal seçimi
#define I2S_MIC_CHANNEL I2S_CHANNEL_FMT_ONLY_LEFT
#define I2S_MIC_SERIAL_CLOCK GPIO_NUM_32
#define I2S_MIC_LEFT_RIGHT_CLOCK MICC
#define I2S_MIC_SERIAL_DATA MICD

// I2S konfigürasyon ayarları

i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_PDM),
    .sample_rate = 16000,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
    .channel_format = I2S_MIC_CHANNEL,
    .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_I2S),
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 4,
    .dma_buf_len = 64,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0};


i2s_pin_config_t i2s_mic_pins = {
    .bck_io_num = I2S_MIC_SERIAL_CLOCK,
    .ws_io_num = I2S_MIC_LEFT_RIGHT_CLOCK,
    .data_out_num = I2S_PIN_NO_CHANGE,
    .data_in_num = I2S_MIC_SERIAL_DATA};
    
void setup() {
  Serial.begin(115200);
  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &i2s_mic_pins);
  }
int32_t raw_samples[SAMPLE_BUFFER_SIZE];
void loop() {
  // mikrofondan veri okuma
  size_t bytes_read = 0;
  i2s_read(I2S_NUM_0, raw_samples, sizeof(int32_t) * SAMPLE_BUFFER_SIZE, &bytes_read, portMAX_DELAY);
  int samples_read = bytes_read / sizeof(int32_t);
  for (int i = 0; i < samples_read; i++)
  { 
    Serial.println(raw_samples[i]);
  }
}
#else
#error Bu uygulama dahili mikrofon olmadigi icin Deneyap Mini ile gerceklestirilemez!
#endif