/******************************************************************************
 * 
 * 
 * 
 * 
******************************************************************************/

#include <Arduino.h>
#include "mp34dt05.h"
#include "deneyap.h"

long total_read = 0;

void micBegin() {
   
  esp_err_t err;

  i2s_config_t audio_in_i2s_config = {
       .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_PDM),
       .sample_rate = SAMPLE_RATE,
       .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
       .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT, // although the SEL config should be left, it seems to transmit on right
       .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_LSB),
       .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1, // high interrupt priority
       .dma_buf_count = 4,
       .dma_buf_len = BLOCK_SIZE
      };
  
  // This function must be called before any I2S driver read/write operations.
  err = i2s_driver_install(I2S_PORT, &audio_in_i2s_config, 0, NULL);
  if (err != ESP_OK) {
    Serial.printf("Failed installing driver: %d\n", err);
    while (true);
  }
  else {
    Serial.printf("Driver installed \n");
  }

  // configure which pin on the ESP32 is connected to which pin on the mic:
  i2s_pin_config_t audio_in_pin_config = {
      .bck_io_num = I2S_PIN_NO_CHANGE, // not used
      .ws_io_num = MICC,  // IO 15 clock pin
      .data_out_num = I2S_PIN_NO_CHANGE, // Not used
      .data_in_num = MICD   // data pin
  };
  
  err = i2s_set_pin(I2S_PORT, &audio_in_pin_config);
  if (err != ESP_OK) {
    Serial.printf("Failed setting pin: %d\n", err);
    while (true);
  }
  else {
    Serial.printf("Pin set \n");
  }

  //xTaskCreatePinnedToCore(dataProcess, "PDM_reader", 2048, (void *) threshold, 1, NULL, 1);
}

void micRead(size_t *dataReadNumber, void *dataRead) {
  i2s_read(I2S_PORT,
           (char *)dataRead, 
           BLOCK_SIZE,     // the doc says bytes, but its elements.
           dataReadNumber,
           portMAX_DELAY); // no timeout
}

float dataFilter(FilterBeHp2 filter, size_t num_bytes_read, int *samples) {
  int samples_read = num_bytes_read / 4;
  total_read += samples_read;
  float sample;

  for(int i=0; i < samples_read; i++) {
    sample = filter.step((float)samples[i] / INT_MAX);
    //sample = (float)samples[i] / INT_MAX;
    Serial.println((short)(sample * SHRT_MAX));

    return (short)(sample * SHRT_MAX);
  }
}