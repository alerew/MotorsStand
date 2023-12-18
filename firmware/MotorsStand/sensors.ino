#include "ACS712.h"
ACS712 ampSen(AMP_PIN, CURRENT30A);

#include "VoltageSensor.h"
VoltageSensor voltSen(VOLT_PIN, 30000, 7500);

#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 tempSen;

void readSensors() {
  if (sensorsTmr.isReady()) {
    data.thrust = readThrust();
    data.amperage = ampSen.read();
    data.voltage = voltSen.read();
    data.vibration = analogRead(VIBR_PIN);
    data.temp = tempSen.readObjectTempC();
  }
}

void initSensors() {
  initTenzo();
  tempSen.begin();
}