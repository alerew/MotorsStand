#define AMP_PIN A0   // пин амперметра
#define VOLT_PIN A1  // пин вольтметра
#define VIBR_PIN A2  // пин датчика вибрации
#define MOTOR_PIN 5  // пин мотора
#define TACHO_PIN A3   // пин тахометра
#define MICROFON_PIN A6   // пин микрофона

#define DOUT_PIN 3  // пин DT тензодатчика
#define SCK_PIN 4   // пин SCK тензодатчика

#define S1_PIN 6  // пины энкодера
#define S2_PIN 7
#define BTN_PIN 8

struct Data {
  uint16_t thrust = 0;  // тяга
  float amperage = 0;
  float voltage = 0;
  uint16_t vibration = 0;
  byte temp = 0;
  uint16_t rpm = 0;
  float power = 0;
  float efficiency = 0;
  uint16_t volume = 0;
};

struct Settings {
  byte motor = 0;
  byte value = 0;
  byte mode = 0;    // 0 - ручное измерение, 1 - авто измерение
  byte count = 2;   // количество лопастей
};

Data data;
Settings settings;

#include "Filter.h"
Filter filt(0.5);  // фильтр тензодатчика

#include "Timer.h"

Timer sensorsTmr(300, true);
Timer sendTmr(300, true);
Timer lcdTmr(1000, true);
Timer autoTmr(200, true);


//////////////// МЕНЮ ////////////////
int8_t arrowPos = 0;           // положение указателя
byte page = 0;                 // страница меню
char cursors[] = { 126, 62 };  // курсоры
byte controlState = 0;         // номер курсора

#define TO_STR(x) ((String)(x))
