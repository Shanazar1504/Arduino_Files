#include <AFMotor.h>
AF_DCMotor MotorFR(1);// Motor for drive Front Right on M1
AF_DCMotor MotorFL(2); // Motor for drive Front Left on M2
AF_DCMotor MotorBL(3); // Motor for drive Back Left on M3
AF_DCMotor MotorBR(4); // Motor for drive Back Right on M4


#define S0_PIN 14
#define S1_PIN 15
#define S2_PIN 16
#define S3_PIN 17
#define OUT_PIN 18

int r, g, b;
int valSpeed = 255;
String readString; // declaring string

void setup() {
  Serial.begin(9600); // set up Serial library at 9600 bps
  Serial.println("* Robot Conveyer *");
  // Set the S0, S1, S2, S3 Pins as Output
  pinMode(S0_PIN, OUTPUT);
  pinMode(S1_PIN, OUTPUT);
  pinMode(S2_PIN, OUTPUT);
  pinMode(S3_PIN, OUTPUT);
  //Set OUT_PIN as Input
  pinMode(OUT_PIN, INPUT);

  // Set Pulse Width scaling to 20%
  digitalWrite(S0_PIN, HIGH);
  digitalWrite(S1_PIN, LOW);

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
        MotorFR.run(BACKWARD);
        MotorBL.run(BACKWARD);
        MotorBR.run(FORWARD);
        break;

      case 'B':
        // move backward
        SetSpeed(valSpeed);
        MotorFL.run(BACKWARD);
        MotorFR.run(FORWARD);
        MotorBL.run(FORWARD);
        MotorBR.run(BACKWARD);
        break;
      case 'R':
        // turn right
        SetSpeed(valSpeed);
        MotorFL.run(FORWARD);
        MotorFR.run(FORWARD);
        MotorBL.run(BACKWARD);
        MotorBR.run(BACKWARD);
        break;
      case 'L':
        // turn left
        SetSpeed(valSpeed);
        MotorFL.run(BACKWARD);
        MotorFR.run(BACKWARD);
        MotorBL.run(FORWARD);
        MotorBR.run(FORWARD);
        break;
      case 'G':

        // forward left
        MotorFL.setSpeed(valSpeed / 4);
        MotorBL.setSpeed(valSpeed / 4);
        MotorFL.run(FORWARD);
        MotorFR.run(RELEASE);
        MotorBL.run(BACKWARD);
        MotorBR.run(RELEASE);
        break;
      case 'H':
        // backward left
        MotorFL.setSpeed(valSpeed / 4);
        MotorBL.setSpeed(valSpeed / 4);
        MotorFL.run(RELEASE);
        MotorFR.run(BACKWARD);
        MotorBL.run(RELEASE);
        MotorBR.run(FORWARD);
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
  r = process_red_value();
  delay(200);
  g = process_green_value();
  delay(200);
  b = process_blue_value();
  delay(200);
  Serial.print("r = ");
  Serial.print(r);
  Serial.print(" ");
  Serial.print("g = ");
  Serial.print(g);
  Serial.print(" ");
  Serial.print("b = ");
  Serial.print(b);
  Serial.print(" ");
  Serial.println();

  if (r < 85 && g < 190 && b < 170)
  {
    Serial.println("Colour Red");
    SetSpeed(valSpeed);
    MotorFL.run(BACKWARD);
    MotorFR.run(BACKWARD);
    MotorBL.run(FORWARD);
    MotorBR.run(FORWARD);
    delay(1500);
    MotorFL.run(RELEASE);
    MotorFR.run(RELEASE);
    MotorBL.run(RELEASE);
    MotorBR.run(RELEASE);
  }
  else if (r > 130 && g > 70 && b < 90)
  {
    Serial.println("Colour Green");
    SetSpeed(valSpeed);
    MotorFL.run(FORWARD);
    MotorFR.run(FORWARD);
    MotorBL.run(BACKWARD);
    MotorBR.run(BACKWARD);
    delay(1500);
    MotorFL.run(RELEASE);
    MotorFR.run(RELEASE);
    MotorBL.run(RELEASE);
    MotorBR.run(RELEASE);
  }
  else if (r < 150 && g < 165 && b < 80)
  {
    Serial.println("Colour White");
    SetSpeed(valSpeed);
    MotorFL.run(BACKWARD);
    MotorFR.run(FORWARD);
    MotorBL.run(FORWARD);
    MotorBR.run(BACKWARD);
    delay(1500);
    MotorFL.run(RELEASE);
    MotorFR.run(RELEASE);
    MotorBL.run(RELEASE);
    MotorBR.run(RELEASE);
  }
}


int process_red_value()
{
  digitalWrite(S2_PIN, LOW);
  digitalWrite(S3_PIN, LOW);
  int pulse_length = pulseIn(OUT_PIN, LOW);
  return pulse_length;
}

int process_green_value()
{
  digitalWrite(S2_PIN, HIGH);
  digitalWrite(S3_PIN, HIGH);
  int pulse_length = pulseIn(OUT_PIN, LOW);
  return pulse_length;
}

int process_blue_value()
{
  digitalWrite(S2_PIN, LOW);
  digitalWrite(S3_PIN, HIGH);
  int pulse_length = pulseIn(OUT_PIN, LOW);
  return pulse_length;
}

//function for setting speed of motors
void SetSpeed(int val) {
  valSpeed = val;
  MotorFL.setSpeed(val);
  MotorFR.setSpeed(val);
  MotorBL.setSpeed(val);
  MotorBR.setSpeed(val);
}
