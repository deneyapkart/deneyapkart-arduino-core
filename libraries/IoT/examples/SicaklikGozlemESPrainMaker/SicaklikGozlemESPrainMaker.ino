// ---------->>>>>>>>>> YUKLEME YAPILMADAN DIKKAT EDILMESI GEREKEN HUSUS <<<<<<<<<<----------
// "Araçlar -> Partition Scheme -> RainMaker" secilmeli //
// "Tools -> Partition Scheme -> RainMaker" secilmeli //
/*
 *    SicaklikGozlemESPrainMaker örneği,
 *    Bu örnekte ESP Rain Maker mobil uygulaması kullanılmaktadır. 
 *    Deneyap Kart'taki dahili IMU'dan alınan sıcaklık verileri ESP Rain Maker mobil uygulamasında gözlenmektedir.
 *    Bu örnek uygulama diğer Deneyap Geliştirme Kartları kullanılırsa harici sıcaklık sensörü bağlanılmalı ve kodda gerekli değişiklikler yapılmalıdır.
 *
 *    Örnek uygulamayı yükledikten sonra seri port ekranına gelen QR kodunu ESP RainMaker mobil uygulamasında taratınız.
 *    Seri port ekranına gelen QR kodu görünür değilse, altındaki URL'yi bir tarayıcıda kopyala yapıştırın.
 *    QR kod seri port ekranından görünmüyor ise dahili butona "BUT" 4 saniyeden fazla basılı tutun.    
 *
 *    Bu uygulama örneği için "SimpleTimer by Alexander Kiryanenko" kütüphanesi indirilmelidir.  -> https://github.com/kiryanenko/SimpleTimer<-
 *    Bu uygulama örneği SimpleTimer kütüphanesi 1.0.0 versiyonu ile yazılmıştır.
*/
#include "RMaker.h"
#include "WiFi.h"
#include "WiFiProv.h"
#include "lsm6dsm.h"  // Deneyap Kart dahili IMU kütüphanesinin eklenmesi
#include <SimpleTimer.h>

LSM6DSM IMU;  // IMU için class tanımlanması

float temp;

const char *service_name = "DeneyapKart";
const char *pop = "1234567";

static uint8_t button = GPKEY;

bool wifi_connected = 0;

SimpleTimer Timer;

static TemperatureSensor temperature("Temperature");

void sysProvEvent(arduino_event_t *sys_event) {
  switch (sys_event->event_id) {
    case ARDUINO_EVENT_PROV_START:
#if CONFIG_IDF_TARGET_ESP32
      printQR(service_name, pop, "ble");
#else
      printQR(service_name, pop, "softap");
#endif
      break;
    case ARDUINO_EVENT_WIFI_STA_CONNECTED:
      wifi_connected = 1;
      delay(500);
      break;
    case ARDUINO_EVENT_PROV_CRED_RECV:
      {
        break;
      }
    default:;
  }
}

void setup() {
  Serial.begin(115200);
  IMU.begin();
  delay(3000);

  Node myNode;
  myNode = RMaker.initNode("Deneyap Sicaklik Gozlem");

  myNode.addDevice(temperature);

  RMaker.enableOTA(OTA_USING_PARAMS);
  RMaker.enableTZService();
  RMaker.enableSchedule();

  RMaker.start();

  // Sensör verilerini göndermek için Zamanlayıcı(Timer)
  Timer.setInterval(5000);

  WiFi.onEvent(sysProvEvent);

#if CONFIG_IDF_TARGET_ESP32
  WiFiProv.beginProvision(WIFI_PROV_SCHEME_BLE, WIFI_PROV_SCHEME_HANDLER_FREE_BTDM, WIFI_PROV_SECURITY_1, pop, service_name);
#else
  WiFiProv.beginProvision(WIFI_PROV_SCHEME_SOFTAP, WIFI_PROV_SCHEME_HANDLER_NONE, WIFI_PROV_SECURITY_1, pop, service_name);
#endif
}

void loop() {
  temp = IMU.readTempC();
  Serial.println("\nSıcaklık değerleri");
  Serial.print("Celsius: ");  // Sicaklik verisi okunması (Celsius)
  Serial.print(temp);
  Serial.print("\tFahrenheit: ");  // Sicaklik verisi okunması (Fahrenheit)
  Serial.println(IMU.readTempF());

  if (Timer.isReady() && wifi_connected) {
    Serial.println("Sensör verileri gönderiliyor.");
    temperature.updateAndReportParam("Temperature", temp);
    Timer.reset();
  }

  if (digitalRead(button) == LOW) {
    delay(100);
    int startTime = millis();
    while (digitalRead(button) == LOW) delay(50);
    int endTime = millis();

    if ((endTime - startTime) > 10000) {
      // Tuşa 10 saniyeden fazla basılırsa, hepsini sıfırlayın
      Serial.printf("Fabrika ayarlarını sıfırla\n");
      RMakerFactoryReset(2);
    } else if ((endTime - startTime) > 3000) {
      Serial.printf("Sıfırla\n");
      // Tuşa 3 saniyeden fazla, ancak 10'dan az basılırsa, Wi-Fi'yi sıfırlayın
      RMakerWiFiReset(2);
    }
  }
  delay(100);
}