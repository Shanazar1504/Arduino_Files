#include <AFMotor.h>
AF_DCMotor MotorFR(1);// Motor for drive Front Right on M1
AF_DCMotor MotorFL(2); // Motor for drive Front Left on M2
AF_DCMotor MotorBL(3); // Motor for drive Back Left on M3
AF_DCMotor MotorBR(4); // Motor for drive Back Right on M4

String readString; // declaring string

void setup() {
  // turn off motor
  MotorFL.run(RELEASE);
  MotorFR.run(RELEASE);
  MotorBL.run(RELEASE);
  MotorBR.run(RELEASE);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available())
  {
    String Direction = Serial.readString();
    if (Direction == "1")
    {
      // move forward
      MotorFL.run(FORWARD);
      MotorFR.run(FORWARD);
      MotorBL.run(FORWARD);
      MotorBR.run(FORWARD);
    }
    else if (Direction == "2")
    {
      // move backward
      MotorFL.run(BACKWARD);
      MotorFR.run(BACKWARD);
      MotorBL.run(BACKWARD);
      MotorBR.run(BACKWARD);

    }

    else if (Direction == "3")
    {
      // turn left
      MotorFL.run(BACKWARD);
      MotorFR.run(FORWARD);
      MotorBL.run(BACKWARD);
      MotorBR.run(FORWARD);

    }

    else if (Direction == "4")
    {
      // turn right
      MotorFL.run(FORWARD);
      MotorFR.run(BACKWARD);
      MotorBL.run(FORWARD);
      MotorBR.run(BACKWARD);

    }

    else if (Direction == "5")
    {
      // stop
      MotorFL.run(RELEASE);
      MotorFR.run(RELEASE);
      MotorBL.run(RELEASE);
      MotorBR.run(RELEASE);
    }
  }
}
