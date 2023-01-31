/*
 *   RFIDkartUIDokuma örneği,
 *   RFIDkartUIDokuma uygulamasında RFID NFC modülüne kart okutulunca kartın UIDsini seri port ekrane yazdırmaktadır.
 *   Kart UIDnizi okunduğunda harici olarak D12 pinine bağlanan LED yanmaktadır. 
 *
 *  ==============================================================================
 *    Bu uygulama örneği için "MFRC522 by GithubCommunity" kütüphanesi indirilmelidir.  ->https://github.com/miguelbalboa/rfid<-
 *    Bu uygulama örneği MFRC522 kütüphanesi 1.4.8 versiyonu ile yazılmıştır.
 *  ==============================================================================
*/
#include <MFRC522.h>

MFRC522 mfrc522(D4, D0);  //D4:SDA(CS), D0:RST

/* Kart UID yazıldı*/
String fnc_user_ID() {
  mfrc522.PICC_ReadCardSerial();
  String user_ID = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    user_ID += (mfrc522.uid.uidByte[i] < 0x10 ? "0" : " ") + String(mfrc522.uid.uidByte[i], HEX);
  }
  return user_ID;
}

void setup() {
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.begin(115200);
  pinMode(D12, OUTPUT);
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    Serial.print("Kart UID: ");
    String strID = fnc_user_ID();
    Serial.println(strID);  //Kart UID seri port ekrane yazıldı
    Serial.println();

    /*Kart UIDnizi okuduğunda LED yanmaktadır*/
    if (strID.indexOf("33 38 1f 2e") >= 0) {  //Kendi KART UIDnizi yazın
      digitalWrite(D12, HIGH);
    }
    delay(1000);
  } else {
    digitalWrite(D12, LOW);
  }
}