#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <TM1637Display.h>
#include <Wire.h>
#include <RTClib.h>

#define SDA_PIN 4  // Example GPIO pin for SDA
#define SCL_PIN 5  // Example GPIO pin for SCL

const int CLK = 14;  // Define CLK pin for TM1637
const int DIO = 12;  // Define DIO pin for TM1637

RTC_DS1307 rtc;

TM1637Display display(CLK, DIO);

const char* ssid = "Test";
const char* password = "test12345";

ESP8266WebServer server(80);

String command;

void handlePong() {
  server.send(200, "text/html", "Ishleyar");
}

void setup() {
  Serial.begin(115200);


  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // You can set the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  }

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

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

  display.setBrightness(7);  // Set brightness (0x00 to 0x0f)


  Serial.println("Charging:");



}

void loop() {
  showTime();
  server.handleClient(); 
}

void sendDataFromMaster() {
  command = server.arg("command");

  command.trim();
  if (command.length() > 0) {
    Serial.println(command);
    updateDisplay();
  }
  server.send(200, "text/plain", "ok");
}

void updateDisplay() {
  int value = command.toInt();

  // Assuming your TM1637 display has 4 digits
  display.showNumberDec(value, false, 4);
  delay(2500);

  Serial.print("Charging: ");
  Serial.print(value);
  Serial.println("%");
}

void showTime() {
  DateTime now = rtc.now();
  int hours = now.hour();
  int minutes = now.minute();

  // Toggle the dots every second
  static bool dotsOn = true;
  dotsOn = !dotsOn;

  // Display time with blinking dots on TM1637
  if (dotsOn) {
    display.showNumberDecEx((hours * 100) + minutes, 0b11100000, true);
  } else {
    display.showNumberDecEx((hours * 100) + minutes, 0b00000000, true);
  }
  delay(1000);

  // Serial print the current hour and minute
  Serial.print("Current time: ");
  Serial.print(hours);
  Serial.print(":");
  Serial.print(minutes);
}
