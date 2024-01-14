#include "ACS712.h"
ACS712 ampSen(AMP_PIN, CURRENT30A);

#include "VoltageSensor.h"
VoltageSensor voltSen(VOLT_PIN, 30000, 7500);

#if TEMP == 1
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 tempSen;
#endif

void readSensors() {
  if (sensorsTmr.isReady()) {
    data.thrust = readThrust();
    data.amperage = ampSen.read();
    data.voltage = voltSen.read();
    data.vibration = analogRead(VIBR_PIN);
#if TEMP == 1
    data.temp = tempSen.readObjectTempC();
#endif
  }
}

void initSensors() {
  initTenzo();
#if TEMP == 1
  tempSen.begin();
#endif
}