// Define pins for ultrasonic sensors
const int trigPin1 = 2;
const int echoPin1 = 3;
const int trigPin2 = 4;
const int echoPin2 = 5;
const int trigPin3 = 6;
const int echoPin3 = 7;

// Define pins for LEDs
const int redLedPin1 = 8;
const int greenLedPin1 = 9;
const int redLedPin2 = 10;
const int greenLedPin2 = 11;
const int redLedPin3 = 12;
const int greenLedPin3 = 13;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Ultrasonic sensor pins
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);

  // LED pins
  pinMode(redLedPin1, OUTPUT);
  pinMode(greenLedPin1, OUTPUT);
  pinMode(redLedPin2, OUTPUT);
  pinMode(greenLedPin2, OUTPUT);
  pinMode(redLedPin3, OUTPUT);
  pinMode(greenLedPin3, OUTPUT);
}

void loop() {
  // Function to get distance from ultrasonic sensor
  int distance1 = getDistance(trigPin1, echoPin1);
  int distance2 = getDistance(trigPin2, echoPin2);
  int distance3 = getDistance(trigPin3, echoPin3);

  // Check if distance is less than 10cm for sensor 1
  if (distance1 <= 10) {
    digitalWrite(redLedPin1, HIGH);
    digitalWrite(greenLedPin1, LOW);
  } else {
    digitalWrite(redLedPin1, LOW);
    digitalWrite(greenLedPin1, HIGH);
  }

  // Check if distance is less than 10cm for sensor 2
  if (distance2 <= 10) {
    digitalWrite(redLedPin2, HIGH);
    digitalWrite(greenLedPin2, LOW);
  } else {
    digitalWrite(redLedPin2, LOW);
    digitalWrite(greenLedPin2, HIGH);
  }

  // Check if distance is less than 10cm for sensor 3
  if (distance3 <= 10) {
    digitalWrite(redLedPin3, HIGH);
    digitalWrite(greenLedPin3, LOW);
  } else {
    digitalWrite(redLedPin3, LOW);
    digitalWrite(greenLedPin3, HIGH);
  }

  delay(100); // Delay between each sensor reading
}

int getDistance(int trigPin, int echoPin) {
  // Trigger pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the pulse duration
  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance
  int distance = duration * 0.034 / 2; // Speed of sound is 0.034 cm/µs

  return distance;
}
