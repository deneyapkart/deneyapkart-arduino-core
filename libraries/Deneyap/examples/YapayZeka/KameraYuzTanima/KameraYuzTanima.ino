/*
 *  KameraYuzTanima örneği,
 *  Bu örnek WiFi ağı ve şifresini girdikten sonra ağa bağlanacaktır. 
 *  WiFi ağına bağlandıktan sonra seri port ekranından görüntünün yayınlanacağı IP adresi yazılacaktır.
 * 
 *  Bu örnek kamera konnektörü dahili olan Deneyap Geliştirme Kartlarını desteklemektedir.  
*/
// ---------->>>>>>>>>> YUKLEME YAPILAMDAN DIKKAT EDILMESI GEREKEN HUSUS <<<<<<<<<<----------
// "Araclar->Partition Scheme->Huge APP" secilmeli //
// "Tools->Partition Scheme->Huge APP" secilmeli //

#include "WiFi.h"
#include "esp_camera.h"

const char* ssid = "*********";      // Baglanti kurulacak Wi-Fi agi adi
const char* password = "*********";  // Baglanti kurulacak Wi-Fi agi sifresi

void cameraInit(void);
void startCameraServer();

void setup() {
  Serial.begin(115200);  // Hata ayiklamak icin seri port ekran baslatildi
  Serial.setDebugOutput(true);
  Serial.println();

  cameraInit();  // Kamera konfigurasyonu yapildi

  WiFi.begin(ssid, password);  // Wi-Fi agina baglaniliyor

  while (WiFi.status() != WL_CONNECTED) {  // Baglanti saglanan kadar bekleniyor
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Wi-Fi agina baglanildi ");

  startCameraServer();  // Kamera server baslatildi

  Serial.print("Kamera hazir! Baglanmak icin 'http://");  // Baglanti saglandi
  Serial.print(WiFi.localIP());                           // Goruntunun yayinlanacagi IP adresi seri port ekranına yaziliyor
  Serial.println("' adresini kullaniniz");
}

void loop() {
  delay(1000);
}

void cameraInit(void) {
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = CAMD2;
  config.pin_d1 = CAMD3;
  config.pin_d2 = CAMD4;
  config.pin_d3 = CAMD5;
  config.pin_d4 = CAMD6;
  config.pin_d5 = CAMD7;
  config.pin_d6 = CAMD8;
  config.pin_d7 = CAMD9;
  config.pin_xclk = CAMXC;
  config.pin_pclk = CAMPC;
  config.pin_vsync = CAMV;
  config.pin_href = CAMH;
  config.pin_sscb_sda = CAMSD;
  config.pin_sscb_scl = CAMSC;
  config.pin_pwdn = -1;
  config.pin_reset = -1;
  config.xclk_freq_hz = 15000000;
  config.frame_size = FRAMESIZE_UXGA;
  config.pixel_format = PIXFORMAT_JPEG;
  //config.pixel_format = PIXFORMAT_RGB565; // for face detection/recognition
  config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;
  config.fb_location = CAMERA_FB_IN_PSRAM;
  config.jpeg_quality = 12;
  config.fb_count = 1;

  //init with high specs to pre-allocate larger buffers                     for larger pre-allocated frame buffer.
  if (config.pixel_format == PIXFORMAT_JPEG) {
    if (psramFound()) {
      config.jpeg_quality = 10;
      config.fb_count = 2;
      config.grab_mode = CAMERA_GRAB_LATEST;
    } else {
      // Limit the frame size when PSRAM is not available
      config.frame_size = FRAMESIZE_SVGA;
      config.fb_location = CAMERA_FB_IN_DRAM;
    }
  } else {
    // Best option for face detection/recognition
    config.frame_size = FRAMESIZE_240X240;
#if CONFIG_IDF_TARGET_ESP32S3
    config.fb_count = 2;
#endif
  }

  // Camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  sensor_t* s = esp_camera_sensor_get();
  // Drop down frame size for higher initial frame rate
  s->set_framesize(s, FRAMESIZE_QVGA);
}
