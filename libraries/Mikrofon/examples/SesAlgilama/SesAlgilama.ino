#if DENEYAP_KART

#include <driver\i2s.h>

// Örnekleme ve hafıza değerleri
#define I2S_SAMPLE_RATE   16000 
#define SAMPLE_BUFFER_SIZE 512
  
#define I2S_CHANNEL       I2S_NUM_0           

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
