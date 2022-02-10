/*
 *  SesKaydetmeSD örneği,
 *  Deneyap Karttaki dahili mikrofon ile kullanıcı Deneyap Karttaki dahili butona bastıktan sonra ortamdaki sesleri SD kartta belirlenen SURE boyunca ses kaydetmekte ve kayıt boyunca karttaki mavi ledi yakmaktadır.
 * 
 *  Bu uygulama Deneyap Kart 1A ve Deneyap Mini Kartları ile gerçekleştirilmek istenirse harici mikrofon bağlanmalıdır ve gerekli bağlantı bilgileri değiştirilmelidir. 
 *  
*/
#include <driver/i2s.h>
#include "FS.h"
#include "SD.h"

#define SURE  15   //kaç saniye ses kaydı yapılacağı ayarlama

#define I2S_SAMPLE_RATE   16000   // örnekleme değerleri
#define I2S_CHANNEL       I2S_NUM_0           

bool I2S_Init()
{ 
  i2s_config_t i2s_config = {  //I2S konfigürasyon ayarları
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
    
  i2s_pin_config_t pin_config = {  //Kanal seçimi
    .bck_io_num           = I2S_PIN_NO_CHANGE,
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

void I2S_Quit() {
  if (i2s_driver_uninstall(I2S_CHANNEL) != ESP_OK) {
    Serial.println("i2s_driver_uninstall() hatası");
  }
}

//Bir dosya oluşturma ve daha sonra PC'den oynatabilmesi için ona wav başlığı ekleme
bool create_wav_file(const char* song_name, uint32_t duration, uint16_t num_channels, const uint32_t sampling_rate, uint16_t bits_per_sample) {

  // bayt cinsinden veri boyutu -> bu miktarda veriyi daha sonra mikrofonda kaydetme
  uint32_t data_size = sampling_rate * num_channels * bits_per_sample * duration / 8;

  if (!SDCard.begin()) {
    Serial.println("Kart bağlantısı başarısız");
    return false;
  }

  File new_audio_file = SDCard.open(song_name, FILE_WRITE);
  if (new_audio_file == NULL) {
    Serial.println("Dosya oluşturulamadı");
    return false;
  }

  /* *************** EKLEME ".WAV"  *************** */
  uint8_t CHUNK_ID[4] = {'R', 'I', 'F', 'F'};
  new_audio_file.write(CHUNK_ID, 4);

  uint32_t chunk_size = data_size + 36;
  uint8_t CHUNK_SIZE[4] = {chunk_size, chunk_size >> 8, chunk_size >> 16, chunk_size >> 24};
  new_audio_file.write(CHUNK_SIZE, 4);

  uint8_t FORMAT[4] = {'W', 'A', 'V', 'E'};
  new_audio_file.write(FORMAT, 4);

  uint8_t SUBCHUNK_1_ID[4] = {'f', 'm', 't', ' '};
  new_audio_file.write(SUBCHUNK_1_ID, 4);

  uint8_t SUBCHUNK_1_SIZE[4] = {0x10, 0x00, 0x00, 0x00};
  new_audio_file.write(SUBCHUNK_1_SIZE, 4);

  uint8_t AUDIO_FORMAT[2] = {0x01, 0x00};
  new_audio_file.write(AUDIO_FORMAT, 2);

  uint8_t NUM_CHANNELS[2] = {num_channels, num_channels >> 8};
  new_audio_file.write(NUM_CHANNELS, 2);

  uint8_t SAMPLING_RATE[4] = {sampling_rate, sampling_rate >> 8, sampling_rate >> 16, sampling_rate >> 24};
  new_audio_file.write(SAMPLING_RATE, 4);

  uint32_t byte_rate = num_channels * sampling_rate * bits_per_sample / 8;
  uint8_t BYTE_RATE[4] = {byte_rate, byte_rate >> 8, byte_rate >> 16, byte_rate >> 24};
  new_audio_file.write(BYTE_RATE, 4);

  uint16_t block_align = num_channels * bits_per_sample / 8;
  uint8_t BLOCK_ALIGN[2] = {block_align, block_align >> 8};
  new_audio_file.write(BLOCK_ALIGN, 2);

  uint8_t BITS_PER_SAMPLE[2] = {bits_per_sample, bits_per_sample >> 8};
  new_audio_file.write(BITS_PER_SAMPLE, 2);

  uint8_t SUBCHUNK_2_ID[4] = {'d', 'a', 't', 'a'};
  new_audio_file.write(SUBCHUNK_2_ID, 4);

  uint8_t SUBCHUNK_2_SIZE[4] = {data_size, data_size >> 8, data_size >> 16, data_size >> 24};
  new_audio_file.write(SUBCHUNK_2_SIZE, 4);

  // Gerçek veriler bu noktadan sonra eklenme
  
  new_audio_file.close();
  SDCard.end();
  return true;
}

void microphone_record(const char* song_name, uint32_t duration) {
  // Daha sonra PC'den oynatabilmemiz için wav dosyası oluşturma
  if (!create_wav_file(song_name, duration, 1, I2S_SAMPLE_RATE, I2S_BITS_PER_SAMPLE_16BIT)) {
    Serial.println("wav dosyası oluşturma hatası");
    return;
  }

  //Mikrofondan veri kaydetmek için SD kartı başlatma
  if (!SDCard.begin()) {
    Serial.println("Kart bağlantısı başarısız");
    return;
  }

  // Mikrofondan veri almak için arabellek
  const size_t BUFFER_SIZE = 500;
  uint8_t* buf = (uint8_t*)malloc(BUFFER_SIZE);

  //PCM verilerini eklemek için oluşturulan .wav dosyasını ekleme + binary modunda geçme
  File audio_file = SDCard.open(song_name, FILE_APPEND);
  if (audio_file == NULL) {
    Serial.println("Dosya oluşturulamadı");
    return;
  }

  // I2S başlatma
  I2S_Init();

  // bayt cinsinden veri boyutu - > bu miktarda veriyi mikrofondan kaydetme
  uint32_t data_size = I2S_SAMPLE_RATE * I2S_BITS_PER_SAMPLE_16BIT * duration / 8;

  // Mikrofondan "file_size" bayt okunana kadar kaydetme
  uint32_t counter = 0;
  uint32_t bytes_written;
  Serial.println("Kayıt başladı");
  
  while (counter != data_size) {
    //Dosya boyutunu taşmasını kontrol etme
    if (counter > data_size) {
      Serial.println("Dosya bozuk. data_size, BUFFER_SIZE değerinin katı olmalıdır. Lütfen BUFFER_SIZE değiştirin");
      break;
    }
    // Mikrofondan veri okuma
    if (i2s_read(I2S_CHANNEL, buf, BUFFER_SIZE, &bytes_written, portMAX_DELAY) != ESP_OK) {
      Serial.println("i2s_read() hatası");
    }

    if(bytes_written != BUFFER_SIZE) {
      Serial.println("Byte yazma hatası");
    }

    // Verileri SD karta kaydetme
    audio_file.write( buf, BUFFER_SIZE);

    counter += BUFFER_SIZE;
  }
  Serial.println("Kayıt bitti");

  I2S_Quit();
  audio_file.close();
  free(buf);
  SDCard.end();
}

void setup() {
  Serial.begin(115200);
  pinMode(GPKEY,INPUT);
  pinMode(LEDB,OUTPUT);
  delay(1000);
  Serial.println("Ses kaydetmeye hazır");
}

void loop() {
    if(digitalRead(GPKEY) == 0 )
  {
    digitalWrite(LEDB,LOW);
    microphone_record("/SesDosyasi.wav", SURE);
  }
  else{
    digitalWrite(LEDB,HIGH);
    }
}
