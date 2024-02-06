#define AMP_PIN A0
#define VOLT_PIN A1
#define VIBR_PIN A2
#define MOTOR_PIN 5
#define DIST_PIN 2

#define DOUT_PIN 3
#define SCK_PIN 4

#define S1_PIN 6
#define S2_PIN 7
#define BTN_PIN 8

struct Data {
  float thrust = 0;  // тяга
  float amperage = 0;
  float voltage = 0;
  uint16_t vibration = 0;
  byte temp = 0;
  uint16_t rpm = 0;
  float power = 0;
};

struct Settings{
  byte motor = 0;
  byte value = 0;
};

Data data;
Settings settings;

#include "Timer.h"
Timer sensorsTmr(300, true);
Timer sendTmr(500, true);
Timer lcdTmr(300, true);

//////////////// МЕНЮ ////////////////
int8_t arrowPos = 0;
byte page = 0;
char cursors[] = {126, 62};
byte controlState = 0;

enum Mdata_t {
    M_NULL,

    M_STR,
    M_CSTR,

    M_BOOL,
    M_INT8,
    M_UINT8,
    M_INT16,
    M_UINT16,
    M_INT32,
    M_UINT32,

    M_FLOAT,
    M_DOUBLE,
};
#define NUM_DATA 7

const char name1[] PROGMEM = "Thrust";
const char name2[] PROGMEM = "Power";
const char name3[] PROGMEM = "Temp";
const char name4[] PROGMEM = "Vibration";
const char name5[] PROGMEM = "RPM";
const char name6[] PROGMEM = "Amperage";
const char name7[] PROGMEM = "Voltage";

const char* const dataNames[] PROGMEM = {name1, name2, name3, name4, name5, name6, name7};
const void* dataValues[] = {&data.thrust, &data.power, &data.temp, &data.vibration, &data.rpm, &data.amperage, &data.voltage}; 
const Mdata_t dataTypes[] = {M_FLOAT, M_FLOAT, M_UINT8,  M_UINT16,  M_UINT16, M_FLOAT, M_FLOAT};

