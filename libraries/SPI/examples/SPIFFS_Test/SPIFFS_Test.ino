/*
 *   SPIFFS_Test örneği,
 *   Bu örnekte karta bir tane "mydir" isimli bir boş klasör ve hello.txt uzantılı dosya açmaktadır. 
 *   Dosyada hello world! yazmaktadır. seri port ekrane hızını ve kaç bayt okunduğu yazmaktadır.
 * 
 */
#include "FS.h"
#include "SPIFFS.h"

/*Örneği ilk çalıştırdığınızda SPIFFS'yi biçimlendirmeniz 
    veya bir bölüm oluşturmak için SPIFFS eklentisini kullanmanız gerekir.
    https://github.com/me-no-dev/arduino-esp32fs-plugin */
#define FORMAT_SPIFFS_IF_FAILED false

void listDir(fs::FS &fs, const char *dirname, uint8_t levels) {
  Serial.printf("Dizin listesi: %s\n", dirname);

  File root = fs.open(dirname);
  if (!root) {
    Serial.println("Dizin acma islemi basarisiz");
    return;
  }
  if (!root.isDirectory()) {
    Serial.println("Boyle bir dizin yok");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if (levels) {
        listDir(fs, file.path(), levels - 1);
      }
    } else {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("  SIZE: ");
      Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}

void createDir(fs::FS &fs, const char *path) {
  Serial.printf("Dizin olusturuluyor: %s\n", path);
  if (fs.mkdir(path)) {
    Serial.println("Dizin olusturuldu");
  } else {
    Serial.println("Dizin olusturma islemi basarisiz");
  }
}

void removeDir(fs::FS &fs, const char *path) {
  Serial.printf("Dizin kaldırma: %s\n", path);
  if (fs.rmdir(path)) {
    Serial.println("Dizin silindi");
  } else {
    Serial.println("Dizin silme islemi basarisiz");
  }
}

void readFile(fs::FS &fs, const char *path) {
  Serial.printf("Dosya okuma: %s\n", path);

  File file = fs.open(path);
  if (!file) {
    Serial.println("Dosyadan okuma yapilamadi");
    return;
  }

  Serial.print("Dosyadan okunuyor: ");
  while (file.available()) {
    Serial.write(file.read());
  }
  file.close();
}

void writeFile(fs::FS &fs, const char *path, const char *message) {
  Serial.printf("Dosya yazma: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Dosyaya yazilamadi");
    return;
  }
  if (file.print(message)) {
    Serial.println("Dosyaya yazildi");
  } else {
    Serial.println("Yazma islemi basarisiz");
  }
  file.close();
}

void appendFile(fs::FS &fs, const char *path, const char *message) {
  Serial.printf("Dosya ekleme: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if (!file) {
    Serial.println("Ekleme islemi icin dosya acilamadi");
    return;
  }
  if (file.print(message)) {
    Serial.println("Ekleme islemi basarili");
  } else {
    Serial.println("Ekleme islemi basarisiz");
  }
  file.close();
}

void renameFile(fs::FS &fs, const char *path1, const char *path2) {
  Serial.printf("Dosya ismi degistiriliyor %s to %s\n", path1, path2);
  if (fs.rename(path1, path2)) {
    Serial.println("Dosya ismi degistirildi");
  } else {
    Serial.println("Dosya ismi degistirme islemi basarisiz");
  }
}

void deleteFile(fs::FS &fs, const char *path) {
  Serial.printf("Dosya siliniyor: %s\n", path);
  if (fs.remove(path)) {
    Serial.println("Dosya silindi");
  } else {
    Serial.println("Silme islemi basarisiz");
  }
}

void testFileIO(fs::FS &fs, const char *path) {
  File file = fs.open(path);
  static uint8_t buf[512];
  size_t len = 0;
  uint32_t start = millis();
  uint32_t end = start;
  if (file) {
    len = file.size();
    size_t flen = len;
    start = millis();
    while (len) {
      size_t toRead = len;
      if (toRead > 512) {
        toRead = 512;
      }
      file.read(buf, toRead);
      len -= toRead;
    }
    end = millis() - start;
    Serial.printf("%u ms\n hiz ile %u bayt okundu", end, flen);
    file.close();
  } else {
    Serial.println("Okuma islemi basarisiz");
  }


  file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Okuma islemi basarisiz");
    return;
  }

  size_t i;
  start = millis();
  for (i = 0; i < 2048; i++) {
    file.write(buf, 512);
  }
  end = millis() - start;
  Serial.printf("%u ms\n hiz ile %u bayt yazildi", end, 2048 * 512);
  file.close();
}

void setup() {
  Serial.begin(115200);
  if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
    Serial.println("SPIFFS okuma başarısız");
    return;
  }

  listDir(SPIFFS, "/", 0);
  createDir(SPIFFS, "/mydir");
  listDir(SPIFFS, "/", 0);
  removeDir(SPIFFS, "/mydir");
  listDir(SPIFFS, "/", 2);
  writeFile(SPIFFS, "/hello.txt", "Hello ");
  appendFile(SPIFFS, "/hello.txt", "World!\n");
  readFile(SPIFFS, "/hello.txt");
  deleteFile(SPIFFS, "/foo.txt");
  renameFile(SPIFFS, "/hello.txt", "/foo.txt");
  readFile(SPIFFS, "/foo.txt");
  testFileIO(SPIFFS, "/test.txt");
  Serial.printf("Toplam alan: %lluMB\n", SPIFFS.totalBytes() / (1024 * 1024));
  Serial.printf("Kullanılan alan: %lluMB\n", SPIFFS.usedBytes() / (1024 * 1024));
}

void loop() {
}
