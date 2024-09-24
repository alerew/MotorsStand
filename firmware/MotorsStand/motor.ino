#include <Servo.h>
static Servo motor;


void initMotor() {
  motor.attach(MOTOR_PIN);
  stopMotor();
}
void writeMotor(byte val) {
  motor.write(val);
}
void stopMotor() {
  motor.write(0);
}
void motorTick() {
  static byte lastVal = 0;
  if (settings.motor) {
    autoMotorTick();

    if (lastVal != settings.value) {
      writeMotor(settings.value);
      lastVal = settings.value;
    }
  } else {
    if (lastVal != 0) {
      stopMotor();
      lastVal = 0;
      settings.mode = 0;
    }
  }
}
void autoMotorTick() {  // автоматическое измерение
  if (settings.mode == 1 && autoTmr.isReady()) {
    settings.value++;
    if (settings.value > 180) {
      settings.mode = 0;
      settings.value = 0;
      settings.motor = 0;
    }
  }
}