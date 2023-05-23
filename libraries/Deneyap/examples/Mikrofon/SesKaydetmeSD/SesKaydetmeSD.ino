/*
 *  SesKaydetmeSD örneği,
 *  Deneyap Karttaki dahili mikrofon ile mikrofon sesleri .wav dosyası şeklinde SD kartta belirlenen SURE boyunca kaydetmektedir ve kayıt boyunca karttaki mavi ledi yakmaktadır.
 *  Bu uygulama diğer Deneyap geliştirme kartları ile gerçekleştirilmek istenirse harici mikrofon bağlanmalıdır ve gerekli bağlantı bilgileri değiştirilmelidir.
 */
#include "mp34dt05.h" // Deneyap Kart dahili mikrofonun kütüphanesinin eklenmesi
#include "SD.h"       // SD Kart kütüphanesinin eklenmesi

#define SURE 15 // kaç saniye ses kaydı yapılacağı ayarlanması

bool create_wav_file(const char *song_name, uint32_t duration, uint16_t num_channels, const uint32_t sampling_rate, uint16_t bits_per_sample); // fonkiyon prototip tanımlaması
void microphone_record(const char *song_name, uint32_t duration);                                                                              // fonkiyon prototip tanımlaması

void setup() {
  Serial.begin(115200);
  pinMode(LEDB, OUTPUT);

  delay(3000);
  Serial.println("Ses kaydetmeye başlıyor");
  microphone_record("/SesDosyasi.wav", SURE); // Ses kayıt
}

void loop() {
}

/*Bir dosya oluşturma ve daha sonra PC'den oynatabilmesi için ona wav başlığı ekleme*/
bool create_wav_file(const char *song_name, uint32_t duration, uint16_t num_channels, const uint32_t sampling_rate, uint16_t bits_per_sample) {

  /* bayt cinsinden veri boyutu -> bu miktarda veriyi daha sonra mikrofonda kaydetme */
  uint32_t data_size = sampling_rate * num_channels * bits_per_sample * duration / 8;

  if (!SD.begin()) {
    Serial.println("Kart bağlantısı başarısız");
    return false;
  }

  File new_audio_file = SD.open(song_name, FILE_WRITE);
  if (new_audio_file == NULL) {
    Serial.println("Dosya oluşturulamadı");
    return false;
  }

  /* *************** EKLEME ".WAV"  *************** */
  uint8_t CHUNK_ID[4] = {'R', 'I', 'F', 'F'};
  new_audio_file.write(CHUNK_ID, 4);

  uint32_t chunk_size = data_size + 36;
  uint8_t CHUNK_SIZE[4] = {uint8_t(chunk_size), uint8_t(chunk_size >> 8), uint8_t(chunk_size >> 16), uint8_t(chunk_size >> 24)};
  new_audio_file.write(CHUNK_SIZE, 4);

  uint8_t FORMAT[4] = {'W', 'A', 'V', 'E'};
  new_audio_file.write(FORMAT, 4);

  uint8_t SUBCHUNK_1_ID[4] = {'f', 'm', 't', ' '};
  new_audio_file.write(SUBCHUNK_1_ID, 4);

  uint8_t SUBCHUNK_1_SIZE[4] = {0x10, 0x00, 0x00, 0x00};
  new_audio_file.write(SUBCHUNK_1_SIZE, 4);

  uint8_t AUDIO_FORMAT[2] = {0x01, 0x00};
  new_audio_file.write(AUDIO_FORMAT, 2);

  uint8_t NUM_CHANNELS[2] = {uint8_t(num_channels), uint8_t(num_channels >> 8)};
  new_audio_file.write(NUM_CHANNELS, 2);

  uint8_t SAMPLING_RATE[4] = {uint8_t(sampling_rate), uint8_t(sampling_rate >> 8), uint8_t(sampling_rate >> 16), uint8_t(sampling_rate >> 24)};
  new_audio_file.write(SAMPLING_RATE, 4);

  uint32_t byte_rate = num_channels * sampling_rate * bits_per_sample / 8;
  uint8_t BYTE_RATE[4] = {uint8_t(byte_rate), uint8_t(byte_rate >> 8), uint8_t(byte_rate >> 16), uint8_t(byte_rate >> 24)};
  new_audio_file.write(BYTE_RATE, 4);

  uint16_t block_align = num_channels * bits_per_sample / 8;
  uint8_t BLOCK_ALIGN[2] = {uint8_t(block_align), uint8_t(block_align >> 8)};
  new_audio_file.write(BLOCK_ALIGN, 2);

  uint8_t BITS_PER_SAMPLE[2] = {uint8_t(bits_per_sample), uint8_t(bits_per_sample >> 8)};
  new_audio_file.write(BITS_PER_SAMPLE, 2);

  uint8_t SUBCHUNK_2_ID[4] = {'d', 'a', 't', 'a'};
  new_audio_file.write(SUBCHUNK_2_ID, 4);

  uint8_t SUBCHUNK_2_SIZE[4] = {uint8_t(data_size), uint8_t(data_size >> 8), uint8_t(data_size >> 16), uint8_t(data_size >> 24)};
  new_audio_file.write(SUBCHUNK_2_SIZE, 4);

  /* Gerçek veriler bu noktadan sonra eklenme */

  new_audio_file.close();
  SD.end();
  return true;
}

void microphone_record(const char *song_name, uint32_t duration) {
  /* Daha sonra PC'den oynatabilmemiz için wav dosyası oluşturma */
  if (!create_wav_file(song_name, duration, 1, SAMPLE_RATE, I2S_BITS_PER_SAMPLE_16BIT)) {
    Serial.println("wav dosyası oluşturma hatası");
    return;
  }

  /* Mikrofondan veri kaydetmek için SD kartı başlatma */
  if (!SD.begin()) {
    Serial.println("Kart bağlantısı başarısız");
    return;
  }

  /* Mikrofondan veri almak için arabellek */
  uint8_t *buf = (uint8_t *)malloc(BUFFER_SIZE);

  /* PCM verilerini eklemek için oluşturulan .wav dosyasını ekleme + binary modunda geçme */
  File audio_file = SD.open(song_name, FILE_APPEND);
  if (audio_file == NULL) {
    Serial.println("Dosya oluşturulamadı");
    return;
  }

  /* I2S başlatma */
  micBegin();

  /* bayt cinsinden veri boyutu - > bu miktarda veriyi mikrofondan kaydetme */
  uint32_t data_size = SAMPLE_RATE * I2S_BITS_PER_SAMPLE_16BIT * duration / 8;

  /* Mikrofondan "file_size" bayt okunana kadar kaydetme */
  uint32_t counter = 0;
  uint32_t bytes_written;
  digitalWrite(LEDB, LOW);
  Serial.println("Kayıt başladı");

  while (counter != data_size) {
    /* Dosya boyutunu taşmasını kontrol etme */
    if (counter > data_size) {
      Serial.println("Dosya bozuk. data_size, BUFFER_SIZE değerinin katı olmalıdır. Lütfen BUFFER_SIZE değiştirin");
      break;
    }
    /* Mikrofondan veri okuma */
    if (i2s_read(I2S_PORT, buf, BUFFER_SIZE, &bytes_written, portMAX_DELAY) != ESP_OK) {
      Serial.println("i2s_read() hatası");
    }

    if (bytes_written != BUFFER_SIZE) {
      Serial.println("Byte yazma hatası");
    }

    /* Verileri SD karta kaydetme */
    audio_file.write(buf, BUFFER_SIZE);

    counter += BUFFER_SIZE;
  }
  Serial.println("Kayıt bitti");
  digitalWrite(LEDB, HIGH);

  micQuit();
  audio_file.close();
  free(buf);
  SD.end();
}
