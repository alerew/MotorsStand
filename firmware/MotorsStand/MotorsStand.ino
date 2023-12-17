#include "data.h"
Data data;

void setup() {
  Serial.begin(9600);
  initSensors();
  //calibration();
}

void loop() {
  readSensors();
  send();
}