#pragma once
#include <Arduino.h>

class AnalogTachometer {
  public:
    AnalogTachometer(byte npin){
      pin = npin;
    }
    void tick() {
      adc = analogRead(pin);
      if (!state && adc > porog) {
        state = true;
      }
      else if (state && adc < porog) {
        state = false;
        if (ticks <= window) {
          if (!ticks) tmr = micros();
          if (ticks == window) tmr = micros() - tmr;
          ticks++;
        }
      }
    }

    void setPorog(uint8_t nporog) {
      porog = nporog;
      ticks = 0;
    }

    // установка количества тиков для счёта времени (по умолч 10)
    void setWindow(uint8_t nwindow) {
      window = nwindow;
      ticks = 0;
    }

    // таймаут прерываний (мс), после которого считается что вращение прекратилось (по умолч 1000)
    void setTimeout(uint16_t ntout) {
      tout = ntout;
    }

    // получить обороты в минуту
    uint32_t getRPM() {
      return getTime() ? (60000000ul / prd) : 0;
    }

    // получить частоту в герцах
    float getHz() {
      return getTime() ? (1000000.0 / prd) : 0;
    }

    // получить период в мкс
    uint32_t getUs() {
      return getTime() ? prd : 0;
    }

  private:
    bool getTime() {
      if (ticks > window) {
        tmrMs = millis();
        prd = (uint32_t)tmr / window;
        ticks = 0;
      }
      return (millis() - tmrMs < tout && prd);
    }

    uint8_t pin;
    uint16_t adc = 0;
    bool state = false;

    volatile uint32_t tmr;
    volatile uint8_t ticks = 0;

    uint8_t window = 10;
    uint32_t tmrMs = millis();
    uint32_t prd = 0;
    uint16_t tout = 5000;
    uint16_t porog = 100;
};
