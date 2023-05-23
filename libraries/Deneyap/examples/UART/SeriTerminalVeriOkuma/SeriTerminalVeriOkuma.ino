/*
 *  SeriTerminalVeriOkuma örneği,
 *  Uygulama kullanıcıdan birinci sayı ve ikinci sayıyı girmesini istemektedir. Daha sonra işlem seçilmesi beklenmektedir. 1'a basınca toplama, 2'a basınca çıkarma, 3'a basınca çarpma ve 4'a basınca bölme işlemlerini gerçekleştirmektedir. 
 *  Daha sonra herhangi bir karaktere basınca hesaplama işlemleri baştan başlamaktadır.
 * 
 */

// ---->>>>>>>>>> SERİ TERMİNALDE VERİ GİRİŞİ İÇİN UYARI <<<<<<<<<<-----
// Seri Termianal'de "No line ending (Satir sonu yok)" seceneği aktif olmalidir //       

uint32_t serialData1  = 0;                                            // Okunacak ilk veri degiskeni
uint32_t serialData2  = 0;                                            // Okunacak ikinci veri degiskeni
uint32_t arithOp      = 0;                                            // Aritmetik islem secimi degiskeni
uint32_t returnValue  = 0;                                            // Sonuc degiskeni
float divisionResult  = 0;                                            // Bolum sonucu degiskeni
uint8_t newCalcFlag   = 1;                                            // Yeni hesaplama baslsatmak icin bayrak

void setup() {
  Serial.begin(115200);                                               // Seri haberlesme baslatildi
}                                                                     

void loop() {
  if(newCalcFlag)
  {
    Serial.println();
    Serial.print("\nAritmetik islem icin ilk sayiyi giriniz:");         // Ilk veriyi yakala 
    while(Serial.available() == 0);  
    serialData1 = Serial.parseInt();
    Serial.printf("\nYazdiginiz sayi\t: %d", serialData1);              
    Serial.println();
    
    Serial.print("\nAritmetik islem icin ikinci sayiyi giriniz:");      // Ikinci veriyi yakala
    while(Serial.available() == 0);
    serialData2 = Serial.parseInt();
    Serial.printf("\nYazdiginiz sayi\t: %d", serialData2);
    Serial.println();
    
    Serial.println("\nAritmeitk islem seciniz:");                       // Yapilmak istenen aritmetik isleme ait veriyi yakala
    Serial.println("Toplama\t--> 1");
    Serial.println("Cikarma\t--> 2");
    Serial.println("Carpma\t--> 3");
    Serial.println("Bolme\t--> 4");
    while(Serial.available() == 0);
    arithOp = Serial.parseInt();

    if(arithOp != 1 && arithOp != 2 && arithOp != 3 && arithOp != 4)
    {
      Serial.println("\nYanlis secim yaptiniz, lutfen 1,2,3 ya da 4 degerlerini giriniz!");
    }
    else
    {
      switch(arithOp)
      {
        case 1:                                                       // Toplama islemi
          returnValue = serialData1 + serialData2;
          Serial.printf("\nToplama islemi sonucu\t: %d", returnValue);
        break;
    
        case 2:                                                       // Cikarma islemi
          returnValue = serialData1 - serialData2;              
          Serial.printf("\nCikarma islemi sonucu\t: %d", returnValue);
        break;
    
        case 3:
          returnValue = serialData1 * serialData2;                    // Carpma islemi
          Serial.printf("\nCarpim islemi sonucu\t: %d", returnValue);
        break;
    
        case 4:                                                       // Bolme islemi
          divisionResult = (float)serialData1 / (float)serialData2;
          Serial.printf("\nBolum islemi sonucu\t: %.2f", divisionResult);
        break;
      }
    }    

    newCalcFlag = 0;                                                  // Hesaplama bitti
  } 

  Serial.println();                                         
  Serial.print("\nYeni bir hesaplamaya baslamak icin lutfen herhangi bir tusa basiniz!!!");           // Yeni hesaplamaya basla          
  while(Serial.available() == 0);
  if(Serial.read() != 0)
    newCalcFlag = 1;                                                  // Yeni hesaplamaya baslama sarti saglandi
}
