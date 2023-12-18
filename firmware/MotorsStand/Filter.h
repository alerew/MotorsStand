#pragma once
#define EXP_RUNNING_AVERAGE 0
#define MIDLE_ARIFM 1


class Filter {
public:
  Filter(float k = 1) {
    _k = k;
  }
  float filter(float newVal) {
    filt += (newVal - filt) * _k;
    Serial.println("filt1");
    return filt;
  }
  setK(float k) {
    _k = k;
  }
private:
  float _k = 1;
  float filt = 0;
};