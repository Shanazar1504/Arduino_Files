
#include <AFMotor.h>
AF_DCMotor MotorFR(2);// Motor for drive Front Right on M1
AF_DCMotor MotorFL(4); // Motor for drive Front Left on M2
AF_DCMotor MotorBL(7); // Motor for drive Back Left on M3
AF_DCMotor MotorBR(8); // Motor for drive Back Right on M4

//const int buzPin = 9; // set digital pin 2 as buzzer pin (use active buzzer)
//const int ledPin = 3; // set digital pin 3 as LED pin (use super bright LED)

int valSpeed = 255;
String readString; // declaring string

void setup() {
  Serial.begin(9600); // set up Serial library at 9600 bps
  Serial.println("*Robot Remote Control Mode*");

//  pinMode(9, OUTPUT); // sets the buzzer pin as an Output
//  pinMode(3, OUTPUT); // sets the LED pin as an Output

  // Set the speed to start, from 0 (off) to 255 (max speed)
  MotorFL.setSpeed(valSpeed);
  MotorFR.setSpeed(valSpeed);
  MotorBL.setSpeed(valSpeed);
  MotorBR.setSpeed(valSpeed);
  // turn off motor
  MotorFL.run(RELEASE);
  MotorFR.run(RELEASE);
  MotorBL.run(RELEASE);
  MotorBR.run(RELEASE);
}
void loop() {
  while (Serial.available() > 0) {
    char command = Serial.read();// gets one byte from serial buffer
    Serial.println(command);

    switch (command) {
      case 'F':
        // move forward
        SetSpeed(valSpeed);
        MotorFL.run(FORWARD);
        MotorFR.run(FORWARD);
        MotorBL.run(FORWARD);
        MotorBR.run(FORWARD);
        break;
        
      case 'B':
        // move backward
        SetSpeed(valSpeed);
        MotorFL.run(BACKWARD);
        MotorFR.run(BACKWARD);
        MotorBL.run(BACKWARD);
        MotorBR.run(BACKWARD);
        break;
      case 'R':
        // turn right
        SetSpeed(valSpeed);
        MotorFL.run(FORWARD);
        MotorFR.run(BACKWARD);
        MotorBL.run(FORWARD);
        MotorBR.run(BACKWARD);
        break;
      case 'L':
        // turn left
        SetSpeed(valSpeed);
        MotorFL.run(BACKWARD);
        MotorFR.run(FORWARD);
        MotorBL.run(BACKWARD);
        MotorBR.run(FORWARD);
        break;
      case 'G':

        // forward left
        MotorFL.setSpeed(valSpeed / 4);
        MotorBL.setSpeed(valSpeed / 4);
        MotorFL.run(FORWARD);
        MotorFR.run(FORWARD);
        MotorBL.run(FORWARD);
        MotorBR.run(FORWARD);
        break;
      case 'H':
        // backward left
        MotorFL.setSpeed(valSpeed / 4);
        MotorBL.setSpeed(valSpeed / 4);
        MotorFL.run(BACKWARD);
        MotorFR.run(BACKWARD);
        MotorBL.run(BACKWARD);
        MotorBR.run(BACKWARD);
        break;
      case 'I':
        // forward right
        MotorFR.setSpeed(valSpeed / 4);
        MotorBR.setSpeed(valSpeed / 4);
        MotorFL.run(FORWARD);
        MotorFR.run(FORWARD);
        MotorBL.run(FORWARD);
        MotorBR.run(FORWARD);
        break;
      case 'J':
        // backward right
        MotorFR.setSpeed(valSpeed / 4);
        MotorBR.setSpeed(valSpeed / 4);
        MotorFL.run(BACKWARD);
        MotorFR.run(BACKWARD);
        MotorBL.run(BACKWARD);
        MotorBR.run(BACKWARD);
        break;
      case 'S':
        // stop
        MotorFL.run(RELEASE);
        MotorFR.run(RELEASE);
        MotorBL.run(RELEASE);
        MotorBR.run(RELEASE);
        break;
      case 'V': // beep buzzer
        digitalWrite(2, HIGH);
        delay (5000);
         digitalWrite(2, LOW);
        break;
      case 'W':
        // turn light off
        digitalWrite(3, HIGH);
        break;
      case 'w':
        // turn light on
        digitalWrite(3, LOW);
        break;
      case '0':  // set speed motor to 0(min)
        SetSpeed(0);
        break;
      case '1':  // set speed motor to 30
        SetSpeed(30);
        break;
      case '2':  // set speed motor to 55
        SetSpeed(55);
        break;
      case '3':  // set speed motor to 80
        SetSpeed(80);
        break;
      case '4':  // set speed motor to 105
        SetSpeed(105);
        break;
      case '5':  // set speed motor to 130
        SetSpeed(130);
        break;
      case '6':  // set speed motor to 155
        SetSpeed(155);
        break;
      case '7':  // set speed motor to 180
        SetSpeed(180);
        break;
      case '8':  // set speed motor to 205
        SetSpeed(205);
        break;
      case '9':  // set speed motor to 230
        SetSpeed(230);
        break;
      case 'q':  // set speed motor to 255
        SetSpeed(255);
        break;
    }
  }
}

//function for setting speed of motors
void SetSpeed(int val) {
  valSpeed = val;
  MotorFL.setSpeed(val);
  MotorFR.setSpeed(val);
  MotorBL.setSpeed(val);
  MotorBR.setSpeed(val);
}
