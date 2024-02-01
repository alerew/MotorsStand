#include <Servo.h>
Servo motor;

byte lastVal = 0;

void initMotor(){
  motor.attach(MOTOR_PIN);
  stopMotor();
}
void writeMotor(byte val){
  motor.write(val);
}
void stopMotor(){
  motor.write(0);
}
void motorTick(){
  if(settings.motor){
    writeMotor(settings.value);
    lastVal = settings.value;
  }
  else stopMotor();
}
