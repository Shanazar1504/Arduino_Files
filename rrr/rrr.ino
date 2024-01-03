#define in1 5 //Motor1  L298 Pin in1
#define in2 4 //Motor1  L298 Pin in1
#define in3 7 //Motor2  L298 Pin in1
#define in4 6 //Motor2  L298 Pin in1
#define enA 8 //Motor2  L298 Pin in1
#define enB 9 //Motor2  L298 Pin in1

int Speed = 200;
const int triggerPin = 10;
const int echoPin = 11;

long duration;
float distanceCm;
float distanceInch;

char command; // Variable to store incoming Bluetooth commands

void setup() {
  Serial.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(triggerPin, OUTPUT);

  // Set up Bluetooth communication
  Serial.begin(9600);
}

void loop() {
  // Check for incoming Bluetooth data
  if (Serial.available() > 0) {
    command = Serial.read();
    executeCommand(command);
  }

  // Ultrasonic sensor code
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.034 / 2;

//  if (distanceCm <= 30) {
//    Stop();
//    delay(100);
//    turnRight();
//    delay(1000);
//    forward();
//    delay(1500);
//    turnRight();
//    delay(1000);
//  }
}

void executeCommand(char command) {
  switch (command) {
    case 'F':
      forward();
      break;
    case 'B':
      backward();
      break;
    case 'L':
      turnLeft();
      break;
    case 'R':
      turnRight();
      break;
    case 'S':
      Stop();
      break;
  }
  Serial.println(command);
}

void forward() {
  analogWrite(enA, Speed);
  analogWrite(enB, Speed);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void backward() {
  analogWrite(enA, Speed);
  analogWrite(enB, Speed);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void turnRight() {
  analogWrite(enA, Speed);
  analogWrite(enB, Speed);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turnLeft() {
  analogWrite(enA, Speed);
  analogWrite(enB, Speed);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void Stop() {
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
