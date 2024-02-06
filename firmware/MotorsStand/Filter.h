#pragma once

class Filter {
public:
  Filter(float k = 1) {
    _k = k;
  }
  int32_t set(int32_t newVal) {
    value = newVal;
    return fvalue;
  }
  int32_t get() {
    return fvalue;
  }
  void tick() {
    if (millis() - tmr >= 30) {
      fvalue += (value - fvalue) / _k;
      tmr = millis();
    }
  }
  void setK(float k) {
    _k = k;
  }
private:
  byte _k = 1;
  int32_t fvalue = 0;
  int32_t value = 0;
  uint32_t tmr = 0;
};
