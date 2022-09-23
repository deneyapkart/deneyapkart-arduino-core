/*
 *   Dijital okuma örneği,
 *   Kartın üzerinde yer alan RGB led 400 milisaniye arayla Kırmızı, Yeşil, Mavi, Turuncu, Magenta, 
 *   Cyan, Beyaz renkleri yakmaktadır.
 *   
 *   Deneyap Kart 1A ve DENEYAP KART G ile bu uygulamayı gerçekleştirilmek istenirse harici ledler bağlanmalıdır.
 *   
 */
#define gecikme_suresi 400        // milisaniye

void setup() {
  pinMode(LEDR, OUTPUT);          // Kirmizi led cikis olarak ayarlandi
  pinMode(LEDG, OUTPUT);          // Yesil led cikis olarak ayarlandi
  pinMode(LEDB, OUTPUT);          // Mavi led cikis olarak ayarlandi
}

void loop() {
  // Mavi
  digitalWrite(LEDR, LOW);      
  digitalWrite(LEDG, LOW);      
  digitalWrite(LEDB, HIGH);     
  delay(gecikme_suresi);

  // Yeşil
  digitalWrite(LEDR, LOW);      
  digitalWrite(LEDG, HIGH);     
  digitalWrite(LEDB, LOW);      
  delay(gecikme_suresi);

  // Kırmızı
  digitalWrite(LEDR, HIGH);     
  digitalWrite(LEDG, LOW);      
  digitalWrite(LEDB, LOW);      
  delay(gecikme_suresi);

  // Beyaz
  digitalWrite(LEDR, HIGH);      
  digitalWrite(LEDG, HIGH);      
  digitalWrite(LEDB, HIGH);      
  delay(gecikme_suresi);
  
  // Renk yok
  digitalWrite(LEDR, LOW);      
  digitalWrite(LEDG, LOW);      
  digitalWrite(LEDB, LOW);      
  delay(gecikme_suresi);

  // Cyan
  digitalWrite(LEDR, LOW);       
  digitalWrite(LEDG, HIGH);      
  digitalWrite(LEDB, HIGH);      
  delay(gecikme_suresi);

  // Meganta
  digitalWrite(LEDR, HIGH);       
  digitalWrite(LEDG, LOW);      
  digitalWrite(LEDB, HIGH);     
  delay(gecikme_suresi);

  // Sarı
  digitalWrite(LEDR, HIGH);     
  digitalWrite(LEDG, HIGH);     
  digitalWrite(LEDB, LOW);      
  delay(gecikme_suresi);
}
