
// Adafruit IO kullanarak IoT tabanli uzaktan led kontrol uygulamasi 

#include "deneyap.h"
#include "WiFiESP32.h"
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

#define WLAN_SSID       "***********"         // Baglanti kurulacak Wi-Fi agi adi
#define WLAN_PASS       "***********"         // Baglanti kurulacak Wi-Fi agi sifresi
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                  
#define AIO_USERNAME    "***********"         // Adafruit IO kullanici ismi
#define AIO_KEY         "***********"         // Adafruit IO kullanici anahtari

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);       
Adafruit_MQTT_Subscribe kirmizi_led = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/kirmizi-led");
Adafruit_MQTT_Subscribe yesil_led = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/yesil-led");
Adafruit_MQTT_Subscribe mavi_led = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/mavi-led");

void setup() {
  expanderInit();                         
  pinMode(BUILTIN_LED_R, OUTPUT);         
  pinMode(BUILTIN_LED_G, OUTPUT);         
  pinMode(BUILTIN_LED_B, OUTPUT);         
  Serial.begin(115200);
  delay(10);
  
  Serial.println(); Serial.println();
  Serial.print(WLAN_SSID);
  Serial.print(" kablosuz agina baglaniliyor");
  
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Kablosuz aga baglanildi!");
  Serial.print("IP adresi: "); Serial.println(WiFi.localIP());
  mqtt.subscribe(&kirmizi_led);
  mqtt.subscribe(&yesil_led);
  mqtt.subscribe(&mavi_led);  
}

void loop() {
  MQTT_connect();
  Adafruit_MQTT_Subscribe *subscription;
  
  while ((subscription = mqtt.readSubscription(5000))) 
  {
    if(subscription == &kirmizi_led) 
    {
      Serial.print(F("Gelen mesaj: "));
      Serial.println((char *)kirmizi_led.lastread);

      if (!strcmp((char*) kirmizi_led.lastread, "AÇIK"))
      {
        writeRedLed(HIGH);
      }
      else
      {
        writeRedLed(LOW);
      }
    }
    else if(subscription == &yesil_led) 
    {
      Serial.print(F("Gelen mesaj: "));
      Serial.println((char *)yesil_led.lastread);

      if (!strcmp((char*) yesil_led.lastread, "AÇIK"))
      {
        writeGreenLed(HIGH);
      }
      else
      {
        writeGreenLed(LOW);
      }
    }
    else if(subscription == &mavi_led) 
    {
      Serial.print(F("Gelen mesaj: "));
      Serial.println((char *)mavi_led.lastread);

      if (!strcmp((char*) mavi_led.lastread, "AÇIK"))
      {
        writeBlueLed(HIGH);
      }
      else
      {
        writeBlueLed(LOW);
      }
    }
  }
}

void MQTT_connect() {
  int8_t ret;
  if (mqtt.connected()) 
  {
    return;
  }
  
  Serial.print("Bulut sistemine baglaniliyor... ");
  uint8_t count = 3;
  
  while ((ret = mqtt.connect()) != 0) 
  {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("3 saniye icinde tekrar baglanti denemesi gerceklesecek...");
    mqtt.disconnect();
    delay(5000); 
    count = count - 1 ;

    if (count == 0) 
    {
      esp_restart();
    }
  }
  
  Serial.println("Bulut sistemine baglanildi!");
}
