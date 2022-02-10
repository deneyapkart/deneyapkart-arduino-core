/*
 *   LCD örneği,
 *   LCD ekranın ilk satırında Deneyap kart ikinci satırında T3 Vakfı 2022 yazdırmaktadır.
 *    
 */
#include "Adafruit_LiquidCrystal.h"

/*
 * Sırasıyla pinler ( RS, EN, D4, D5, D6, D7 ) şeklindedir. 
 * V0 pini 10k potansiyonometre ile bağlanmalıdır
*/
Adafruit_LiquidCrystal lcd(D10, D13, D15, D12, D11, D14); 

void setup()
{
     lcd.begin(16, 2);
     lcd.clear();
     lcd.print("DENEYAP KART");
     lcd.setCursor(0,1); 
     lcd.print ("T3 VAKFI 2022");
}
void loop() {
    
}
