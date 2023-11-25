#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

#define in1 4
#define in2 5
#define echoPin 12
#define triggerPin 14

long duration;
float distanceCm;
float distanceInch;


const char* ssid = "ELECTRONICLAB";
const char* password = "Electronic123";

ESP8266WebServer server(80);
void returnCheck() {
  server.send(200, "text/html", "Ishleyar" );
}
void go_up() {
  server.send(200, "text/html", "Go_Up");
  up();
  delay(1050);
  stoppp();
  delay(10000);
  down();
  delay(700);
  stoppp();
}
void go_down() {
  server.send(200, "text/html", "Go_Down");
  down();
  delay(2000);
  stoppp();
}
void stopp() {
  server.send(200, "text/html", "Stop");
  stoppp();
}

void setup() {
  Serial.begin(115200);
  pinMode(in2, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(triggerPin, OUTPUT);       // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);


  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

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
  server.on("/check/", returnCheck);
  server.on("/control/1", go_up);
  server.on("/GO_DOWN/", go_down);
  server.on("/STOP/", stopp);

}

void loop() {
  server.handleClient();
//  digitalWrite(triggerPin, LOW);
//  delayMicroseconds(2);
//  digitalWrite(triggerPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(triggerPin, LOW);

  // Read the duration of the high pulse on the echo pin
//  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
//  distanceCm = duration * 0.034 / 2; // Speed ofsound wave divided by 2 (go and back)
////  Serial.println(distanceCm);
//  if (distanceCm <= 40) {
//    digitalWrite(in1, HIGH);
//    digitalWrite(in2, LOW);
//    Serial.println("ACHYLDY");
//    delay(1050);
//    digitalWrite(in1, LOW);
//    digitalWrite(in2, LOW);
//    Serial.println("DUR");
//    delay(10000);
//    digitalWrite(in1, LOW);
//    digitalWrite(in2, HIGH);
//    Serial.println("YAP");
//    delay(625);
//    digitalWrite(in1, LOW);
//    digitalWrite(in2, LOW);
//  }
//  else {
//    digitalWrite(in1, LOW);
//    digitalWrite(in2, LOW);
//  }
}


void up() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}

void down() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}

void stoppp() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}
