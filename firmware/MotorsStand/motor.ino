#include <Servo.h>
Servo motor;

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