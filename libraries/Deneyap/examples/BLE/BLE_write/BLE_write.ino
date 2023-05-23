/*
 *  Bluetooth BLE_write örneği,
 *  Bu uygulama örneği için telefona BLE Scanner, nRF Connect veya LightBlue gibi bir uygulama indirilmesi gerekmektedir. 
 *  Yazılım karta yüklendikten sonra telefondaki uygulama ile DeneyapKart ile bağlantısını gerçekleştirilmelidir. 
 *  seri port ekrana yazılan karakterler telefon uygulamasında görünmektedir.
 *  Deneyap Mini Kartında dahili Bluetooth haberleşme özelliği bulunmamaktadır.   
*/
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// UUID oluşturmak için aşağıdaki linki kullanabilirsiniz:
// https://www.uuidgenerator.net/
#define SERVICE_UUID                    "7cdddbbf-b5a6-4c20-aaf1-f873fa503243"
#define CHARACTERISTIC_UUID             "47332d64-d60d-4831-b135-aadbb34e2b92"

class MyCallbacks: public BLECharacteristicCallbacks {
  
  void onWrite(BLECharacteristic *pCharacteristic) { // Yazma isteği için callback fonksiyonu
      
    std::string value = pCharacteristic->getValue(); // Karakteristiğin değeri alındı

    if (value.length() > 0) { // Karakteristik değerinin uzunluğu (karakter cinsinden) 0'dan büyük ise
      
      Serial.println("*********");
      Serial.print("Yeni Deger: ");
      
      for (int i = 0; i < value.length(); i++) // Karakteristik değeri seri monitöre yazıldı
        Serial.print(value[i]);

      Serial.println();
      Serial.println("*********");
    }
  }
};

void setup() {
  
  Serial.begin(115200);

  Serial.println("1- Telefonunuza bir BLE tarayici uygulamasi(BLE Scanner, nRF Connect, LightBlue vb.) indirin ve yukleyin");
  Serial.println("2- Uygulamada BLE cihazlarini tarayin");
  Serial.println("3- DENEYAP KART'a baglanin");
  Serial.println("4- Oluşturduğunuz servisin içerisindeki karakteristiğe gidin ve bir şeyler yazın");  

  BLEDevice::init("DENEYAP KART"); // BLE cihazı başlatıldı
  
  BLEServer *pServer = BLEDevice::createServer(); // BLE server oluşturuldu
  BLEService *pService = pServer->createService(SERVICE_UUID); // BLE servis oluşturuldu

  BLECharacteristic *pCharacteristic = pService->createCharacteristic( // BLE karakteristik oluşturuldu
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );
  pCharacteristic->setCallbacks(new MyCallbacks()); // Karakteristik için callback ayarlandı
  pCharacteristic->setValue("Merhaba Dunya"); // Karakteristiğin değeri ayarlandı
  
  pService->start(); // Servis başlatıldı

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start(); // Yayın başlatıldı
}

void loop() {
 
  delay(2000);
}
