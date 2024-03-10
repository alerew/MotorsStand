#include "ACS712.h"
ACS712 ampSen(AMP_PIN, CURRENT30A);

#include "VoltageSensor.h"
VoltageSensor voltSen(VOLT_PIN, 30000, 7500);

#include "Tachometer.h"
Tachometer tachometer;

#if TEMP == 1
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 tempSen;
#endif

void readSensors() {
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
  }
  filt.tick();
}

void initSensors() {
  attachInterrupt(0, tacho, FALLING);
  initTenzo();
#if TEMP == 1
  tempSen.begin();
#endif
  
}
void tacho(){
  tachometer.tick();
}
