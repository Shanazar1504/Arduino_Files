#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);

int sensor_pin = A0;

int output_value ;
int output_value1;

int button = 12;
int via = 16;

const int enbA = 14;
const int motA = 2;
const int motB = 0;

const char* ssid = "Sanly_Saglyk";
const char* password = "000000001";

ESP8266WebServer server(80);
void returnMois() {
  server.send(200, "text/html", "" + String(output_value1));
}
void pumpON() {
  server.send(200, "text/html", "PumpOn");
     digitalWrite(via, 1);
}
void pumpOFF() {
  server.send(200, "text/html", "PumpOff");
     digitalWrite(via, 0);
}

void setup() {
  Serial.begin(115200);
  pinMode(enbA, OUTPUT);
  pinMode(motA, OUTPUT);
  pinMode(motB, OUTPUT);
  pinMode(button, INPUT);
pinMode(via, OUTPUT);
  digitalWrite(motA, 0);
  digitalWrite(motB, 0);
   digitalWrite(via, 0);

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
  server.on("/checkMois/", returnMois);
  server.on("/pumpOn/", pumpON);
  server.on("/pumpOff/", pumpOFF);
  lcd.begin();
  lcd.clear();
  lcd.backlight();

}
void loop() {
  server.handleClient();
  moisturee();

  if (output_value1 <= 49 || digitalRead(button) == 1 ) {
    pumppon();
  }
  else if (output_value1 >= 50  || digitalRead(button) == 0 ) {
    pumppoff();
  }
}

void moisturee() {

  output_value = analogRead(sensor_pin);

  output_value1 = map(output_value, 1023, 0, 0, 100);

  Serial.print("Mositure : ");

  Serial.print(output_value1);

  Serial.println("%");
  lcd.setCursor(0, 0);  //Set cursor to character 2 on line 0
  lcd.print("Chyglylyk:");
  lcd.setCursor(11, 1);  //Move cursor to character 2 on line 1
  lcd.print(output_value1);
  lcd.setCursor(14, 1);  //Set cursor to character 2 on line 0
  lcd.print("%");
  delay(3000);

}
void pumppon() {
  analogWrite(enbA, 255);
  digitalWrite(motA, 1);
  digitalWrite(motB, 0);
  Serial.println("suwarysh");
}

void pumppoff() {
  analogWrite(enbA, 0);
  digitalWrite(motA, 0);
  digitalWrite(motB, 0);
  Serial.println("suwarysh yok");
}

void pumpp1on() {
  analogWrite(enbA, 255);
  digitalWrite(motA, 1);
  digitalWrite(motB, 0);
  Serial.println("suwarysh");
}

void pumpp1off() {
  analogWrite(enbA, 0);
  digitalWrite(motA, 0);
  digitalWrite(motB, 0);
  Serial.println("suwarysh yok");
}
