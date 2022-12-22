#include "RMakerQR.h"
#ifdef CONFIG_ESP_RMAKER_WORK_QUEUE_TASK_STACK
void printQR(const char *name, const char *pop, const char *transport)
{
    if (!name || !pop || !transport) {
        log_w("QR kodu yüklemesi oluşturulamıyor. Veri eksik.");
        return;
    }
    char payload[150];
    snprintf(payload, sizeof(payload), "{\"ver\":\"%s\",\"name\":\"%s\"" \
                    ",\"pop\":\"%s\",\"transport\":\"%s\"}",
                    PROV_QR_VERSION, name, pop, transport);
    if(Serial){
        Serial.printf("\nESP RainMaker telefon uygulamasından bu QR kodunu taratın.\n");
    }
    qrcode_display(payload);
    if(Serial){
        Serial.printf("QR kodu görünür değilse, aşağıdaki URL'yi bir tarayıcıda kopyala yapıştırın.\n%s?data=%s\n\n", QRCODE_BASE_URL, payload);
    }
}
#endif