#define echoPin 12
#define triggerPin 14

const int dirPin = 0;
const int stepPin = 2;
const int stepsPerRevolution = 200;
const int step_stopp = 0;

long highPulseDuration;
int calculatedDistanceCm;

void setup() {
  pinMode(triggerPin, OUTPUT);       // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}
void loop() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(5);

  // Create the 10 seconds pulse on the trig pin
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);

  // Set the pin to low to end the pulse
  digitalWrite(triggerPin, LOW);

  // Read the duration of the high pulse on the echo pin
  highPulseDuration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  calculatedDistanceCm = highPulseDuration * 0.034 / 2; // Speed ofsound wave divided by 2 (go and back)
  if (calculatedDistanceCm >= 50) {
    step_up();
  }
  else {
    step_down();
  }
}

void step_up() {
  // Set motor direction clockwise
  digitalWrite(dirPin, HIGH);   // Spin motor slowly
  for (int x = 0; x < stepsPerRevolution; x++)  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
    delay(5000);
   
}

void step_down() {
  // Set motor direction counterclockwise
  digitalWrite(dirPin, LOW);  // Spin motor quickly
  for (int x = 0; x < stepsPerRevolution; x++)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
}

void step_stop(){
  // Set motor direction counterclockwise
  digitalWrite(dirPin, LOW);  // Spin motor quickly
  for (int x = 0; x < step_stopp; x++)
  {
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
}
