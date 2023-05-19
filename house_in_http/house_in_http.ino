#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#ifndef APSSID
#define APSSID "Test"
#define APPSK  "test123"
#endif

#include <DHT.h>
#define DHTPIN 5
#define DHTTYPE DHT11
#define gassensor A0

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

const int led2 = 13;
const int led1 = 12;
const int buzzer = 14;

ESP8266WebServer server(80);

int sensorPin = 4; /* assigning the Arduino pin for motion detection sensor*/
int val = 0;
int temp;
int hum;
int gas;
int high = 500;

DHT dht(DHTPIN, DHTTYPE);

void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected</h1>");
}

void returnTemp() {
  server.send(200, "text/html", "" + String(temp));
}
void returnGas() {
  server.send(200, "text/html", "" + String(gas));
}
void returnHum() {
  server.send(200, "text/html", "" + String(hum));
}
void light1on() {
  //  server.send(200, "text/html", "light1on");
  digitalWrite(led2, HIGH);
  Serial.println("l1");
}
void light1off() {
  //  server.send(200, "text/html", "light1off");
  digitalWrite(led2, LOW);
  Serial.println("l2");
}
void light2on() {
  //  server.send(200, "text/html", "light1on");
  digitalWrite(led1, HIGH);

  Serial.println("l3");
}
void light2off() {
  //  server.send(200, "text/html", "light1off");
  digitalWrite(led1, LOW);
  Serial.println("l4");
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
   server.on("/checkTemp/", returnTemp);
  server.on("/checkGas/", returnGas);
  server.on("/checkHum/", returnHum);
  server.on("/Light1/", light1on);
  server.on("/Light2/", light1off);
  server.on("/Light3/", light2on);
  server.on("/Light4/", light2off);
  server.begin();
  Serial.println("HTTP server started");
    dht.begin();
  pinMode(led1, OUTPUT);
  digitalWrite(led1, LOW);
  pinMode(led2, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(led2, LOW);
  pinMode(sensorPin, INPUT);
  pinMode(gassensor, INPUT);
}



void loop() {
  server.handleClient();
  dhtt();
  gasss();
  PIRSensor();
}

void dhtt() {
  //read temperature and publish to android app
  temp = dht.readTemperature();
    Serial.println(temp);
    hum = dht.readHumidity();
    Serial.println(hum);
}

void PIRSensor() {
  val = digitalRead(sensorPin);  /* reading the output of the motion sensor*/  if (val == HIGH) {
    //    Serial.println(val);
    digitalWrite(led1, HIGH);  /* turn on the RED led */
  } else if (val == LOW) {
    //    Serial.println(val);
    digitalWrite(led2, LOW); /* turn the red led off */
  }
}

void gasss() {
  gas = analogRead(gassensor);
  Serial.println(gas);
  if (gas >= high) {
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
  }
  else {
    digitalWrite(buzzer, LOW);
  }
}
