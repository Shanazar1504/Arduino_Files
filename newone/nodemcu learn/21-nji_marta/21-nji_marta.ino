#include <SoftwareSerial.h>
#include "dht.h"
#include <Servo.h>
#define dht_pin A2

SoftwareSerial BT(2, 3);

dht DHT;
Servo x;
Servo y;

int state;
int pos = 0;
int temp;
int hum;
int timer = 0;

void setup() {
  Serial.begin(9600);
  BT.begin(9600);
  x.attach(9);
  y.attach(10);
  delay(500);
}

void loop() {

  if (BT.available() > 0) {
    state = BT.read();
    Serial.println(state);
    if (state > 10) {
    }
  }

  if (state == 1) {
    x.write(pos += 180);
    y.write(pos += 180);
    delay(15);
  }

  else if (state == 5) {
    x.write(pos -= 180);
    y.write(pos -= 180);
    delay(15);
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
}
