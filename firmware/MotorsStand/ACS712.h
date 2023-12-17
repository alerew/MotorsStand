#pragma once
#include <Arduino.h>

#define CURRENT5A 0.185
#define CURRENT20A 0.1
#define CURRENT30A 0.066

class ACS712 {
public:
  ACS712(byte pin, float type) {
    _pin = pin;
    k = type;
  }
  float read() {
    int value = 0;
    for (byte i = 0; i < 16; i++) {
      value += analogRead(_pin);
    }
    value /= 16;
    float amperage = value * 5.0 / 1023.0;
    amperage = (amperage - 2.5) / k;
    return amperage;
  }
private:
  byte _pin;
  float k = 0;
};