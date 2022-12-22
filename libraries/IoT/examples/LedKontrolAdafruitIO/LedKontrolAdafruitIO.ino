/*
 *    LedKontrolAdafruitIO örneği,
 *    Bu örnekte AdafruitIO uygulaması ile MQTT protokolü kullanalarak yazılmıştır.
 *    AdafruitIO web tabanlı bulut(https://io.adafruit.com/) hesabı açmanız gerekmektedir. Hesap açtıktan sonra Dashboards oluşturulmalıdır.
 *    Daha sonra "feeds" nesneleri ekleyip veri alınıp veri gönderilecektir.
 *
 *    Deneyap Geliştirme Kartlarındaki dahili LED durumu AdafruitIO web tabanlı bulut ekranından konrol edilmektedir.
 *    Aynı zamanda Deneyap Geliştirme Kartlarındaki dahili buton durumu AdafruitIO web tabanlı bulut ekranında gözlemlenmektedir.
*/
#include "WiFi.h"
#include <Adafruit_MQTT.h> // Adafruit MQTT Library kütüphanesi indirilmelidir
#include <Adafruit_MQTT_Client.h>

#define WLAN_SSID       "*******"         // Bağlantı kurulacak Wi-Fi ağı adı
#define WLAN_PASS       "*******"         // Bağlantı kurulacak Wi-Fi ağı şifresi
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                  
#define AIO_USERNAME    "*******"         // AdafruitIO kullanıcı ismi, AdafruitIO bulut ekranındaki anahtar simgesinde yer almaktadır
#define AIO_KEY         "*******"         // AdafruitIO kullanıcı anahtarı, AdafruitIO bulut ekranındaki anahtar simgesinde yer almaktadır

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Subscribe ledState = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/led-durumu");  // AdafruitIO'da oluşturulan Dashboards ekranında "Create New Block" kısmına tıklayarak "Toggle" feeds nesnesi eklenmelidir
Adafruit_MQTT_Publish button = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/buton-durumu");      // AdafruitIO'da oluşturulan Dashboards ekranında "Create New Block" kısmına tıklayarak "Gauge" feeds nesnesi eklenmelidir

void setup() {
  pinMode(LED_BUILTIN,OUTPUT); // Deneyap Geliştirme Kartlarındaki dahili LED çıkış olarak ayarlanması
  pinMode(GPKEY,INPUT);        // Deneyap Geliştirme Kartlarındaki dahili Genel amaçlı buton pini giriş olarak ayarlanması            
  Serial.begin(115200);        // Seri haberleşme başlatılması
  delay(10);
  
  WiFi.begin(WLAN_SSID, WLAN_PASS); // Wi-Fi bağlatısının gerçekleştirilmesi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  mqtt.subscribe(&ledState);
}

void loop() {
  MQTT_connect();
  /* AdafruitIO bulutdan gelen veriye göre Deneyap Geliştirme Kartlarındaki dahili LEDin yanması */
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if(subscription == &ledState)  {
      if (!strcmp((char*) ledState.lastread, "ON")) {
        digitalWrite(LED_BUILTIN, HIGH);
      } else {
        digitalWrite(LED_BUILTIN, LOW);
      }
    }
  }

  /* Buton verisinin AdafruitIO bulutuna gönderilmesi*/
  int ButtonValue = digitalRead(GPKEY); 
  button.publish(ButtonValue);
  delay(250);
}

/* MQTT sunucusuna bağlanması */
void MQTT_connect() {
  int8_t ret;
  if (mqtt.connected()) {
    return;
  }
  Serial.print("Bulut sistemine baglaniliyor... ");
  uint8_t count = 3;
  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("3 saniye icinde tekrar baglanti denemesi gerceklesecek...");
    mqtt.disconnect();
    delay(5000); 
    count = count - 1 ;
    if (count == 0) {
      esp_restart();
    }
  }
  Serial.println("Bulut sistemine baglanildi!");
}