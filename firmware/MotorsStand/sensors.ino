#include "ACS712.h"
ACS712 ampSen(AMP_PIN, CURRENT30A);

#include "VoltageSensor.h"
VoltageSensor voltSen(VOLT_PIN, 30000, 7500);

#include "AnalogTachometer.h"
AnalogTachometer tachometer(TACHO_PIN);

#if TEMP == 1
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 tempSen;
#endif

uint16_t raw = 0;

void readSensors() {
  tachometer.tick();
  if (sensorsTmr.isReady()) {
    data.thrust = (uint16_t)abs(filt.set(readThrust()));
    data.amperage = abs(ampSen.read());
    data.voltage = voltSen.read();
    data.power = data.amperage * data.voltage;
    data.vibration = 1023 - analogRead(VIBR_PIN);
    data.rpm = tachometer.getRPM() / 2;
#if TEMP == 1
    data.temp = tempSen.readObjectTempC();
#endif
    if (settings.motor == 0 || data.power == 0 || data.thrust == 0)
      data.efficiency = 0;
    else
      data.efficiency = data.thrust / data.power;
     data.volume = (raw + 83.2073) / 11.003;
  }
  filt.tick();
}

void initSensors() {
  initTenzo();
#if TEMP == 1
  tempSen.begin();
#endif
}

void readMicrofon(){
  static byte count = 0;
  static uint32_t tmr = 0;
  static uint16_t _max = 0, _min = 60000;
  if (micros() - tmr >= 500) {
    tmr = micros();
    uint16_t read = analogRead(MICROFON_PIN);
    _max = max(_max, read);
    _min = min(_min, read);
    if (++count >= 20) {
      raw = _max - _min;
      _min = 0;
      count = 0;
      _max = 60000;
      return true;
    }
  }
  return false;
}
