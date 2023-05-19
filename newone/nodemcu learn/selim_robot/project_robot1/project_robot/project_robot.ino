#include <SoftwareSerial.h>
SoftwareSerial BT(2, 3);


int motor2Pin1 = 6; // pin 6 on L293D IC
int motor2Pin2 = 7; // pin 7 on L293D IC
int motor2EnablePin = 10; // pin 10 on L293D IC

int motor1Pin1 = 4; // pin 4 on L293D IC
int motor1Pin2 = 5; // pin 5 on L293D IC
int motor1EnablePin = 9; // pin 9 on L293D IC

int motor3Pin1 = 12;
int motor3Pin2 = 13;// pin 4 on L293D IC
int motor3EnablePin = 11; // pin 9 on L293D IC

int state;
int Speed = 100;
int sensorThres = 300;
int buzzer = 8;
int duration = 0;
int distance = 0;

const int echoPin = A0;
const int trigPin = A1;
const int ledPin = A2;
const int smokeA0 = A3;

void setup() {
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor1EnablePin, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(motor2EnablePin, OUTPUT);
  pinMode(motor3Pin1, OUTPUT);
  pinMode(motor3Pin2, OUTPUT);
  pinMode(motor3EnablePin, OUTPUT);
  pinMode(A0 , INPUT);
  pinMode(A1 , OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, INPUT);
  pinMode(buzzer, OUTPUT);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  BT.begin(9600); // Setting the baud rate of Software Serial Library
  delay(500);

  digitalWrite(A2, HIGH);
}

void loop() {
  //if some date is sent, reads it and saves in state
  if (BT.available() > 0) {
    state = BT.read();
    Serial.println(state);
    if (state > 10) {
      Speed = state;
    }
  }

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;

  int analogSensor = analogRead(smokeA0);
  analogWrite(motor3EnablePin, 60);
  analogWrite(motor1EnablePin, Speed);
  analogWrite(motor2EnablePin, Speed);

  Serial.print("Pin A3: ");
  Serial.println(analogSensor);

  // if the state is '1' the DC motor will go forward
  if ( distance <= 15 )
    Stopforward();
  else if (state == 1)
    forword();

  // if the state is '2' the motor will Reverse
  else if (state == 2)
    backword();

  // if the state is '3' the motor will turn left
  else if (state == 3)
    turnLeft();

  // if the state is '4' the motor will turn right
  else if (state == 4)
    turnRight();

  // if the state is '5' the motor will Stop
  else if (state == 5)
    Stop();
  else if (state == 6)
    Cam();
  else if (state == 7)
    Cam1();
  else if (state == 8)
    Chyra1();
  else if (state == 9)
    Chyra2();
  else if (state == 10)
    Chyra3();
  else if (state == 11)
    Chyra4();
  if (analogSensor > sensorThres)
  {
    tone(buzzer, 1000, 200); \
  }
  else
  {
    noTone(buzzer);
  }
}
void Stopforward() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
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
  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, LOW);
}
void Cam() {
  digitalWrite(motor3Pin2, HIGH);
}
void Cam1() {
  digitalWrite(motor3Pin1, HIGH);
}
void Chyra1() {
  digitalWrite(A2, LOW);
}

void Chyra2() {
  digitalWrite(A2, LOW);
}
void Chyra3() {
  digitalWrite(A2, HIGH);

}
void Chyra4() {
  digitalWrite(A2, HIGH);
}
