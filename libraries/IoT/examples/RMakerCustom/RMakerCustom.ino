/*
 * Arduino IDE'deki bölüm şemasını RainMaker olarak değiştirin 
 * Araçlar -> Partition Scheme -> RainMaker
 * Tools -> Partition Scheme -> RainMaker
 */


//Bu örnek, standart bir Custom cihazı ile Deneyap Kart ile RainMaker'ı göstermektedir.
#include "RMaker.h"
#include "WiFi.h"
#include "WiFiProv.h"

#define DEFAULT_POWER_MODE true
#define DEFAULT_DIMMER_LEVEL 50
const char *service_name = "DeneyapKart";
const char *pop = "abcd1234";

//Buton için GPIO pin tanımlaması
static int gpio_0 = 0;
//Sanal cihaz için GPIO pin tanımlaması
static int gpio_dimmer = 16;
/* Pin durumunu okumak için değişken*/
bool dimmer_state = true;

// anahtar, led, fan, ampül, sıcaklık sensörü gibi bazı standart cihaz türleri sağlar.
// Ancak, burada gösterildiği gibi 'Aygıt' temel sınıf nesnesini kullanarak özel aygıtları da tanımlayabilirsiniz.
static Device my_device("Dimmer", "custom.device.dimmer", &gpio_dimmer);

void sysProvEvent(arduino_event_t *sys_event)
{
    switch (sys_event->event_id) {      
        case ARDUINO_EVENT_PROV_START:
#if CONFIG_IDF_TARGET_ESP32
        Serial.printf("\nProvisioning Started with name \"%s\" and PoP \"%s\" on BLE\n", service_name, pop);
        printQR(service_name, pop, "ble");
#else
        Serial.printf("\nProvisioning Started with name \"%s\" and PoP \"%s\" on SoftAP\n", service_name, pop);
        printQR(service_name, pop, "softap");
#endif        
        break;
    }
}

void write_callback(Device *device, Param *param, const param_val_t val, void *priv_data, write_ctx_t *ctx)
{
    const char *device_name = device->getDeviceName();
    const char *param_name = param->getParamName();

    if(strcmp(param_name, "Power") == 0) {
        Serial.printf("Received value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
        dimmer_state = val.val.b;
        (dimmer_state == false) ? digitalWrite(gpio_dimmer, LOW) : digitalWrite(gpio_dimmer, HIGH);
        param->updateAndReport(val);
    } else if (strcmp(param_name, "Level") == 0) {
        Serial.printf("\nReceived value = %d for %s - %s\n", val.val.i, device_name, param_name);
        param->updateAndReport(val);
    }
}

void setup()
{
    Serial.begin(115200);
    pinMode(gpio_0, INPUT);
    pinMode(gpio_dimmer, OUTPUT);
    digitalWrite(gpio_dimmer, DEFAULT_POWER_MODE);

    Node my_node;    
    my_node = RMaker.initNode("Deneyap RainMaker Düğümü");

    //Özel custom oluştur
    my_device.addNameParam();
    my_device.addPowerParam(DEFAULT_POWER_MODE);
    my_device.assignPrimaryParam(my_device.getParamByName(ESP_RMAKER_DEF_POWER_NAME));

    // Özel bir seviye parametresi oluştur ve ekle
    Param level_param("Level", "custom.param.level", value(DEFAULT_DIMMER_LEVEL), PROP_FLAG_READ | PROP_FLAG_WRITE);
    level_param.addBounds(value(0), value(100), value(1));
    level_param.addUIType(ESP_RMAKER_UI_SLIDER);
    my_device.addParam(level_param);

    my_device.addCb(write_callback);
    
    //Düğüme custom device ekle 
    my_node.addDevice(my_device);

    //Bu isteğe bağlıdır 
    RMaker.enableOTA(OTA_USING_PARAMS);
    //Zamanlamayı etkinleştirmek istiyorsanız, setTimeZone() kullanarak bölgeniz için saat dilimini ayarlayın.
    //Kullanılabilir değerlerin listesi burada verilmiştir
    // RMaker.setTimeZone("Asia/Shanghai");
    // Alternatif olarak, Saat Dilimi hizmetini etkinleştirin ve telefon uygulamalarının uygun saat dilimini ayarlamasına izin verin
    RMaker.enableTZService();

    RMaker.enableSchedule();

    RMaker.start();

    WiFi.onEvent(sysProvEvent);
#if CONFIG_IDF_TARGET_ESP32
    WiFiProv.beginProvision(WIFI_PROV_SCHEME_BLE, WIFI_PROV_SCHEME_HANDLER_FREE_BTDM, WIFI_PROV_SECURITY_1, pop, service_name);
#else
    WiFiProv.beginProvision(WIFI_PROV_SCHEME_SOFTAP, WIFI_PROV_SCHEME_HANDLER_NONE, WIFI_PROV_SECURITY_1, pop, service_name);
#endif
}

void loop()
{
    if(digitalRead(gpio_0) == LOW) { //Butona basıldıysa

        delay(100);
        int startTime = millis();
        while(digitalRead(gpio_0) == LOW) delay(50);
        int endTime = millis();

        if ((endTime - startTime) > 10000) {
          // Tuşa 10 saniyeden fazla basılırsa, hepsini sıfırlayın
          Serial.printf("Fabrika ayarlarını sıfırla\n");
          RMakerFactoryReset(2);
        } else if ((endTime - startTime) > 3000) {
          Serial.printf("Wi-Fi sıfırla\n");
          // Tuşa 3 saniyeden fazla, ancak 10'dan az basılırsa, Wi-Fi'yi sıfırlayın
          RMakerWiFiReset(2);
        } else {
          // Cihaz durumunu değiştir
          dimmer_state = !dimmer_state;
          Serial.printf("Buton durumu %s.\n", dimmer_state ? "true" : "false");
          my_device.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, dimmer_state);
          (dimmer_state == false) ? digitalWrite(gpio_dimmer, LOW) : digitalWrite(gpio_dimmer, HIGH);
      }
    }
    delay(100);
}
