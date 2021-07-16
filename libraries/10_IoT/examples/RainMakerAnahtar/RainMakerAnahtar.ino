//This example demonstrates the ESP RainMaker with a standard Switch device.
#include "RMaker.h"
#include "WiFiESP32.h"
#include "WiFiProv.h"

#define DEFAULT_POWER_MODE true
const char *service_name = "PROV_1234";
const char *pop = "abcd1234";

//GPIO for push button
static int gpio_0 = 0;
//GPIO for virtual device
static int gpio_switch = 16;
/* Variable for reading pin status*/
bool switch_state = true;

//The framework provides some standard device types like switch, lightbulb, fan, temperaturesensor.
static Switch my_switch("Switch", &gpio_switch);

void sysProvEvent(arduino_event_t *sys_event)
{
    switch (sys_event->event_id) {      
        case ARDUINO_EVENT_PROV_START:
#if CONFIG_IDF_TARGET_ESP32
        Serial.printf("\nProvizyon baslatildi, servis ismi: \"%s\" ve PoP: \"%s\" (BLE)\n", service_name, pop);
        printQR(service_name, pop, "ble");
#else
        Serial.printf("\nProvizyon baslatildi, servis ismi: \"%s\" ve PoP \"%s\" (SoftAP)\n", service_name, pop);
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
        Serial.printf("Alinan deger = %s icin %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
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
    my_node = RMaker.initNode("ESP RainMaker Node");

    //Standard switch device
    my_switch.addCb(write_callback);
    
    //Add switch device to the node   
    my_node.addDevice(my_switch);

    //This is optional 
    RMaker.enableOTA(OTA_USING_PARAMS);
    //If you want to enable scheduling, set time zone for your region using setTimeZone(). 
    //The list of available values are provided here https://rainmaker.espressif.com/docs/time-service.html
    // RMaker.setTimeZone("Asia/Shanghai");
    // Alternatively, enable the Timezone service and let the phone apps set the appropriate timezone
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
    if(digitalRead(gpio_0) == LOW) { //Push button pressed

        // Key debounce handling
        delay(100);
        int startTime = millis();
        while(digitalRead(gpio_0) == LOW) delay(50);
        int endTime = millis();

        if ((endTime - startTime) > 10000) {
          // If key pressed for more than 10secs, reset all
          Serial.printf("Fabrika ayarlarina geri donuyor...\n");
          RMakerFactoryReset(2);
        } else if ((endTime - startTime) > 3000) {
          Serial.printf("Wi-Fi ayarlari sifirlaniyor...\n");
          // If key pressed for more than 3secs, but less than 10, reset Wi-Fi
          RMakerWiFiReset(2);
        } else {
          // Toggle device state
          switch_state = !switch_state;
          Serial.printf("Anahtar durumu degisiyor: %s.\n", switch_state ? "true" : "false");
          my_switch.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, switch_state);
          (switch_state == false) ? digitalWrite(gpio_switch, LOW) : digitalWrite(gpio_switch, HIGH);
      }
    }
    delay(100);
}
