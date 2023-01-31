/*
 *    LedKontrolTelegramBot örneği,
 *    Bu örnekte Telegram BotFather botu kullanılmıştır. 
 *    BotFather aracıyla açtığımız bot ile Deneyap Geliştirme Kartlarındaki dahili LED durumu kontrol edilmektedir.
 *    
 *    Telegram Botu Oluşturma
 *    - BotFather BOTuna giriş yapılır. "/start" yazılır.
 *    - "/newbot" komutu girilir. Bot adı seçilir. Bot adını daha önce seçilmemiş olmaması ve sonunu bot ile bitmesi gerekmektedir.
 *    - Bot onaylandıktan sonra bot token HTTP API verilir ve bu Arduino koduna eklenir.
 *    - Kod  yükledikten sonra oluşturulan bot ekranına girilip "/start" yazılıp kullanılmaya başlanır. 
 *   
 *  ==============================================================================
 *    Bu uygulama örneği için "UniversalTelegramBot by Brian Lough" kütüphanesi indirilmelidir.  ->https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot<-
 *    Bu uygulama örneği UniversalTelegramBot kütüphanesi 1.3.0 versiyonu ile yazılmıştır.
 *  ==============================================================================
*/
#include "WiFi.h"
#include "WiFiClientSecure.h"
#include <UniversalTelegramBot.h>

#define WIFI_SSID "*******"      // Bağlantı kurulacak Wi-Fi ağı adı
#define WIFI_PASSWORD "*******"  // Bağlantı kurulacak Wi-Fi ağı şifresi
#define BOT_TOKEN "*******"      // Telegram BOT Token (HTTP API Botfather tarafından alınacak)

const unsigned long BOT_MTBS = 1000;

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime;

int ledStatus = 0;

void handleNewMessages(int numNewMessages) {
  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "")
      from_name = "Guest";

    if (text == "/ledOn") {             // Telegram botuna "/ledOn" yazılırsa
      digitalWrite(LED_BUILTIN, HIGH);  // Deneyap Geliştirme Kartlarındaki dahili LEDin yanması
      ledStatus = 1;
      bot.sendMessage(chat_id, "Led açık", "");
    }

    if (text == "/ledOff") {           // Telegram botuna "/ledOff" yazılırsa
      digitalWrite(LED_BUILTIN, LOW);  // Deneyap Geliştirme Kartlarındaki dahili LEDin sönmesi
      ledStatus = 0;
      bot.sendMessage(chat_id, "Led kapalı", "");
    }

    if (text == "/status") {
      if (ledStatus) {
        bot.sendMessage(chat_id, "Led açık", "");
      } else {
        bot.sendMessage(chat_id, "Led kapalı", "");
      }
    }

    if (text == "/start") {
      String welcome = "Deneyap Telegram Botuna hosgeldin " + from_name + ".\n";
      welcome += "Led Durum Kontrol Ornek Uygulamasi.\n\n";
      welcome += "/ledOn : Led acmak icin bu komutu kullanin\n";
      welcome += "/ledOff : Led kapatmak icin bu komutu kullanin\n";
      welcome += "/status : Led durunu gormek icin bu komutu kullanin\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
  }
}

void setup() {
  Serial.begin(115200);          // Seri haberleşme baslatılması
  pinMode(LED_BUILTIN, OUTPUT);  // Deneyap Geliştirme Kartlarındaki dahili LED çıkış olarak ayarlanması

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);  // Wi-Fi bağlatısının gerçekleştirilmesi
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  configTime(0, 0, "pool.ntp.org");
  time_t now = time(nullptr);
  while (now < 24 * 3600) {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);
}

void loop() {
  if (millis() - bot_lasttime > BOT_MTBS) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages) {
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    bot_lasttime = millis();
  }
}
