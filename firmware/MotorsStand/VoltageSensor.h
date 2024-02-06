#pragma once
#include <Arduino.h>

class VoltageSensor {
public:
  VoltageSensor(byte pin, uint16_t R1, uint16_t R2) {
    _pin = pin;
    _R1 = R1;
    _R2 = R2;
  }
  float read() {
    int value = 0;
    for (byte i = 0; i < 16; i++) {
      value = analogRead(_pin);
    }
    value /= 16;
    float voltage = value * refVoltage / 1023.0;
    voltage = voltage / ((float)_R2 / (_R1 + _R2));
    return voltage;
  }
  void setRef(float ref){
    refVoltage = ref;
  }
private:
  byte _pin;
  uint16_t _R1 = 0;
  uint16_t _R2 = 0;
  float refVoltage = 5.0;
};