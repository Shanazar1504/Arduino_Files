#include <Stepper.h>
#include <Servo.h>

const int stepsPerRevolution = 2038;
Stepper stepperMotor1 = Stepper(stepsPerRevolution, 8, 10, 9, 11);
Stepper stepperMotor2 = Stepper(stepsPerRevolution, 4, 6, 5, 7);

Servo servoMotor;

void setup() {
  servoMotor.attach(2);  // Attach the servo to pin 2
  servoMotor.write(2);

  stepy();
  delay(500);
  stepx();
  delay(500);
  releasexy();
}

void stepy() {
  stepperMotor1.setSpeed(15);
  stepperMotor1.step(2200);
  delay(200);
  servoMotor.write(50);
  delay(500);
  servoMotor.write(2);
  stepperMotor1.setSpeed(15);
  stepperMotor1.step(2200);
  delay(200);
  servoMotor.write(50);
  delay(500);
  servoMotor.write(2);
  stepperMotor1.setSpeed(15);
  stepperMotor1.step(2200);
  delay(200);
  servoMotor.write(50);
  delay(500);
  servoMotor.write(2);
  stepperMotor1.setSpeed(15);
  stepperMotor1.step(2200);
  delay(200);
  servoMotor.write(50);
  delay(500);
  servoMotor.write(2);
  stepperMotor1.setSpeed(15);
  stepperMotor1.step(2200);
  delay(200);
  servoMotor.write(50);
  delay(500);
  servoMotor.write(2);
  stepperMotor1.setSpeed(15);
  stepperMotor1.step(-11000);

}
void stepx() {
  stepperMotor2.setSpeed(15);
  stepperMotor2.step(6300);
  delay(200);
  servoMotor.write(50);
  delay(300);
  servoMotor.write(2);
  stepperMotor1.setSpeed(15);
  stepperMotor1.step(2200);
  delay(200);
  servoMotor.write(50);
  delay(500);
  servoMotor.write(2);
  stepperMotor1.setSpeed(15);
  stepperMotor1.step(2200);
  delay(200);
  servoMotor.write(50);
  delay(500);
  servoMotor.write(2);
  stepperMotor1.setSpeed(15);
  stepperMotor1.step(2200);
  delay(200);
  servoMotor.write(50);
  delay(500);
  servoMotor.write(2);
  stepperMotor1.setSpeed(15);
  stepperMotor1.step(2200);
  delay(200);
  servoMotor.write(50);
  delay(500);
  servoMotor.write(2);
  stepperMotor1.setSpeed(15);
  stepperMotor1.step(2200);
  delay(200);
  servoMotor.write(50);
  delay(500);
  servoMotor.write(2);
  stepperMotor1.setSpeed(15);
  stepperMotor1.step(-11000);
  delay(200);
  stepperMotor2.setSpeed(15);
  stepperMotor2.step(-6300);
}


void releasexy() {
  stepperMotor1.setSpeed(10);
  stepperMotor1.step(5);
  stepperMotor1.setSpeed(0);
  stepperMotor1.step(0);
  stepperMotor2.setSpeed(10);
  stepperMotor2.step(5);
  stepperMotor2.setSpeed(0);
  stepperMotor2.step(0);
}

void loop() {


}
