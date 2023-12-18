#include "data.h"
Data data;


void setup() {
  Serial.begin(9600);
  initSensors();
  initLcd();
  //initMotor();
  //calibration();
}

void loop() {
  readSensors();
  //send();
}