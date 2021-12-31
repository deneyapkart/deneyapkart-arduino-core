#include "mp34dt05.h"
#define threshold -200
int samples[BLOCK_SIZE];
FilterBeHp2 filter;

void setup() {
  Serial.begin(1000000);
  pinMode(LEDB, OUTPUT);
  pinMode(D0, OUTPUT);
  micBegin();
}

void loop() {
  delay(10); 
  size_t num_bytes_read = 0;
  micRead(&num_bytes_read, samples);

  if (num_bytes_read > 0) {
    float data = dataFilter(filter, num_bytes_read, samples);
    if(data < threshold)
    {
      digitalWrite(LEDB, LOW);
      digitalWrite(D0, LOW);     
    }
    else
    {
      digitalWrite(LEDB, HIGH);
      digitalWrite(D0, HIGH);
    }
  }
}
