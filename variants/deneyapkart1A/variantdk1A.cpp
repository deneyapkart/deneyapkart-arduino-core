#include "Arduino.h"

static const uint8_t DK_1A_GPIO_PINS[] = {
    D0,  D1,  D4,  D5,  D6,  D7, D8,  D9,
    D10, D11, D12, D13, D14, D15, DAC1,
    DAC2, A0, A1, A2, A3, A4, A5
};

static const uint8_t DK_1A_GPIO_PIN_COUNT = 24;

extern "C" void initVariant() {
    for (uint8_t i = 0; i < DK_1A_GPIO_PIN_COUNT; i++) {
        pinMode(DK_1A_GPIO_PINS[i], OUTPUT);
        digitalWrite(DK_1A_GPIO_PINS[i], LOW);
    }
}
