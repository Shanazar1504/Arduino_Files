#include <SoftwareSerial.h>
SoftwareSerial BT(2, 3); //Rx, Tx

int motor2Pin1 = 8; // pin 6 on L293D IC
int motor2Pin2 = 9; // pin 7 on L293D IC
int motor2EnablePin = 10; // pin 10 on L293D IC

int motor1Pin1 = 11; // pin 4 on L293D IC
int motor1Pin2 = 12; // pin 5 on L293D IC
int motor1EnablePin = 13; // pin 9 on L293D IC


int state;
int Speed = 150;

void setup() {
  Serial.begin(9600);
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor1EnablePin, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(motor2EnablePin, OUTPUT);
  Serial.begin(9600);
  BT.begin(9600); // Setting the baud rate of Software Serial Library
  delay(500);
}

void loop() {

  if (BT.available() > 0) { //if some date is sent, reads it and saves in state
    state = BT.read();
    if (state > 10) {
      Speed = state;
    }
  }

  analogWrite(motor1EnablePin, Speed);
  analogWrite(motor2EnablePin, Speed);

  if (state == 1) {
    forword(); // if the state is '1' the DC motor will go forward
  }
  else if (state == 2) {
    backword(); // if the state is '2' the motor will Reverse
  }
  else if (state == 3) {
    turnLeft(); // if the state is '3' the motor will turn left
  }
  else if (state == 4) {
    turnRight(); // if the state is '4' the motor will turn right
  }
  else if (state == 5) {
    Stop();   // if the state is '5' the motor will Stop
  }
}

void forword() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor2Pin2, HIGH);
}

void backword() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

void turnLeft() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void turnRight() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

void Stop() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}
