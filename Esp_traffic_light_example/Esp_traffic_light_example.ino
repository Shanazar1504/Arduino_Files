#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "ELECTRONICLAB";
const char* password = "Electronic123";

const int emergency1 = 5;
const int emergency2 = 4;
const int ldr = 16;
const int water = 14;

const int pump = 12;
const int relay = 13;
const int traffic = 15;

int val1 = 1;
int val2 = 1;
int val_ldr = 0;
int val_water = 0;

ESP8266WebServer server(80);

String stream;

String serverName = "http://192.168.0.108:3000/btn/";


void handlePong() {
  server.send(200, "text/html", "Esp_Traffic_Light");
}


void setup() {
  Serial.begin(115200);
  
  pinMode(emergency1, INPUT);
  pinMode(emergency2, INPUT);
  pinMode(ldr, INPUT);
  pinMode(water, INPUT);
  
  pinMode(traffic, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(pump, OUTPUT);

  digitalWrite(traffic, LOW);
  digitalWrite(pump, LOW);
  digitalWrite(relay, LOW);

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
  readData();
}

void readData() {
  
  val1 = digitalRead(emergency1);
  val2 = digitalRead(emergency2);
  val_ldr = digitalRead(ldr);
  val_water = digitalRead(water);

  if (val1 == 0) {
    postDatatoUrl1();
  }
  else if (val2 == 0) {
    postDatatoUrl2();
  }
  else if (val_ldr == 1) {
    digitalWrite(relay, HIGH);
  }
  else if (val_water == 1) {
    digitalWrite(pump, HIGH);
  }
  else {
    digitalWrite(relay, LOW);
    digitalWrite(pump, LOW);
  }
}

void postDatatoUrl1() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    String serverPath = serverName + "1" ;
    Serial.println(serverPath);
    // Your Domain name with URL path or IP address with path
    http.begin(client, serverPath.c_str());
    // Send HTTP GET request
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }
}

void postDatatoUrl2() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    String serverPath = serverName + "2" ;
    Serial.println(serverPath);
    // Your Domain name with URL path or IP address with path
    http.begin(client, serverPath.c_str());
    // Send HTTP GET request
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }
}

void sendDataFromMaster() {
  String command = server.arg("command");
  command.trim();
  if (command.length() > 0) {
    if (command == "traffic10") {
      digitalWrite(traffic, HIGH);
      delay(9000);
            digitalWrite(traffic, LOW);
    }
    else if (command == "autonomus") {
      digitalWrite(traffic, LOW);
    }
    Serial.println(command);
  }
  server.send(200, "text/plain", "ok");
}
