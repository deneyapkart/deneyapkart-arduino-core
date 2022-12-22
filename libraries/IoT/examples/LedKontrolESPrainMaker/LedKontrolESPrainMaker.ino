// ---------->>>>>>>>>> YUKLEME YAPILMADAN DIKKAT EDILMESI GEREKEN HUSUS <<<<<<<<<<----------
// "Araçlar -> Partition Scheme -> RainMaker" secilmeli //
// "Tools -> Partition Scheme -> RainMaker" secilmeli //
/*
 *    LedKontrolESPRainMaker örneği,
 *    Bu örnekte ESP RainMaker mobil uygulaması kullanılmıştır.
 *    ESP RainMaker uygulamasındaki buton ile Deneyap Geliştirme Kartındaki dahili buton kullanılmıştır.
 *    Deneyap Geliştirme Kartlarındaki LED'in durumunu butonlar ile değiştirmektedir.
 *
 *    Örnek uygulamayı yükledikten sonra seri port ekranına gelen QR kodunu ESP RainMaker mobil uygulamasında taratınız.
 *    Seri port ekranına gelen QR kodu görünür değilse, altındaki URL'yi bir tarayıcıda kopyala yapıştırın.
 *    QR kod seri port ekranından görünmüyor ise dahili butona "BUT" 4 saniyeden fazla basılı tutun.    
*/
#include "RMaker.h"
#include "WiFi.h"
#include "WiFiProv.h"

#define DEFAULT_POWER_MODE true
#define DEFAULT_LED_LEVEL 50

const char *service_name = "DeneyapKart";
const char *pop = "abcd1234";

static int button = GPKEY;
static int led = LED_BUILTIN;

bool ledState = true;

static Device my_device("Button", "custom.device.button", &led);

void sysProvEvent(arduino_event_t *sys_event) {
  switch (sys_event->event_id) {
    case ARDUINO_EVENT_PROV_START:
#if CONFIG_IDF_TARGET_ESP32S2
      printQR(service_name, pop, "softap");
#else
      printQR(service_name, pop, "ble");
#endif
      break;
    default:;
  }
}

void write_callback(Device *device, Param *param, const param_val_t val, void *priv_data, write_ctx_t *ctx) {
  const char *device_name = device->getDeviceName();
  const char *param_name = param->getParamName();

  if (strcmp(param_name, "Power") == 0) {
    ledState = val.val.b;
    (ledState == false) ? digitalWrite(led, LOW) : digitalWrite(led, HIGH);
    Serial.printf("ESP RainMaker mobil uygulamasındaki buton ile LED durumu değiştirildi. \n Led durumu: %s\n\n", ledState ? "Açık" : "Kapalı");
    param->updateAndReport(val);
  } else if (strcmp(param_name, "Level") == 0) {
    param->updateAndReport(val);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(GPKEY, INPUT);

  Node my_node;
  my_node = RMaker.initNode("Deneyap ESP RainMaker Düğümü");

  my_device.addNameParam();
  my_device.addPowerParam(DEFAULT_POWER_MODE);
  my_device.assignPrimaryParam(my_device.getParamByName(ESP_RMAKER_DEF_POWER_NAME));

  Param level_param("Level", "custom.param.level", value(DEFAULT_LED_LEVEL), PROP_FLAG_READ | PROP_FLAG_WRITE);
  level_param.addBounds(value(0), value(100), value(1));
  level_param.addUIType(ESP_RMAKER_UI_SLIDER);
  my_device.addParam(level_param);

  my_device.addCb(write_callback);

  my_node.addDevice(my_device);


  RMaker.enableOTA(OTA_USING_PARAMS);
  RMaker.enableTZService();
  RMaker.enableSchedule();
  RMaker.start();

  WiFi.onEvent(sysProvEvent);
#if CONFIG_IDF_TARGET_ESP32S2
  WiFiProv.beginProvision(WIFI_PROV_SCHEME_SOFTAP, WIFI_PROV_SCHEME_HANDLER_NONE, WIFI_PROV_SECURITY_1, pop, service_name);
#else
  WiFiProv.beginProvision(WIFI_PROV_SCHEME_BLE, WIFI_PROV_SCHEME_HANDLER_FREE_BTDM, WIFI_PROV_SECURITY_1, pop, service_name);
#endif
}

void loop() {
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
    } else {
      ledState = !ledState;
      Serial.printf("Deneyap Geliştirme Kartlarındanki dahili buton ile LED durumu değiştirildi. \nLed durumu: %s\n\n", ledState ? "Açık" : "Kapalı");
      my_device.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, ledState);
      (ledState == false) ? digitalWrite(led, LOW) : digitalWrite(led, HIGH);
    }
  }
  delay(100);
}