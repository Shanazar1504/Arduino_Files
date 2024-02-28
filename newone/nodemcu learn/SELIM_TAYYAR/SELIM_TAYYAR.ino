#include <SoftwareSerial.h>

// Define the motor control pins
const int motor1A = 2;
const int motor1B = 3;
const int motor2A = 4;
const int motor2B = 5;

int speed = 225;
const int led = 6;

// Define Bluetooth module pins
SoftwareSerial bluetooth(7, 8); // RX, TX

void setup() {
    digitalWrite(led, 1);

  // Set motor control pins as outputs
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
  pinMode(led, OUTPUT);


  // Set up Bluetooth serial communication
  bluetooth.begin(9600);

  Serial.begin(9600);
  Serial.println("Bluetooth Car Robot Control");
  Serial.println("Send 'F', 'B', 'L', 'R', 'S' from the Bluetooth app to control the robot.");
}

void loop() {
  if (bluetooth.available() > 0) {
    char command = bluetooth.read();
    Serial.println(command);

    switch (command) {
      case 'B':
        forward();
        break;
      case 'F
      ':
        backward();
        break;
      case 'L':
        left();
        break;
      case 'R':
        right();
        break;
      case 'S':
        stop();
        break;
      case 'w':
  digitalWrite(led, 0);
        break;
      case 'W':
  digitalWrite(led, 1);
        break;
    }
  }
}

void forward() {
  digitalWrite(motor1A, speed);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, speed);
  digitalWrite(motor2B, LOW);
}

void backward() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, speed);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, speed);
}

void left() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, speed);
  digitalWrite(motor2A, speed);
  digitalWrite(motor2B, LOW);
}

void right() {
  digitalWrite(motor1A, speed);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, speed);
}

void stop() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, LOW);
}
