#pragma once
#include "Timer.h"

class Filter {
public:
  Filter(float k = 1) {
    _k = k;
  }
  int16_t set(uint16_t newVal) {
    value = newVal;
    return fvalue;
  }
  int16_t get() {
    return fvalue;
  }
  void tick() {
    if (tmr.isReady()) {
      fvalue += (value - fvalue) * _k;
    }
  }
  void setK(float k) {
    _k = k;
  }
private:
  float _k = 1;
  int16_t fvalue = 0;
  int16_t value = 0;
  TimerT<30, byte> tmr;
};
