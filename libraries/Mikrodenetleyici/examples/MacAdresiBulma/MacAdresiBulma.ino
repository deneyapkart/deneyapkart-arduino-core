/*
 *   MACadresiBulma örneği,
 *   Bu örnekte, MAC adresi seri port ekrane yazdırmaktadır. 
 *   
 */  
#include <WiFi.h>

void setup(){
  Serial.begin(115200);;
}
 
void loop(){
  Serial.print("MAC adresi:  ");
  Serial.println(WiFi.macAddress());
  delay(1000);
}
