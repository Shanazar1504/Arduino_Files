#include <SoftwareSerial.h>
SoftwareSerial bt(2, 3); // RX, TX
#include <DHT.h>
#define DHTPIN A0
#define DHTTYPE DHT11

unsigned long previousMillis = 0;
unsigned long interval = 5000;
DHT dht(DHTPIN, DHTTYPE);
const int led = 5;
int state;
int gas = 29;

void setup() {
  Serial.begin(9600);
  bt.begin(9600);
  dht.begin();
  pinMode(led, OUTPUT);
  Serial.println("Ready");
  digitalWrite(led, LOW);
}

int temp;
int hum;

void loop() {
  if (bt.available() > 0) { //if some date is sent, reads it and saves in state
    state = bt.read();
    if (state > 10) {
    }
  }
  if (state == 1) {
    digitalWrite(led, HIGH);
  }
  else if (state == 0) {
    digitalWrite(led, LOW);
  }
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    //read humidity and publish to android app
    hum = dht.readHumidity();
    temp = dht.readTemperature();

    bt.print(temp); //send distance to MIT App
    bt.print(";");
    delay(1000);
    bt.print(hum); //send distance to MIT App
    bt.println(";");
    delay(1000);
    bt.print(gas); //send distance to MIT App
    bt.println(";");
    delay(1000);
  }
}
