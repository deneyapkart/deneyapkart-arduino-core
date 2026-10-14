#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN  D10
#define RST_PIN D0

MFRC522 mfrc522(SS_PIN, RST_PIN);

String yetkiliUID = "3B AA 43 0E";

String kartUIDOku() {

  String uid = "";

  for (byte i = 0; i < mfrc522.uid.size; i++) {

    if (i > 0) {
      uid += " ";
    }

    if (mfrc522.uid.uidByte[i] < 0x10) {
      uid += "0";
    }

    uid += String(mfrc522.uid.uidByte[i], HEX);
  }

  uid.toUpperCase();

  return uid;
}

void setup() {

  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("RFID sistemi baslatiliyor...");
  
  rgbLedWrite(RGB_BUILTIN, 0, 0, 0);

  SPI.begin(SCK, MISO, MOSI, SS_PIN);

  mfrc522.PCD_Init();

  delay(500);

  byte version = mfrc522.PCD_ReadRegister(MFRC522::VersionReg);

  Serial.print("RC522 VersionReg: 0x");
  Serial.println(version, HEX);

  if (version == 0x00 || version == 0xFF) {

    Serial.println("HATA: RC522 bulunamadi!");

    rgbLedWrite(RGB_BUILTIN, 255, 0, 0);

  } else {

    Serial.println("RC522 BASARIYLA BULUNDU!");
    Serial.println("RFID kartinizi yaklastirin...");

    rgbLedWrite(RGB_BUILTIN, 0, 0, 0);
  }
}

void loop() {

  // Yeni kart var mı?
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  String strID = kartUIDOku();

  Serial.println();
  Serial.print("Kart UID: ");
  Serial.println(strID);

  
  if (strID == yetkiliUID) {

    Serial.println("YETKILI KART!");
    Serial.println("Giris basarili.");


    rgbLedWrite(RGB_BUILTIN, 0, 255, 0);

  } else {

    Serial.println("YETKISIZ KART!");
    Serial.println("Giris reddedildi.");

    // KIRMIZI
    rgbLedWrite(RGB_BUILTIN, 255, 0, 0);
  }
 
  delay(2000);

  // LED kapansın
  rgbLedWrite(RGB_BUILTIN, 0, 0, 0);

  
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();

  delay(500);

  Serial.println();
  Serial.println("Yeni kart bekleniyor...");
}