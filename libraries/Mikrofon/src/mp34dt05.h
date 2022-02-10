#ifndef _MP34DT05_H_
#define _MP34DT05_H_

#include "driver/i2s.h"
#include "dsps_fft2r.h"

#define I2S_PORT I2S_NUM_0
#define BUFFER_SIZE 512
#define SAMPLE_RATE 24000

// http://www.schwietering.com/jayduino/filtuino/index.php?characteristic=be&passmode=hp&order=2&usesr=usesr&sr=24000&frequencyLow=100&noteLow=&noteHigh=&pw=pw&calctype=float&run=Send
//High pass bessel filter order=2 alpha1=0.0041666666666667 
class FilterBeHp2
{
public:
  FilterBeHp2()
  {
    v[0]=0.0;
    v[1]=0.0;
  }
private:
  float v[3];
public:
  float step(float x) //class II 
  {
    v[0] = v[1];
    v[1] = v[2];
    v[2] = (9.823849154958753660e-1 * x)
       + (-0.96497792085018785357 * v[0])
       + (1.96456174113331383246 * v[1]);
    return 
       (v[0] + v[2])
      - 2 * v[1];
  }
};

void micBegin();
void micRead(size_t *dataReadNumber, void *dataRead);
int16_t dataFilter(FilterBeHp2 filter, size_t num_bytes_read, int *samples);

#endif // _MP34DT05_H_