#include "data.h"
Data data;
Settings settings;


void setup() {
  Serial.begin(9600);
  //initSensors();
  initLcd();
  //initMotor();
  //calibration();
}

void loop() {
  readSensors();
  readEnc();
  //send();
  showMenu();
}