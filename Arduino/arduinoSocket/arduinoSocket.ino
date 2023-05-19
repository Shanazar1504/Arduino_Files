#include <SoftwareSerial.h>

char data;


int relayLED = 5;
int relay2LED = 6;
int relay3LED = 7;

int relay = 8;
int relay2 = 9;
int relay3 = 10;


int buzzer = 12;
int smokeA0 = A1;
// Your threshold value
int sensorThres = 400;


void setup() {
Serial.begin(115200);

pinMode(relayLED, OUTPUT);
pinMode(relay2LED, OUTPUT);
pinMode(relay3LED, OUTPUT);

pinMode(relay, OUTPUT);
pinMode(relay2, OUTPUT);
pinMode(relay3, OUTPUT);


digitalWrite(relay, HIGH);
digitalWrite(relay2, HIGH);
digitalWrite(relay3, HIGH);


  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
}
 
void loop() {
  if (Serial.available()>0)
  {
    data=Serial.read();
    Serial.println(data);
    if (data == '0') {
      digitalWrite(relay, HIGH);
      digitalWrite(relayLED, LOW);
    }
    if (data == '1') {
      digitalWrite(relay, LOW);
      digitalWrite(relayLED, HIGH);
    }
    if (data == '3') {
      digitalWrite(relay2, HIGH);
      digitalWrite(relay2LED, LOW);
    }
    if (data == '2') {
      digitalWrite(relay2, LOW);
      digitalWrite(relay2LED, HIGH);
    }
    if (data == '5') {
      digitalWrite(relay3, HIGH);
      digitalWrite(relay3LED, LOW);
    }
    if (data == '4') {
      digitalWrite(relay3, LOW);
      digitalWrite(relay3LED, HIGH);
    }
  }
 
  int analogSensor = analogRead(smokeA0);

  Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {

    digitalWrite(relay, HIGH);
    digitalWrite(relay2, HIGH);
    digitalWrite(relay3, HIGH);

    digitalWrite(relayLED, LOW);
    digitalWrite(relay2LED, LOW);
    digitalWrite(relay3LED, LOW);
    
    tone(buzzer, 1000, 200);
  }
//  else if (analogSensor < sensorThres)
//  {
//    digitalWrite(relay, LOW);
//    digitalWrite(relay2, LOW);
//    digitalWrite(relay3, LOW);
//    
//    noTone(buzzer);
//  }
  delay(1000);
}
