/* 
 *   MagnetikOkumaZamani örneği, 
 *   MagnetikOkumaZamani uygulamasında RTC modülü kullanılmıştır. 
 *    
 *   Bu örnekte Deneyap Kart ve Deneyap Kart 1A kartlarındaki mikrodenetleyiye yaklaştırılan mıknatıs belirlenen değer üstünde mıknatıs değeri okuyunca alınan veriler
 *   seri port ekranına "Magnetik Algılandı: xx:xx xx:xx:xxxx ....." yazdırmaktadır.  
 *   
 *   Bu örnek uygulama diğer Deneyap Geliştirme Kartları kullanılırsa harici magnetik alan sensörü bağlanılmalı ve kodda gerekli değişiklikler yapılmalıdır.   
 *   Bu uygulama örneği için "Deneyap_GercekZamanliSaat" kütüphanesi indirilmelidir.    
*/

#include <Deneyap_GercekZamanliSaat.h>
#include "soc/sens_reg.h"
#include "driver/adc.h"

RTC GercekZamanliSaat;

int hallRead() {
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);
    SET_PERI_REG_MASK(SENS_SAR_TOUCH_CTRL1_REG, SENS_XPD_HALL_FORCE_M);
    SET_PERI_REG_MASK(SENS_SAR_TOUCH_CTRL1_REG, SENS_HALL_PHASE_FORCE_M);
    int hall_value = adc1_get_raw(ADC1_CHANNEL_0);
    CLEAR_PERI_REG_MASK(SENS_SAR_TOUCH_CTRL1_REG, SENS_XPD_HALL_FORCE_M);
    CLEAR_PERI_REG_MASK(SENS_SAR_TOUCH_CTRL1_REG, SENS_HALL_PHASE_FORCE_M);
    return hall_value;
}

void setup() {
    Serial.begin(115200);
    if (!GercekZamanliSaat.begin()) {
        Serial.println("I2C bağlantısı başarısız");
        while (1);
    }
    GercekZamanliSaat.deviceStart();
    GercekZamanliSaat.adjust();
}

void loop() {
    int MagnetikDegeri = hallRead();
    Serial.printf("\nMagnetik Değeri: %d", MagnetikDegeri);
    Serial.println();

    if (MagnetikDegeri > 0) {
        DateTime now = GercekZamanliSaat.now();
        Serial.print("Magnetik Algılandı: ");
        Serial.printf("%02d:%02d:%02d  ", now.hour(), now.minute(), now.second());
        Serial.printf("%02d-%02d-%04d\n", now.day(), now.month(), now.year());
        delay(5000);
    }
    delay(100);
}
