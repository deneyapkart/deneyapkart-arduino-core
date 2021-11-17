#if DENEYAP_KART
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// UUID oluşturmak için aşağıdaki linki kullanabilirsiniz:
// https://www.uuidgenerator.net/
#define SERVICE_UUID                    "42ac05e6-9955-42ef-ab86-87111361d3ea"
#define CHARACTERISTIC_UUID             "6414d63c-5b8b-4b2a-b01e-1e1422b9fa64"

void setup() {
  
  Serial.begin(115200);
  
  BLEDevice::init("DENEYAP KART"); // BLE cihazı başlatıldı
  
  BLEServer *pServer = BLEDevice::createServer(); // BLE server oluşturuldu
  BLEService *pService = pServer->createService(SERVICE_UUID); // BLE servis oluşturuldu
  
  BLECharacteristic *pCharacteristic = pService->createCharacteristic( // BLE karakteristik oluşturuldu
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );
  pCharacteristic->setValue("Merhaba Dunya"); // Karakteristiğin değeri ayarlandı
  
  pService->start(); // Servis başlatıldı
  
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // iPhone bağlantı sorununa yardımcı olan fonksiyonlar
  pAdvertising->setMinPreferred(0x12);
  
  BLEDevice::startAdvertising(); // Yayın başlatıldı

  Serial.println("Karakteristik tanımlandı! Şimdi telefonunuzdan karakteristik değerini okuyabilirsiniz!");
}

void loop() {

  delay(2000);
}
#else
#error Deneyap Mini ile bu uygulama gerceklestirilemez!
#endif