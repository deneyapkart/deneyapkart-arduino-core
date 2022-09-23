/*
 *  SDKartTimeServer örneği,
 *  Bu uygulamada seri port ekrande tarih ve saati yazdırmaktadır. SDKartTimeServer uygulamada SD karta bir tane "mydir" isimli bir boş klasör ve holle.txt uzantılı dosya açmaktadır. 
 *  Dosyada hello world! yazmaktadır. seri port ekrane hızını ve kaç bayt okunduğu yazmaktadır.
 * 
 *  Deneyap Kart ve Deneyap Kart 1A için CS(SS) pini D4 pinine bağlanması gerekmektedir.
 *  Deneyap Mini Kartı için CS(SS) pini D10 pinine bağlanması gerekmektedir.
 *  
*/
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include <time.h> 
#include <WiFi.h>

const char* ssid     = "********";
const char* password = "********";

long timezone = 1; 
byte daysavetime = 1;

void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    Serial.printf("Dizinler listeleniyor: %s\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("Dizin acma islemi basarisiz");
        return;
    }
    if(!root.isDirectory()){
        Serial.println("Boyle bir dizin yok");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.print (file.name());
            time_t t= file.getLastWrite();
            struct tm * tmstruct = localtime(&t);
            Serial.printf("  SON YAZMA ISLEMI: %d-%02d-%02d %02d:%02d:%02d\n",(tmstruct->tm_year)+1900,( tmstruct->tm_mon)+1, tmstruct->tm_mday,tmstruct->tm_hour , tmstruct->tm_min, tmstruct->tm_sec);
            if(levels){
                listDir(fs, file.path(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("  SIZE: ");
            Serial.print(file.size());
            time_t t= file.getLastWrite();
            struct tm * tmstruct = localtime(&t);
            Serial.printf("  SON YAZMA ISLEMI: %d-%02d-%02d %02d:%02d:%02d\n",(tmstruct->tm_year)+1900,( tmstruct->tm_mon)+1, tmstruct->tm_mday,tmstruct->tm_hour , tmstruct->tm_min, tmstruct->tm_sec);
        }
        file = root.openNextFile();
    }
}

void createDir(fs::FS &fs, const char * path){
    Serial.printf("Creating Dir: %s\n", path);
    if(fs.mkdir(path)){
        Serial.println("Dizin olusturuldu");
    } else {
        Serial.println("Dizin olusturma islemi basarisiz");
    }
}

void removeDir(fs::FS &fs, const char * path){
    Serial.printf("Removing Dir: %s\n", path);
    if(fs.rmdir(path)){
        Serial.println("Dizin silindi");
    } else {
        Serial.println("Dizin silme islemi basarisiz");
    }
}

void readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if(!file){
        Serial.println("Okuma islemi icin dosya acilamadi");
        return;
    }

    Serial.print("Dosyadan okuma: ");
    while(file.available()){
        Serial.write(file.read());
    }
    file.close();
}

void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Dosya yaziliyor: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Yazma islemi icin dosya acilamadi");
        return;
    }
    if(file.print(message)){
        Serial.println("Dosya yazildi");
    } else {
        Serial.println("Dosya yazma islemi basarisiz");
    }
    file.close();
}

void appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Appending to file: %s\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Ekleme islemi icin dosya acilamadi");
        return;
    }
    if(file.print(message)){
        Serial.println("Ekleme islemi basarili");
    } else {
        Serial.println("Ekleme islemi basarisiz");
    }
    file.close();
}

void renameFile(fs::FS &fs, const char * path1, const char * path2){
    Serial.printf("Renaming file %s to %s\n", path1, path2);
    if (fs.rename(path1, path2)) {
        Serial.println("Dosya ismi degistirildi");
    } else {
        Serial.println("Dosya ismi degistirme islemi basarisiz");
    }
}

void deleteFile(fs::FS &fs, const char * path){
    Serial.printf("Deleting file: %s\n", path);
    if(fs.remove(path)){
        Serial.println("Dosya silindi");
    } else {
        Serial.println("Dosya silme islemi basarisiz");
    }
}

void setup(){
    Serial.begin(115200);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.println();
    Serial.print("Aga baglaniyor ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Aga baglanildi");
    Serial.println("IP adres: ");
    Serial.println(WiFi.localIP());
    Serial.println("Time Server'a baglaniliyor");
	configTime(3600*timezone, daysavetime*3600, "time.nist.gov", "0.pool.ntp.org", "1.pool.ntp.org");
	struct tm tmstruct ;
    delay(2000);
    tmstruct.tm_year = 0;
    getLocalTime(&tmstruct, 5000);
	Serial.printf("\nSu an : %d-%02d-%02d %02d:%02d:%02d\n",(tmstruct.tm_year)+1900,( tmstruct.tm_mon)+1, tmstruct.tm_mday,tmstruct.tm_hour , tmstruct.tm_min, tmstruct.tm_sec);
    Serial.println("");
    
    if(!SDCard.begin()){
        Serial.println("SD Kart baglantisi basarisiz");
        return;
    }
    uint8_t cardType = SDCard.cardType();

    if(cardType == CARD_NONE){
        Serial.println("SD Kart bagli degil");
        return;
    }

    Serial.print("SD Kart Turu: ");
    if(cardType == CARD_MMC){
        Serial.println("MMC");
    } else if(cardType == CARD_SD){
        Serial.println("SDSC");
    } else if(cardType == CARD_SDHC){
        Serial.println("SDHC");
    } else {
        Serial.println("TANIMSIZ");
    }

    uint64_t cardSize = SDCard.cardSize() / (1024 * 1024);
    Serial.printf("SD Kart Boytu: %lluMB\n", cardSize);

    listDir(SDCard, "/", 0);
    removeDir(SDCard, "/mydir");
    createDir(SDCard, "/mydir");
    deleteFile(SDCard, "/hello.txt");
    writeFile(SDCard, "/hello.txt", "Hello ");
    appendFile(SDCard, "/hello.txt", "World!\n");
	listDir(SDCard, "/", 0);
}

void loop(){
}
