#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <Arduino.h>
#include <TM1637Display.h>

#define red1 5
#define red2 4
#define green1 13
#define green2 15

const int CLK = 12;
const int DIO = 14;
const int button = 2;
const int chrome = 16;

int counter = 0;

const uint8_t SEG_DONE[] = {
  SEG_F | SEG_A | SEG_E | SEG_G | SEG_B | SEG_C,   // R
  SEG_E | SEG_F | SEG_A | SEG_G | SEG_B | SEG_C,   // A
  SEG_A | SEG_F | SEG_E | SEG_D,                   // C
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
};

TM1637Display display(CLK, DIO);

const char* ssid = "GalaxyS10";
const char* password = "galaxys10";

ESP8266WebServer server(80);
void returnCheck() {
  server.send(200, "text/html", "Ishleyar" );
}
void Startt() {
  server.send(200, "text/html", "Start");
  digitalWrite(chrome, HIGH);
  Serial.println("start");
}
void Stopp() {
  server.send(200, "text/html", "Stop");
  digitalWrite(chrome, LOW);
  Serial.println("stop");
}

void setup() {
  display.setBrightness(0xff);
  Serial.begin(115200);
  pinMode(button, INPUT);
  pinMode(chrome, OUTPUT);
  pinMode(red1, OUTPUT);
  pinMode(green1, OUTPUT);
  pinMode(red2, OUTPUT);
  pinMode(green2, OUTPUT);
  digitalWrite(red1, LOW);
  digitalWrite(green1, LOW);
  digitalWrite(red2, LOW);
  digitalWrite(green2, LOW);
  digitalWrite(chrome, LOW);
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
  server.on("/START/", Startt);
  server.on("/FINISH/", Stopp);
}

void loop() {
  server.handleClient();
  if (digitalRead(button) == 1 ) {
    Starton();
  }
}

void Starton() {
  digitalWrite(green1, 0);
  digitalWrite(green2, 0);
  for (int count = 10; count >= 0; count = count - 1) {
    Serial.println(count);
    display.clear();
    display.showNumberDec(count);
    digitalWrite(red1, 0);
    digitalWrite(red2, 1);
    delay(500);
    digitalWrite(red1, 1);
    digitalWrite(red2, 0);
    delay(500);
  }
  go();
}

void Finishoff() {
}
void go() {
   digitalWrite(green1, 0);
  digitalWrite(green2, 1);
  display.clear();
  display.setSegments(SEG_DONE);
  delay(5000);
  if(digitalRead(button) == 0){
  counter++;
  delay(1000);
    display.showNumberDec(counter);
}
}
