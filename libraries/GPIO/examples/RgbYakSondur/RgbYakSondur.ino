#define gecikme_suresi 400        // milisaniye

void setup() {
  pinMode(LEDR, OUTPUT);          // Kirmizi led cikis olarak ayarlandi
  pinMode(LEDG, OUTPUT);          // Yesil led cikis olarak ayarlandi
  pinMode(LEDB, OUTPUT);          // Mavi led cikis olarak ayarlandi
}

void loop() {
  // Kirmizi 
  digitalWrite(LEDR, LOW);       
  digitalWrite(LEDG, HIGH);      
  digitalWrite(LEDB, HIGH);      
  delay(gecikme_suresi);

  // Yesil 
  digitalWrite(LEDR, HIGH);       
  digitalWrite(LEDG, LOW);      
  digitalWrite(LEDB, HIGH);     
  delay(gecikme_suresi);

  // Mavi 
  digitalWrite(LEDR, HIGH);     
  digitalWrite(LEDG, HIGH);     
  digitalWrite(LEDB, LOW);      
  delay(gecikme_suresi);

  // Sari 
  digitalWrite(LEDR, LOW);      
  digitalWrite(LEDG, LOW);      
  digitalWrite(LEDB, HIGH);     
  delay(gecikme_suresi);

  // Magenta 
  digitalWrite(LEDR, LOW);      
  digitalWrite(LEDG, HIGH);     
  digitalWrite(LEDB, LOW);      
  delay(gecikme_suresi);

  // Cyan
  digitalWrite(LEDR, HIGH);     
  digitalWrite(LEDG, LOW);      
  digitalWrite(LEDB, LOW);      
  delay(gecikme_suresi);

  // Beyaz
  digitalWrite(LEDR, LOW);      
  digitalWrite(LEDG, LOW);      
  digitalWrite(LEDB, LOW);      
  delay(gecikme_suresi);
}
