#include "data.h"
Data data;
Settings settings;

#define TENZO 1
#define TEMP 1
#define LCD 1
#define SERIAL 1

void setup() {
  Serial.begin(9600);
  initSensors();
  initLcd();
  initMotor();
  //calibration();
}

void loop() {
  readSensors();
  send();
  readEnc();
  showMenu();
  motorTick();
}
