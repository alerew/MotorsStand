#include "data.h"
Data data;
Settings settings;

#define TENZO 0
#define TEMP 0
#define LCD 1
#define SERIAL 0

void setup() {
  Serial.begin(9600);
  initSensors();
  initLcd();
  initMotor();
  //calibration();
}

void loop() {
  readSensors();
  readEnc();
  send();
  showMenu();
}