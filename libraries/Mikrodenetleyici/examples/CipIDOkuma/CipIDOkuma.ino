/*
 *   CipIDOkuma örneği,
 *   Bu örnekte, ESP32 veya ESP32S2 çip modelini, çipte kaç çekirdek olduğunu ve çip ID seri terminale yazdırmaktadır. 
 *   
 */	
uint32_t chipId = 0;

void setup() {
	Serial.begin(115200);
}

void loop() {
  
	for(int i=0; i<17; i=i+8) {
	  chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
	}
 
	Serial.printf("ESP32 Çip modeli = %s Rev %d\n", ESP.getChipModel(), ESP.getChipRevision());
	Serial.printf("Bu çipte %d çekirdek var\n", ESP.getChipCores());
  Serial.print("Çip ID: "); Serial.println(chipId);
  
	delay(3000);
}
