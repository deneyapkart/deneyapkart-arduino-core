/*
 *  PotStepMotorKontrol örneği,
 *  Bu örnek uygulamada step motorun mili potansiyonometredeki değer kadar saat yönünde hareket etmektedir. 
*/
#include <Stepper.h>    // Step motor sürücüsü için gerekli kütüphane

const int POT_PIN = A0;   // Potansiyonometrenin bağlandığı analog giriş pininin numarası
const int STEPS_PER_REV = 2048;   // Motorunuzun kaç adım/devir yaptığı, kullandığınız step motora göre tur sayısı değişiklik gösterebilir 

Stepper motor(STEPS_PER_REV, D12, D14, D13, D15);   // Step motorunuzu tanımlanması

void setup() {
  Serial.begin(115200);
  motor.setSpeed(15);   // Motorunuzun hızını 15 RPM olarak ayarlanması
  pinMode(POT_PIN, INPUT);    // Potansiyonometre pinini giriş olarak ayarlanması
}

void loop() {
  int potValue = analogRead(POT_PIN);   // Potansiyonometrenin değerini okunması

  /* Deneyap Mini veya Deneyap Mini v2 kullanılırsa ADC okuma aralığını 0-8191 olarak değiştirin */
  int motorPosition = map(potValue, 0, 4095, 0, STEPS_PER_REV);   // Potansiyonometrenin değerleri ile step motorun konumu arasında bir orantı kurulması
  Serial.printf("Step motorumuz %d adım ilerliyor.\n",  motorPosition);
  motor.step(motorPosition);    // Step motorunu belirtilen konuma taşınması
  delay(500);    // 500 milisaniye beklenmesi
}
