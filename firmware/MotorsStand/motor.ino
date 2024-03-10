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
    if (lastVal != settings.value) {
      writeMotor(settings.value);
      lastVal = settings.value;
    }
  } else {
    if (lastVal != 0) {
      stopMotor();
      lastVal = 0;
    }
  }
}
