/*  Deneyap Karttaki dahili mikrofon ile kullanıcı ortamdaki ses verilerini SERİ ÇİZİCİ(Serial Plotter)de gözlemlemektedir.
 *  Deneyap Karttaki dahili mavi led ve D0 pinine bağlanan harici led ile belirlenen değere göre ledler yanıp sönmektedir.
 *  Ses değişimini SERİ ÇİZİCİ ekranında grafiksel olarak izlenmelidir.
 *  Bu uygulama diğer Deneyap Geliştirme Kartları ile gerçekleştirilmek istenirse harici mikrofon bağlanmalıdır ve kodda gerekli değişiklikler yapılmalıdır */
#include "mp34dt05.h"  // Deneyap Kart dahili mikrofonun kütüphanesinin eklenmesi

#define threshold 50  // verilen eşik değeri. Ortamın ses durumuna göre istenilen değer ile değiştirilmeli
int samples[BUFFER_SIZE];
FilterBeHp2 filter;

void setup() {
  Serial.begin(115200);
  pinMode(LEDB, OUTPUT);
  pinMode(D0, OUTPUT);
  micBegin();
}

void loop() {
  delay(10);
  size_t num_bytes_read = 0;
  micRead(&num_bytes_read, samples);
  if (num_bytes_read > 0) {
    int data = dataFilter(filter, num_bytes_read, samples);
    Serial.println(data);
    if (data > threshold) {
      digitalWrite(LEDB, LOW);
      digitalWrite(D0, HIGH);
    } else {
      digitalWrite(LEDB, HIGH);
      digitalWrite(D0, LOW);
    }
  }
}
