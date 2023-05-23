/*
 *   LCD_I2C örneği,
 *   LCD ekranın ilk satırında "Merhaba Dunya!!!"" ikinci satırında "Deneyap Kart" yazdırmaktadır.
 *
 *  ==============================================================================
 *    Bu uygulama örneği için "LiquidCrystal_I2C by Frank de Brabander" kütüphanesi indirilmelidir.  ->https://github.com/johnrickman/LiquidCrystal_I2C<-
 *    Bu uygulama örneği LiquidCrystal_I2C kütüphanesi 1.1.4 versiyonu ile yazılmıştır.
 *  ==============================================================================
*/
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // 0x27:I2C adresi, 16:karakter sayısı, 2:satır sayısı

void setup() {
  lcd.init();  // LCD'yi başlat
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Merhaba Dunya!!!");
  lcd.setCursor(2, 1);
  lcd.print("Deneyap Kart");
}

void loop() {
}