/*
 *   ManyetikAlgilayici örneği,
 *   Bu örnekte mikrodenetleyiciden manyetik algılayıcıdan veri okuması yapılmaktadır. Değerler düşük olabilir.
 *   Bu örnekte Deneyap Kart ve Deneyap Kart 1A dahili manyetik alan sensöründen alınan verileri seri port ekranına yazdırmaktadır. 
 *   Bu örnek uygulama diğer Deneyap Geliştirme Kartları kullanılırsa harici magnetik alan sensörü bağlanılmalı ve kodda gerekli değişiklikler yapılmalıdır.
*/
int deger = 0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  deger = hallRead();  
  //Seri port ekranında değerleri yazdırma:
  Serial.print("Okunan değer = ");
  Serial.println(deger);
}
