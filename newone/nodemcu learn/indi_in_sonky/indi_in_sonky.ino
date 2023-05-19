#include <SoftwareSerial.h>
SoftwareSerial BT(2, 3);

#define echopin  A0 // echo pin
#define trigpin A1 // Trigger pin

int motor1Pin1 = 4; // pin 4 on L293D IC
int motor1Pin2 = 5; // pin 5 on L293D IC
int motor1EnablePin = 6; // pin 9 on L293D IC

int motor2Pin1 = 7; // pin 6 on L293D IC
int motor2Pin2 = 8; // pin 7 on L293D IC
int motor2EnablePin = 9; // pin 10 on L293D IC

int IR1 = 10;    //Right sensor
int IR2 = 11;  //left Sensor


int state;
int Speed = 150;
int distanceFwd;
long duration;
int chk = 0;
int set = 35;

void setup() {
  Serial.begin(9600);
  BT.begin(9600);
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor1EnablePin, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(motor2EnablePin, OUTPUT);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(A0 , INPUT);
  pinMode(A1 , OUTPUT);
  Serial.begin(9600);
  delay(500);

}

void loop() {


  if (BT.available() > 0) {
    state = BT.read();
    Serial.println(state);
    if (state > 10) {
    }
  }

  distanceFwd = data();

  analogWrite(motor1EnablePin, Speed);
  analogWrite(motor2EnablePin, Speed);

  if ((distanceFwd < set) && (chk == 1)) {
    chk = 2;
    Stop();
  }
  if (distanceFwd > set) {
    chk = 0;
  }
  if ((state == 1) && (chk == 0)) {
    chk = 1; forword();
  }

 else if (state == 5) {
    Stop();
  }
  else if (state == 2) {
    backword(); // if the state is '2' the motor will Reverse
  }
  else if (state == 3) {
    turnLeft(); // if the state is '3' the motor will turn left
  }
  else if (state == 4)  {
    turnRight(); // if the state is '4' the motor will turn right
  }
}

void forword() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}
void backword() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void turnRight() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

void turnLeft() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void Stop() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}
long data()
{
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  duration = pulseIn (echopin, HIGH);
  return duration / 29 / 2;
}
