#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "ELECTRONICLAB";
const char* password = "Electronic123";

ESP8266WebServer server(80);

String command;

const int led1 = 16;
const int led2 = 5;
const int led3 = 4;
const int led4 = 0;
const int street = 12;
const int pump = 14;

void handlePong() {
  server.send(200, "text/html", "ESP_SMART_CITY");
}

void setup() {
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(street, OUTPUT);
  pinMode(pump, OUTPUT);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  //      WiFi.config();

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
  server.on("/ping/", handlePong);
  server.on("/control/", sendDataFromMaster);
}

void loop() {
  server.handleClient();
}

void sendDataFromMaster() {
  command = server.arg("command");

  command.trim();
  if (command.length() > 0) {
    if (command == "led1_on") {
      digitalWrite(led1, HIGH);
    }
    else if (command == "led1_off") {
      digitalWrite(led1, LOW);
    }
    else if (command == "led2_on") {
      digitalWrite(led2, HIGH);
    }
    else if (command == "led2_off") {
      digitalWrite(led2, LOW);
    }
    else if (command == "led3_on") {
      digitalWrite(led3, HIGH);
    }
    else if (command == "led3_off") {
      digitalWrite(led3, LOW);
    }
    else if (command == "led4_on") {
      digitalWrite(led4, HIGH);
    }
    else if (command == "led4_off") {
      digitalWrite(led4, LOW);
    }
    else if (command == "all_light_on") {
      ledd_all_on();
    }
    else if (command == "all_light_off") {
      ledd_all_off();
    }
    else if (command == "street_on") {
      digitalWrite(street, HIGH);
    }
    else if (command == "street_off") {
      digitalWrite(street, LOW);
    }
    Serial.println(command);
    command = "";
  }
  server.send(200, "text/plain", "ok");
}

void ledd_all_on() {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(street, HIGH);
}
void ledd_all_off() {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(street, LOW);
}
