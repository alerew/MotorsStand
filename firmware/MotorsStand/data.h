#define AMP_PIN A0
#define VOLT_PIN A1
#define VIBR_PIN A2
#define MOTOR_PIN 5

#define DOUT_PIN 3
#define SCK_PIN 2

#define S1_PIN 6
#define S2_PIN 7
#define BTN_PIN 8

struct Data {
  float thrust = 0;  // тяга
  float amperage = 0;
  float voltage = 0;
  uint16_t vibration = 0;
  byte temp = 0;
};

struct Settings{
  byte motor = 0;
  byte value = 0;
};

#include "Timer.h"
Timer sensorsTmr(100, true);
Timer sendTmr(100, true);
Timer lcdTmr(300, true);

//////////////// МЕНЮ ////////////////
int8_t arrowPos = 0;
byte page = 0;
char cursors[] = {126, 62};
byte controlState = 0;