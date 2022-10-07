/*
 *  TouchKesme (interrupt) örneği,
 *  Bu örnekte Deneyap Kart 1A veya Deneyap karttaki D15(GPIO27) dokunulduğunda seri port ekrane Touch algılandı yazdırmaktadır. 
 *  Eşik(threshold) ne kadar büyük olursa, dokunma o kadar mantıklı olur.
 *  Deneyap Kart G touch pinleri bulunmamaktadır.  
*/
int threshold = 40;
bool touch1detected = false;

void gotTouch1() {
 touch1detected = true;
}

void setup() {
  Serial.begin(115200);
  delay(1000); 
  Serial.println("Touch Interrupt Testi");
  touchAttachInterrupt(T2, gotTouch1, threshold);
}

void loop() {
  if(touch1detected) {                    //D15 (GPIO27) pinine dokunulduğunda
    touch1detected = false;
    Serial.println("Touch algılandı");  //seri port ekranına "Touch algılandı" yazdırıldı
  }
}
