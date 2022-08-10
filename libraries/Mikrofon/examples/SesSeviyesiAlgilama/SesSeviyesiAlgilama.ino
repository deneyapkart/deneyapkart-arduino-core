/*
 *  SesSeviyesiAlgilama örneği,
 *  Deneyap Karttaki dahili mikrofon ile kullanıcı ortamdaki ses verisini seri terminalde gözlemlemektedir. 
 *  Karttaki mavi led ve D0 harici bağlanan ledler belirlenen değere göre yanıp sönmektedir. 
 *  Ses değişimini SERİ PORT ekranında grafiksel olarak izlenmelidir.
 * 
 *  Bu uygulama Deneyap Kart 1A ve Deneyap Mini Kartları ile gerçekleştirilmek istenirse harici mikrofon bağlanmalıdır ve gerekli bağlantı bilgileri değiştirilmelidir.  
 *  
*/
#include "mp34dt05.h"
#define threshold 50  //verilen eşik değeri ortamın ses durumuna göre istenilen değer ile değiştirilmeli.
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
    if(data > threshold){
       digitalWrite(LEDB, LOW);
       digitalWrite(D0, HIGH); 
       }else{ 
       digitalWrite(LEDB, HIGH);
       digitalWrite(D0, LOW);  
    }
  }
}
