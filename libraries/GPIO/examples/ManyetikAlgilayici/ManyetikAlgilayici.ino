#if DENEYAP_KART

//Esp32'de dahili hall sensöründen veri okuma
//değerler düşük olabilir.
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

#else
#error Bu uygulama ESP32S2 mikrodenetleyisinde dahili hall sensor olmadigi icin Deneyap Mini ile gerceklestirilemez!
#endif
