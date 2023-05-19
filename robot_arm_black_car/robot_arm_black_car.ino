#include <Servo.h>

Servo motor_1;
Servo motor_2;
Servo motor_3;


#define in1 2 //Motor1  L298 Pin in1 
#define in2 4 //Motor1  L298 Pin in1 
#define in3 7 //Motor2  L298 Pin in1 
#define in4 8 //Motor2  L298 Pin in1 

int servo1 = 90;
int servo2 = 90;
int servo3 = 90;

int bt_data;

const int pingPin = 12; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 13; // Echo Pin of Ultrasonic Sensor

void setup() {

  Serial.begin(9600); // initialize serial communication at 9600 bits per second:

  motor_1.attach(9);
  motor_2.attach(10);
  motor_3.attach(11);

  motor_1.write(servo1);
  motor_2.write(servo2);
  motor_3.write(servo2);

  pinMode(in1, OUTPUT); // declare as output for L298 Pin in1
  pinMode(in2, OUTPUT); // declare as output for L298 Pin in2
  pinMode(in3, OUTPUT); // declare as output for L298 Pin in3
  pinMode(in4, OUTPUT); // declare as output for L298 Pin in4

  delay(1000);
}

void loop() {

  //  long duration, inches, cm;
  //  pinMode(pingPin, OUTPUT);
  //  digitalWrite(pingPin, LOW);
  //  delayMicroseconds(2);
  //  digitalWrite(pingPin, HIGH);
  //  delayMicroseconds(10);
  //  digitalWrite(pingPin, LOW);
  //  pinMode(echoPin, INPUT);
  //  duration = pulseIn(echoPin, HIGH);
  //  inches = microsecondsToInches(duration);
  //  cm = microsecondsToCentimeters(duration);

  if (Serial.available() > 0) {
    bt_data = Serial.read();
    if (bt_data > 20) {

    }
  }
  if (bt_data == 1) {
    forword();  // if the bt_data is '1' the DC motor will go forward
  }
  else if (bt_data == 2) {
    backword(); // if the bt_data is '2' the motor will Reverse
  }
  //   bs
  else if (bt_data == 3) {
    turnRight(); // i*f the bt_data is '3' the motor will turn left
  }
  else if (bt_data == 4) {

    turnLeft();// if the bt_data is '4' the motor will turn right
  }
  else if (bt_data == 5) {
    Stop();  // if the bt_data '5' the motor will Stop
  }
  else if (bt_data == 6) {
    turnLeft();
    delay(400);
    bt_data = 5;
  }
  else if (bt_data == 7) {
    turnRight();
    delay(400);
    bt_data = 5;
  }

  else if (bt_data == 8) {
    if (servo1 < 180) {
      servo1 = servo1 + 1;
    }
    motor_1.write(servo1);
  }
  else if (bt_data == 9) {
    if (servo1 > 0) {
      servo1 = servo1 - 1;
    }
    motor_1.write(servo1);
  }

  else if (bt_data == 10) {
    if (servo2 > 0) {
      servo2 = servo2 - 1;
    }
    motor_2.write(servo2);
  }
  else if (bt_data == 11) {
    if (servo2 < 180) {
      servo2 = servo2 + 1;
    }
    motor_2.write(servo2);
  }

  else if (bt_data == 12) {
    if (servo3 > 0) {
      servo3 = servo3 - 1;
    }
    motor_3.write(servo3);
  }
  else if (bt_data == 13) {
    if (servo3 < 180) {
      servo3 = servo3 + 1;
    }
    motor_3.write(servo3);
  }
  delay(30);
}

void turnLeft() { //forword
  digitalWrite(in1, HIGH); //Right Motor forword Pin
  digitalWrite(in2, LOW);  //Right Motor backword Pin
  digitalWrite(in3, LOW);  //Left Motor backword Pin
  digitalWrite(in4, HIGH); //Left Motor forword Pin
}

void turnRight() { //backword
  digitalWrite(in1, LOW);  //Right Motor forword Pin
  digitalWrite(in2, HIGH); //Right Motor backword Pin
  digitalWrite(in3, HIGH); //Left Motor backword Pin
  digitalWrite(in4, LOW);  //Left Motor forword Pin
}

void forword() { //turnRight
  digitalWrite(in1, LOW);  //Right Motor forword Pin
  digitalWrite(in2, HIGH); //Right Motor backword Pin
  digitalWrite(in3, LOW);  //Left Motor backword Pin
  digitalWrite(in4, HIGH); //Left Motor forword Pin
}

void backword() { //turnLeft
  digitalWrite(in1, HIGH); //Right Motor forword Pin
  digitalWrite(in2, LOW);  //Right Motor backword Pin
  digitalWrite(in3, HIGH); //Left Motor backword Pin
  digitalWrite(in4, LOW);  //Left Motor forword Pin
}

void Stop() { //stop
  digitalWrite(in1, LOW); //Right Motor forword Pin
  digitalWrite(in2, LOW); //Right Motor backword Pin
  digitalWrite(in3, LOW); //Left Motor backword Pin
  digitalWrite(in4, LOW); //Left Motor forword Pin
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

void ultradance() {
  backword();
  delay(500);
  turnRight();
  delay(500);
  forword();
  delay(500);
  turnLeft();
  delay(500);
  Stop();
}
