#define AMP_PIN A0
#define VOLT_PIN A1
#define VIBR_PIN A2

#define DOUT_PIN 3
#define SCK_PIN 2

struct Data {
  float thrust = 0;  // тяга
  float amperage = 0;
  float voltage = 0;
  uint16_t vibration = 0;
  byte temp = 0;
};

#include "Timer.h"
Timer sensorsTmr(100, true);
Timer sendTmr(100, true);