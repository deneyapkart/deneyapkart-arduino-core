/*
 *  SesFrekansiGozlemleme örneği,
 *  Deneyap Karttaki dahili mikrofon ile kullanıcı ortamdaki ses frenkansını seri çizicide grafiksel olarak gözlemleyebilmektedir.
 * 
 *  Bu uygulama diğer DENEYAP geliştirme kartları ile gerçekleştirilmek istenirse harici mikrofon bağlanmalıdır ve gerekli bağlantı bilgileri değiştirilmelidir.  
*/
#include "driver\i2s.h"
#include "mp34dt05.h"       
  
void setup() {
  Serial.begin(115200);
  micBegin();
  }
  
int32_t raw_samples[BUFFER_SIZE];

void loop() {
  // mikrofondan veri okuma
  size_t bytes_read = 0;
  i2s_read(I2S_NUM_0, raw_samples, sizeof(int32_t) * BUFFER_SIZE, &bytes_read, portMAX_DELAY);
  int samples_read = bytes_read / sizeof(int32_t);
  for (int i = 0; i < samples_read; i++) { 
    Serial.println(raw_samples[i]);
  }
}
