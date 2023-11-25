
#include <tcs3200.h>
#include <AFMotor.h>
AF_DCMotor MotorFR(1);// Motor for drive Front Right on M1
AF_DCMotor MotorFL(2); // Motor for drive Front Left on M2
AF_DCMotor MotorBL(3); // Motor for drive Back Left on M3
AF_DCMotor MotorBR(4); // Motor for drive Back Right on M4

int red, green, blue, white;

tcs3200 tcs(14, 15, 16, 17, 18); // (S0, S1, S2, S3, output pin)  //

int valSpeed = 85;
String readString; // declaring string

void setup() {
  Serial.begin(9600);
  Serial.println("* Robot Conveyer *");

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

  Commandd();
  readColor();

}

void Commandd() {
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
}

void readColor() {

  red = tcs.colorRead('r', 0);    //scaling can also be put to 0%, 20%, and 100% (default scaling is 20%)   ---    read more at: https://www.mouser.com/catalog/specsheets/TCS3200-E11.pdf
  red = tcs.colorRead('r', 20);
  red = tcs.colorRead('r', 100);

  red = tcs.colorRead('r');   //reads color value for red
  Serial.print("R= ");
  Serial.print(red);
  Serial.print("    ");

  green = tcs.colorRead('g');   //reads color value for green
  Serial.print("G= ");
  Serial.print(green);
  Serial.print("    ");

  blue = tcs.colorRead('b');    //reads color value for blue
  Serial.print("B= ");
  Serial.print(blue);
  Serial.print("    ");

  white = tcs.colorRead('c');    //reads color value for white(clear)
  Serial.print("W(clear)= ");
  Serial.print(white);
  Serial.print("    ");

//  SetSpeed(valSpeed);
//  MotorFL.run(RELEASE);
//  MotorFR.run(FORWARD);
//  MotorBL.run(FORWARD);
//  MotorBR.run(RELEASE);

  if (red <= 9 && green >= 5 ) {
    delay(700);
    SetSpeed(valSpeed);
    MotorFL.run(RELEASE);
    MotorFR.run(FORWARD);
    MotorBL.run(FORWARD);
    MotorBR.run(RELEASE);
    delay(500);
    Serial.println("GREEN");
    SetSpeed(valSpeed);
    MotorFL.run(FORWARD);
    MotorFR.run(FORWARD);
    MotorBL.run(BACKWARD);
    MotorBR.run(BACKWARD);
    delay(1000);
    MotorFL.run(RELEASE);
    MotorFR.run(RELEASE);
    MotorBL.run(RELEASE);
    MotorBR.run(RELEASE);
  } else if (red >= 25 && blue <= 15) {
    delay(700);
    SetSpeed(valSpeed);
    MotorFL.run(RELEASE);
    MotorFR.run(FORWARD);
    MotorBL.run(FORWARD);
    MotorBR.run(RELEASE);
    delay(500);
    Serial.println("RED");
    SetSpeed(valSpeed);
    MotorFL.run(BACKWARD);
    MotorFR.run(BACKWARD);
    MotorBL.run(FORWARD);
    MotorBR.run(FORWARD);
    delay(1000);
    MotorFL.run(RELEASE);
    MotorFR.run(RELEASE);
    MotorBL.run(RELEASE);
    MotorBR.run(RELEASE);
  } else if (white >= 150) {
    Serial.println("WHITE");
    SetSpeed(valSpeed);
    MotorFL.run(BACKWARD);
    MotorFR.run(FORWARD);
    MotorBL.run(FORWARD);
    MotorBR.run(BACKWARD);
    delay(1000);
    MotorFL.run(RELEASE);
    MotorFR.run(RELEASE);
    MotorBL.run(RELEASE);
    MotorBR.run(RELEASE);
  }
  Serial.println();
  //  delay(300);
}

//function for setting speed of motors
void SetSpeed(int val) {
  valSpeed = val;
  MotorFL.setSpeed(val);
  MotorFR.setSpeed(val);
  MotorBL.setSpeed(val);
  MotorBR.setSpeed(val);
}
