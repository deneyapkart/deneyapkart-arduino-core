/*
 * Arduino IDE'deki bölüm şemasını RainMaker olarak değiştirin 
 * Araçlar -> Partition Scheme -> RainMaker
 * Tools -> Partition Scheme -> RainMaker
 */


//Bu örnek, standart bir Switch cihazı ile Deneyap Kart ile RainMaker'ı göstermektedir.
#include "RMaker.h"
#include "WiFi.h"
#include "WiFiProv.h"

#define DEFAULT_POWER_MODE true
const char *service_name = "DeneyapKart";
const char *pop = "abcd1234";

//Buton için GPIO pin tanımlaması
static int gpio_0 = 0;
//Sanal cihaz için GPIO pin tanımlaması
static int gpio_switch = 16;
/* Pin durumunu okumak için değişken*/
bool switch_state = true;

//anahtar, led, fan, ampül, sıcaklık sensörü gibi bazı standart cihaz türleri sağlar.
static Switch my_switch("Switch", &gpio_switch);

void sysProvEvent(arduino_event_t *sys_event)
{
    switch (sys_event->event_id) {      
        case ARDUINO_EVENT_PROV_START:
#if CONFIG_IDF_TARGET_ESP32
        Serial.printf("\nİsim ile başlayan provizyon \"%s\" ve PoP \"%s\" de BLE\n", service_name, pop);
        printQR(service_name, pop, "ble");
#else
        Serial.printf("\nİsim ile başlayan provizyon \"%s\" ve PoP \"%s\" de SoftAP\n", service_name, pop);
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
        switch_state = val.val.b;
        (switch_state == false) ? digitalWrite(gpio_switch, LOW) : digitalWrite(gpio_switch, HIGH);
        param->updateAndReport(val);
    }
}

void setup()
{
    Serial.begin(115200);
    pinMode(gpio_0, INPUT);
    pinMode(gpio_switch, OUTPUT);
    digitalWrite(gpio_switch, DEFAULT_POWER_MODE);

    Node my_node;    
    my_node = RMaker.initNode("Deneyap RainMaker Düğümü");

    //Standart anahtar cihazı
    my_switch.addCb(write_callback);
    
    //Düğüme anahtar cihazı ekle  
    my_node.addDevice(my_switch);

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
      
        // Anahtar geri dönüşü işleme
        delay(100);
        int startTime = millis();
        while(digitalRead(gpio_0) == LOW) delay(50);
        int endTime = millis();

        if ((endTime - startTime) > 10000) {
          // Tuşa 10 saniyeden fazla basılırsa, hepsini sıfırlayın
          Serial.printf("Fabrika ayarlarını sıfırla\n");
          RMakerFactoryReset(2);
        } else if ((endTime - startTime) > 3000) {
          Serial.printf("Wi-Fi sıfırla.\n");
          // Tuşa 3 saniyeden fazla, ancak 10'dan az basılırsa, Wi-Fi'yi sıfırlayın
          RMakerWiFiReset(2);
        } else {
          // Cihaz durumunu değiştir
          switch_state = !switch_state;
          Serial.printf("Buton Durumu %s.\n", switch_state ? "true" : "false");
          my_switch.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, switch_state);
          (switch_state == false) ? digitalWrite(gpio_switch, LOW) : digitalWrite(gpio_switch, HIGH);
      }
    }
    delay(100);
}
