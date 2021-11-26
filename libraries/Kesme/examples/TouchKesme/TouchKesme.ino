/*
Bu, Touch Interrupt nasıl kullanılacağına bir örnektir.
Eşik ne kadar büyük olursa, dokunma o kadar mantıklı olur
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
