#include "data.h"

#define TENZO 1
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
  send();
  readEnc();
  showMenu();
  motorTick();
}
