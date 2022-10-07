/*
 *   ManyetikAlgilayici örneği,
 *   Bu örnekte mikrodenetleyiciden manyetik algılayıcıdan veri okuması yapılmaktadır. Değerler düşük olabilir.
 *   Bu örnekte Deneyap Kart ve Deneyap Kart 1A dahili manyetik alan sensöründen veri gönderilmiştir. 
 *   Deneyap Mini ve Deneyap Kart G kartındaki mikrodenetleyicilerinde dahili magnetik alan sensörü yoktur bu yüzden magnetik okuma özelliği bulunmamaktadır.
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
