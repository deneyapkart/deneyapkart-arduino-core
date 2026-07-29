/******************************************************************************
 *
 *
 *
 *
 ******************************************************************************/

#include <Arduino.h>
#include "mp34dt05.h"
#include "deneyap.h"

static I2SClass i2s;

void micBegin() {
  i2s.setPinsPdmRx(MICC, MICD);  // MICC: clock pini, MICD: data pini
  if (!i2s.begin(I2S_MODE_PDM_RX, SAMPLE_RATE, I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_MONO)) {
    Serial.println("I2S (PDM RX) baslatilamadi!");
    while (true) ;
  }
}

void micQuit() {
  i2s.end();
}

void micRead(size_t *dataReadNumber, void *dataRead, size_t byte_count) {
  *dataReadNumber = i2s.readBytes((char *)dataRead, byte_count);
}

int16_t dataFilter(FilterBeHp2 filter, size_t num_bytes_read, int *samples) {
  int samples_read = num_bytes_read / 4;
  float data;
  int total_data = 0;

  for (int i = 0; i < samples_read; i++) {
    data = filter.step((float)samples[i] / INT_MAX);
    total_data += (short)(data * SHRT_MAX);
  }

  return total_data / samples_read;
}
