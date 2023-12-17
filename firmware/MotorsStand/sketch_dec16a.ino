#include "data.h"
Data data;

void setup() {
  Serial.begin(9600);
  initTenzo();
  //calibration();
}

void loop() {
  read();
}