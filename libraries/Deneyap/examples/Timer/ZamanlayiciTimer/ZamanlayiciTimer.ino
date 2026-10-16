/*
 *   ZamanlayiciTimer örneği,
 *   Bu örnek, ESP32'de donanım Timer'ın nasıl kullanılacağını göstermektedir. Zamanlayıcı onTimer'ı çağırmaktadır.
 *   Her saniye işlev görmektedir. Zamanlayıcı, (IO0)'a bağlanan BUT butonu ile durdurmaktadır.
*/
#define BTN_STOP_ALARM  GPKEY  //Durdur butonunun tanımlanması (kart üzerindeki BUT butonu)

hw_timer_t * timer = NULL;
volatile SemaphoreHandle_t timerSemaphore;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

volatile uint32_t isrCounter = 0;
volatile uint32_t lastIsrAt = 0;

void ARDUINO_ISR_ATTR onTimer(){
  // Sayacı artırın ve ISR'nin zamanını ayarlayın
  portENTER_CRITICAL_ISR(&timerMux);
  isrCounter++;
  lastIsrAt = millis();
  portEXIT_CRITICAL_ISR(&timerMux);
  // Döngüde kontrol edebileceğimiz bir semaphore verin
  xSemaphoreGiveFromISR(timerSemaphore, NULL);
  // Bir çıkışı değiştirmek istiyorsanız, burada digitalRead/Write kullanmak güvenlidir.
}

void setup() {
  Serial.begin(115200);

  pinMode(BTN_STOP_ALARM, INPUT);  // BTN_STOP_ALARM giriş olarak ayarlandı

  // Timer tetiklendiğinde bizi bilgilendirmek için semaphore oluştur
  timerSemaphore = xSemaphoreCreateBinary();

  // Timer'ı 1 MHz frekansla başlatın (her tik 1 mikrosaniye)
  timer = timerBegin(1000000);

  // Timerımıza onTimer fonksiyonunu ekleyin.
  timerAttachInterrupt(timer, &onTimer);

  // Alarmı her saniye onTimer işlevini çağıracak şekilde ayarlayın (mikrosaniye cinsinden değer)
  // Alarmı tekrarla (üçüncü parametre), sınırsız tekrar (dördüncü parametre 0)
  timerAlarm(timer, 1000000, true, 0);
}

void loop() {
  // Timer tetiklendiyse
  if (xSemaphoreTake(timerSemaphore, 0) == pdTRUE){
    uint32_t isrCount = 0, isrTime = 0;
    // Kesinti sayısını ve zamanını okuyun
    portENTER_CRITICAL(&timerMux);
    isrCount = isrCounter;
    isrTime = lastIsrAt;
    portEXIT_CRITICAL(&timerMux);
    // Yazdırın
    Serial.print("onTimer numarası: ");
    Serial.print(isrCount);
    Serial.print(" 'de ");
    Serial.print(isrTime);
    Serial.println(" ms");
  }
  // Butona basıldıysa
  if (digitalRead(BTN_STOP_ALARM) == LOW) {
    // Timer hala çalışıyorsa
    if (timer) {
      // Timer'ı bitirin
      timerEnd(timer);
      timer = NULL;
    }
  }
}
