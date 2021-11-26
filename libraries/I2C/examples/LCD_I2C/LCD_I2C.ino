#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);   // 16 karakter ve 2 satır ekran için LCD adresini 0x27 olarak ayarlayın

void setup(){

   lcd.init();         // LCD'yi başlat
   lcd.backlight();
   lcd.setCursor(0,0);
   lcd.print("Merhaba Dunya!!!");   
   lcd.setCursor(2,1);
   lcd.print("Deneyap Kart");
}


void loop(){

}
