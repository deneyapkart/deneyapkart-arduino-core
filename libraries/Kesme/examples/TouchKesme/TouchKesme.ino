/*
 *  TouchKesme (interrupt) örneği,
 *  Bu örnekte Deneyap Kart 1A veya Deneyap karttaki D15(GPIO27) dokunulduğunda seri terminale Touch algılandı yazdırmaktadır. 
 *  Eşik(threshold) ne kadar büyük olursa, dokunma o kadar mantıklı olur.
 *  
*/
int threshold = 40;
bool touch1detected = false;

void gotTouch1(){
 touch1detected = true;
}

void setup() {
  Serial.begin(115200);
  delay(1000); 
  Serial.println("ESP32 Touch Interrupt Testi");
  touchAttachInterrupt(T2, gotTouch1, threshold);
}

void loop(){
  if(touch1detected){                    //D15 (GPIO27) pinine dokunulduğunda
    touch1detected = false;
    Serial.println("Touch algılandı");  //seri terminale "Touch algılandı" yazdırıldı
  }
}
