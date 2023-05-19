#define in1 3 //Motor1  L298 Pin in1 
#define in2 2 //Motor1  L298 Pin in1 
#define in3 5 //Motor2  L298 Pin in1 
#define in4 4 //Motor2  L298 Pin in1 

//IR Sensor setup:
const int irCenterPin = 8; // signal center IR sensor connected to Arduino's pin A2
const int irRightPin = 9; // signal right IR sensor connected to Arduino's pin A3
const int irLeftPin = 10; // signal left IR sensor connected to Arduino's pin A4

boolean stateCenterIR = 0; // state to store irCenterPin detected
boolean stateRightIR = 0; // state to store irCenterPin irRightPin
boolean stateLeftIR = 0; // state to store irCenterPin irLeftPin

void setup() {
  Serial.begin(9600); // set up Serial library at 9600 bps
  Serial.println("*Robot Line Follower Mode - L298N 2A*");
  pinMode(irCenterPin, INPUT); // Sets the irCenterPin as an Input
  pinMode(irRightPin, INPUT); // Sets the irRightPin as an Input
  pinMode(stateLeftIR, INPUT); // Sets the stateLeftIR as an Input

  // Set all the motor control pins to outputs
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);


  // move forward - Initial state
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

// main program loop
void loop() {
  //print the detected condition by 3 IR sensor
  Serial.println("IR_L:" + String(stateLeftIR) + "\tIR_C:" + String(stateCenterIR) + "\tIR_R:" + String(stateRightIR));

  // This logical for state 3 IR sensor, state is TRUE if IR sensor on black line, otherwise FALSE if IR sensor on white
  if ((digitalRead(irLeftPin) == false) && (digitalRead(irCenterPin) == true) && (digitalRead(irRightPin) == false)) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    Serial.println("one");
  }
  if ((digitalRead(irLeftPin) == false) && (digitalRead(irCenterPin) == false) && (digitalRead(irRightPin) == true)) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  if ((digitalRead(irLeftPin) == false) && (digitalRead(irCenterPin) == true) && (digitalRead(irRightPin) == true)) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  if ((digitalRead(irLeftPin) == true) && (digitalRead(irCenterPin) == false) && (digitalRead(irRightPin) == false)) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  if ((digitalRead(irLeftPin) == true) && (digitalRead(irCenterPin) == true) && (digitalRead(irRightPin) == false)) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  if ((digitalRead(irLeftPin) == true) && (digitalRead(irCenterPin) == true) && (digitalRead(irRightPin) == true)) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
}
