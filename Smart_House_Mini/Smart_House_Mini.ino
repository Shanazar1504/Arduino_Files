#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>
#define DHTPIN 5
#define DHTTYPE DHT11
#define gassensor A0

const int led2 = 13;
const int led1 = 12;
const int buzzer = 14;

const char *ssid = "Test";
const char *password = "12345678";

int sensorPin = 4; /* assigning the Arduino pin for motion detection sensor*/
int val = 0;
int temp;
int hum;
int gas;
int high = 500;

DHT dht(DHTPIN, DHTTYPE);

ESP8266WebServer server(80);
void returnTemp() {
  server.send(200, "text/html", "" + String(temp));
}
void returnGas() {
  server.send(200, "text/html", "" + String(gas));
}
void returnHum() {
  server.send(200, "text/html", "" + String(hum));
}
//void returnMot() {
//  server.send(200, "text/html", "" + String(val));
//}
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
  Serial.begin(115200);
  dht.begin();
  pinMode(led1, OUTPUT);
  digitalWrite(led1, LOW);
  pinMode(led2, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(led2, LOW);
  pinMode(sensorPin, INPUT);
  pinMode(gassensor, INPUT);


  WiFi.begin(ssid, password);
  //    WiFi.config(staticIP , gateway, subnet, dns);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  server.begin();
  Serial.println("Server started");
  server.on("/checkTemp/", returnTemp);
  server.on("/checkGas/", returnGas);
  server.on("/checkHum/", returnHum);
  //  server.on("/checkMot/", returnMot);
  server.on("/Light1/", light1on);
  server.on("/Light2/", light1off);
  server.on("/Light3/", light2on);
  server.on("/Light4/", light2off);
}

void loop() {
  server.handleClient();
  dhtt();
  gasss();
//  Serial.println(temp);
//  Serial.println(hum);
//  Serial.println(gas);
  //  Serial.println(val);
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
