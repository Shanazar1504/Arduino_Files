#include <Servo.h>
Servo servo1;
Servo servo2;
int val;
int val1;
int val2;
int a ;
void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A3, INPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  servo1.attach(9);
  servo2.attach(10);
} 
void loop() {
  Serial.println(a);
  delay(200);
  val1 = digitalRead(A0);
  val2 = digitalRead(A1 );
  if (val1 == 1) {
    servo1.write(76);
    a = a + 1;
    delay(3000);
  }
  if (val1 == 0) {
    servo1.write(0);
  }
  if (val2 == 1) {
    servo2.write(76);
    a = a - 1;
    delay(3000);
  }
  else {
    servo2.write(0);
  }
  if (a > 12) {
    digitalWrite(7, 1);
  }
  else {
    digitalWrite(7, 0);
  }
  val = analogRead(A3);
  if (val >= 324) {
    digitalWrite(8, 1);
    digitalWrite(9, 1);
    
  }
  else {
    digitalWrite(8, 0);
    digitalWrite(9, 0);
    
  }
}
