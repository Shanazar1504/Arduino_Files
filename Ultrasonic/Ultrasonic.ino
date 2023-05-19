#define echoPin 12
#define triggerPin 14

#define in1 5
#define in2 4
#define in3 0
#define in4 2

void setup() {
  pinMode(triggerPin, OUTPUT);       // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);// Sets the echoPin as an INPUT
  Serial.begin(9600);             // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor

  Serial.println("with Arduino UNO");

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void loop() {
  long highPulseDuration;
  int calculatedDistanceCm;

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  //Set the trigPin to low, before setting it to high for the pulse
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

  // Displays the distance on the Serial Monitor
  Serial.print("Calculated Distance: ");
  Serial.print(calculatedDistanceCm);
  Serial.println(" cm");
}
