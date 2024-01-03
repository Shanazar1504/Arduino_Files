#include <Servo.h>
#include <IRremote.h>

Servo motor_1;
Servo motor_2;
Servo motor_3;

// PWM control pin
#define PWM1_PIN            5
#define PWM2_PIN            6
// 74HCT595N chip pin
#define SHCP_PIN            2                               // The displacement of the clock
#define EN_PIN              7                               // Can make control
#define DATA_PIN            8                               // Serial data
#define STCP_PIN            4

int servo1 = 90;
int servo2 = 90;
int servo3 = 90;








































   
int bt_data;

const int pingPin = 12; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 13; // Echo Pin of Ultrasonic Sensor
const int Forward       = 92;                               // Forward
const int Backward      = 163;                              // Backward
const int Turn_Left     = 149;                              // Left translation
const int Turn_Right    = 106;                              // Right translation
const int Top_Left      = 20;                               // Upper left mobile
const int Bottom_Left   = 129;                              // Lower left mobile
const int Top_Right     = 72;                               // Upper right mobile
const int Bottom_Right  = 34;                               // The lower right move
const int Stop          = 0;                                // Stop
const int Contrarotate  = 172;                              // Counterclockwise rotation
const int Clockwise     = 83;
const int RECV_PIN = 3;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {

  Serial.begin(9600); // initialize serial communication at 9600 bits per second:

  irrecv.enableIRIn();
  irrecv.blink13(true);

  motor_1.attach(9);
  motor_2.attach(10);
  motor_3.attach(11);

  motor_1.write(servo1);
  motor_2.write(servo2);
  motor_3.write(servo2);

  pinMode(SHCP_PIN, OUTPUT);
  pinMode(EN_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(STCP_PIN, OUTPUT);
  pinMode(PWM1_PIN, OUTPUT);
  pinMode(PWM2_PIN, OUTPUT);
  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Motor(Stop, 0);

}

void loop() {

  int front_distance = getDistance(pingPin, echoPin);


  if (Serial.available() > 0) {
    bt_data = Serial.read();
    Serial.println(bt_data);
    if (bt_data > 20) {
    }
  }
  if (bt_data == 1) {
    Motor(Forward, 175);
  }
  else if (irrecv.decode(&results)) {
    Serial.println(results.value);
    irrecv.resume();
    if (results.value == 16748655) {
      Motor(Forward, 175);
    }
  }
  else if (bt_data == 2) {
    Motor(Backward, 175);
  }
  else if (irrecv.decode(&results)) {
    Serial.println(results.value);
    irrecv.resume();
    if (results.value == 16769055) {
      Motor(Backward, 175);
    }
  }
  else if (bt_data == 4) {
    Motor(Turn_Right, 225);
  }
  else if (irrecv.decode(&results)) {
    Serial.println(results.value);
    irrecv.resume();
    if (results.value == 16712445) {
      Motor(Turn_Right, 225);
    }
  }
  else if (bt_data == 3) {
    Motor(Turn_Left, 225); // if the bt_data is '4' the motor will turn right
  }
  else if (irrecv.decode(&results)) {
    Serial.println(results.value);
    irrecv.resume();
    if (results.value == 16750695) {
      Motor(Turn_Left, 225);
    }
  }
  else if (bt_data == 5) {
    Motor(Stop, 0);  // if the bt_data '5' the motor will Stop
  }
  else if (irrecv.decode(&results)) {
    Serial.println(results.value);
    irrecv.resume();
    if (results.value == 16720605) {
      Motor(Forward, 175);
      delay(2500);
      Motor(Turn_Right, 225);
      delay(1000);
      Motor(Backward, 175);
      delay(2500);
      Motor(Turn_Left, 225);
      delay(1000);
      Motor(Stop, 0);
    }
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
  else if (front_distance < 30) {
    Motor(Stop, 0);
    delay(100);
    Motor(Turn_Left, 225);
    delay(1500);
    Motor(Stop, 0);
    delay(100);
    Motor(Backward, 175);
    delay(1500);
    Motor(Stop, 0);
  }
  delay(30);
}

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


void Motor(int Dir, int Speed)      // Motor drive
{
  digitalWrite(EN_PIN, LOW);
  analogWrite(PWM1_PIN, Speed);
  analogWrite(PWM2_PIN, Speed);

  digitalWrite(STCP_PIN, LOW);
  shiftOut(DATA_PIN, SHCP_PIN, MSBFIRST, Dir);
  digitalWrite(STCP_PIN, HIGH);
}
