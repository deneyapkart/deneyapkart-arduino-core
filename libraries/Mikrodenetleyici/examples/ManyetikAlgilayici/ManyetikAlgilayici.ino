/*
 * ManyetikAlgilayici örneği,
 * Bu örnekte mikrodenetleyiciedn manyetik algılayıcıdan veri okuması yapılmaktadır.
 * Değerler düşük olabilir.
 * 
 * Bu uygulama Deneyap Mini Kartını desteklememektedir. 
 * 
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
