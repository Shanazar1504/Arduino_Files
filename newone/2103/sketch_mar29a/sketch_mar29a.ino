#include "dht.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "SD.h"
#include "TMRpcm.h"
#include "SPI.h"
#define SD_ChipSelectPin 4

#define echopin  A0 // echo pin
#define trigpin A1 // Trigger pin
#define dht_pin A2 // Pin sensor is connected to
#define MIN_PULSE_WIDTH  650
#define MAX_PULSE_WIDTH  2350
#define DEFAULT_PULSE_WIDTH  1500
#define FREQUENCY 50


TMRpcm saz;
 dht DHT ;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

int motor1Pin1 = 5; // pin 4 on L293D IC
int motor1Pin2 = 6; // pin 5 on L293D IC
int motor1EnablePin = A3; // pin 9 on L293D IC

int motor2Pin1 = 7; // pin 6 on L293D IC
int motor2Pin2 = 8; // pin 7 on L293D IC
int motor2EnablePin = A4; // pin 10 on L293D IC

int state;
int Speed = 150;

int distanceFwd;
long duration;
int chk = 0;
int set = 35;

int temp;
int hum;

int pos = 0;

int timer = 0;

void setup() {
  saz.speakerPin = 9;
  Serial.begin(9600);
  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD fail");
    return;
  }
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor1EnablePin, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(motor2EnablePin, OUTPUT);
  pinMode(A0 , INPUT);
  pinMode(A1 , OUTPUT);
  Serial.begin(9600);
  delay(500);
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);

  saz.setVolume(5);
  saz.play("2.wav");
}
int pulseWidth(int angle) {
  int pulse_wide, analog_value;
  pulse_wide = map(angle, 0 , 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int (float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  return analog_value;
}
void loop() {
  if (Serial.available() > 0) {
    state = Serial.read();
    Serial.println(state);
    if (state > 10) {
      Speed = state;
    }
  }
  distanceFwd = data();

  analogWrite(motor1EnablePin, Speed);
  analogWrite(motor2EnablePin, Speed);

  if ((distanceFwd < set) && (chk == 1)) {
    chk = 2;
    Stop();
  }
  if (distanceFwd > set) {
    chk = 0;
  }
  if ((state == 1) && (chk == 0)) {
    chk = 1; forword();
  }
  else if (state == 2) {
    backword(); // if the state is '2' the motor will Reverse
  }
  else if (state == 3) {
    turnLeft();  // if the state is '3' the motor will turn left
  }
  else if (state == 4) {
    turnRight(); // if the state is '4' the motor will turn right
  }
  else if (state == 5) {
    Stop();   // if the state is '5' the motor will Stop
  }
  else if (state == 6) {
    saz.setVolume(5);
    saz.play("2.wav");
  }
}
timer = timer + 1;

if (timer > 400) {
  DHT.read11(dht_pin);
  hum = DHT.humidity;
  temp = DHT.temperature;

  Serial.print(temp);        //send distance to MIT App
  Serial.print(";");
  Serial.print(hum);         //send distance to MIT App
  Serial.print(";");
  timer = 0;
}
delay(1);
}

void backword() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}
void forword() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void turnLeft() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

void turnRight() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void Stop() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  pwm.setPWM(0, 0, pulseWidth(177));
  pwm.setPWM(1, 0, pulseWidth(0));
  pwm.setPWM(2, 0, pulseWidth(90));
  pwm.setPWM(3, 0, pulseWidth(90));
}

long data()
{
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  duration = pulseIn (echopin, HIGH);
  return duration / 29 / 2;
}
