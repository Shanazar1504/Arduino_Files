#define in1 4 //Motor1  L298 Pin in1 
#define in2 5 //Motor1  L298 Pin in1 
#define in3 6 //Motor2  L298 Pin in1 
#define in4 7//Motor2  L298 Pin in1 

int Speed = 200;
const int triggerPin = 11;
const int echoPin = 12;

long duration;
float distanceCm;
float distanceInch;

void setup() {
  // put your setup code here, to run once:
  pinMode(in1, OUTPUT); // declare as output for L298 Pin in1
  pinMode(in2, OUTPUT); // declare as output for L298 Pin in2
  pinMode(in3, OUTPUT); // declare as output for L298 Pin in3
  pinMode(in4, OUTPUT); //
}

void loop() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // Read the duration of the high pulse on the echo pin
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distanceCm = duration * 0.034 / 2; // Speed ofsound wave divided by 2 (go and back)
    Serial.println(distanceCm);
  if (distanceCm <= 30) {
    Stop();
    delay(100);
    turnRight();
    delay(1000);
    forword();
    delay(1500);
    turnRight();
    delay(1000);
  }
  else {
    forword();
  }
}

void forword() { //forword
  digitalWrite(in1, HIGH); //Right Motor forword Pin
  digitalWrite(in2, LOW);  //Right Motor backword Pin
  digitalWrite(in3, LOW);  //Left Motor backword Pin
  digitalWrite(in4, HIGH); //Left Motor forword Pin
}

void backword() { //backword
  digitalWrite(in1, LOW);  //Right Motor forword Pin
  digitalWrite(in2, HIGH); //Right Motor backword Pin
  digitalWrite(in3, HIGH); //Left Motor backword Pin
  digitalWrite(in4, LOW);  //Left Motor forword Pin
}

void turnRight() { //turnRight
  digitalWrite(in1, LOW);  //Right Motor forword Pin
  digitalWrite(in2, HIGH); //Right Motor backword Pin
  digitalWrite(in3, LOW);  //Left Motor backword Pin
  digitalWrite(in4, HIGH); //Left Motor forword Pin
}

void turnLeft() { //turnLeft
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
