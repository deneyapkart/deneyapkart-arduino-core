/*
 *  SesSeviyesiAlgilama örneği,
 *  Deneyap Karttaki dahili mikrofon ile kullanıcı ortamdaki ses seviyesini değişimini karttaki mavi led ve D0 harici bağlanan led ile gözlemlemektedir. 
 *  Ses şiddetini değişimini seri terminalde gözlemleyebilmektedir.
 * 
 *  Bu uygulama Deneyap Kart 1A ve Deneyap Mini Kartları ile gerçekleştirilmek istenirse harici mikrofon bağlanmalıdır ve gerekli bağlantı bilgileri değiştirilmelidir.  
 *  
*/
#include "mp34dt05.h"
#define threshold -200  //verilen eşik değeri ortamın ses durumuna göre istenilen değer değiştirilebilinir.
int samples[BUFFER_SIZE];
FilterBeHp2 filter;

void setup() {
  Serial.begin(1000000);
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
    if(data < threshold)
    {
      digitalWrite(LEDB, LOW);
      digitalWrite(D0, LOW); 
    }
    else
    { 
      digitalWrite(LEDB, HIGH);
      digitalWrite(D0, HIGH);  
    }
  }
}
