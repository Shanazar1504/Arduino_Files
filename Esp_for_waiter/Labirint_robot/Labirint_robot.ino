
// Define pins for ultrasonic sensors
#define FRONT_TRIG_PIN 9
#define FRONT_ECHO_PIN 8
#define SIDE_TRIG_PIN 11
#define SIDE_ECHO_PIN 10
#define LEFT_TRIG_PIN 7
#define LEFT_ECHO_PIN 6

// Define motor control pins
#define LEFT_MOTOR_PIN1 12
#define LEFT_MOTOR_PIN2 13
#define RIGHT_MOTOR_PIN1 2
#define RIGHT_MOTOR_PIN2 4
int enA = 5;
int enB = 3;


// Define motor speeds
#define TURN_SPEED 200
#define FORWARD_SPEED 250

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set pins for ultrasonic sensors
  pinMode(FRONT_TRIG_PIN, OUTPUT);
  pinMode(FRONT_ECHO_PIN, INPUT);
  pinMode(SIDE_TRIG_PIN, OUTPUT);
  pinMode(SIDE_ECHO_PIN, INPUT);
  pinMode(LEFT_TRIG_PIN, OUTPUT);
  pinMode(LEFT_ECHO_PIN, INPUT);

  // Set pins for motor control
  pinMode(LEFT_MOTOR_PIN1, OUTPUT);
  pinMode(LEFT_MOTOR_PIN2, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN1, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN2, OUTPUT);
  analogWrite(enA, 100);
  analogWrite(enB, 100);
}

void loop() {
  // Read ultrasonic sensor data
  int front_distance = getDistance(FRONT_TRIG_PIN, FRONT_ECHO_PIN);
  int side_distance = getDistance(SIDE_TRIG_PIN, SIDE_ECHO_PIN);
  int left_distance = getDistance(LEFT_TRIG_PIN, LEFT_ECHO_PIN);

  // Print sensor data to serial monitor
  Serial.print("Front distance: ");
  Serial.println(front_distance);
  Serial.print("Side distance: ");
  Serial.println(side_distance);
  Serial.print("Left distance: ");
  Serial.println(left_distance);

  // If there is a wall in front, turn left or right based on side sensor data
  if (front_distance < 30) {
    if (side_distance < 20) {
      turnRight();
    } else {
      turnLeft();
    }
  }
  // If there is a wall on the left, turn right
  else if (left_distance < 20) {
    turnRight();
  }
  // Otherwise, move forward
  else {
    moveForward();
  }
}

// Function to get distance from ultrasonic sensor
int getDistance(int trig_pin, int echo_pin) {
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  int duration = pulseIn(echo_pin, HIGH);
  int distance = duration / 58;
  return distance;
}

// Function to turn left
void turnLeft() {
  digitalWrite(LEFT_MOTOR_PIN1, HIGH);
  digitalWrite(LEFT_MOTOR_PIN2, LOW);
  digitalWrite(RIGHT_MOTOR_PIN1, LOW);
  digitalWrite(RIGHT_MOTOR_PIN2, HIGH);
  analogWrite(enA, 90);
  analogWrite(enB, 90);

  delay(500);
}


// Function to turn right
void turnRight() {
  digitalWrite(LEFT_MOTOR_PIN1, LOW);
  digitalWrite(LEFT_MOTOR_PIN2, HIGH);
  digitalWrite(RIGHT_MOTOR_PIN1, HIGH);
  digitalWrite(RIGHT_MOTOR_PIN2, LOW);
  analogWrite(enA, 90);
  analogWrite(enB, 90);
  delay(500);
}

// Function to move forward
void moveForward() {
  digitalWrite(LEFT_MOTOR_PIN1, HIGH);
  digitalWrite(LEFT_MOTOR_PIN2, LOW);
  digitalWrite(RIGHT_MOTOR_PIN1, HIGH);
  digitalWrite(RIGHT_MOTOR_PIN2, LOW);
  analogWrite(enA, 150);
  analogWrite(enB, 150);

}

// Function to stop the robot
void stopRobot() {
  digitalWrite(LEFT_MOTOR_PIN1, LOW);
  digitalWrite(LEFT_MOTOR_PIN2, LOW);
  digitalWrite(RIGHT_MOTOR_PIN1, LOW);
  digitalWrite(RIGHT_MOTOR_PIN2, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}
