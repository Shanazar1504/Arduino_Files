#define echopin  A0 // echo pin
#define trigpin A1 // Trigger pin

int motor1Pin1 = 4; // pin 4 on L293D IC
int motor1Pin2 = 5; // pin 5 on L293D IC
int motor1EnablePin = 9; // pin 9 on L293D IC

int motor2Pin1 = 6; // pin 6 on L293D IC
int motor2Pin2 = 7; // pin 7 on L293D IC
int motor2EnablePin = 10; // pin 10 on L293D IC

int motor3Pin1 = 12;
int motor3Pin2 = 13;// pin 4 on L293D IC
int motor3EnablePin = 11; // pin 9 on L293D IC

int state;
int Speed = 130;
int distanceFwd;
long duration;
int chk = 0;
int set = 35;

const int buzzer = 3;
const int ledPin = 2;

void setup() {
  Serial.begin(9600);
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
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

  Serial.begin(9600);
  delay(500);

  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
}

void loop() {
  if (Serial.available() > 0) { //if some date is sent, reads it and saves in state
    state = Serial.read();
    if (state > 10) {
      Speed = state;
    }
  }
  distanceFwd = data();

  analogWrite(motor3EnablePin, 60);
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
    Stop() ;
  }
  else if (state == 6) {
    Cam();   // if the state is '6'the motor will Cam
  }
  else if (state == 7) {
    Cam1();   // if the state is '7'the motor will Cam1
  }
  else if (state == 8) {
    Chyra1();   // if the state is '8'the motor will Chyra1
  }
  else if (state == 9) {
    Chyra2();   // if the state is '9'the motor will Chyra2
  }
  else if (state == 10) {
    Chyra3();   // if the state is '10'the motor will Chyra3
  }
  else if (state == 11) {
    Chyra4();   // if the state is '10'the motor will Chyra3
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
  digitalWrite(2, LOW);
}

void Chyra2() {
  tone(buzzer, 1000, 200);
}
void Chyra3() {
  digitalWrite(2, HIGH);

}
void Chyra4() {
  noTone(buzzer);
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
