#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Test";
const char* password = "test12345";

float temperature = 0;
float humidity = 0;
int gasValue = 0;
int fireSensorValue = 0;

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "Hello from ESP8266!");
}

void returnTemp() {
  server.send(200, "text/plain", String(temperature));
}

void returnHum() {
  server.send(200, "text/plain", String(humidity));
}

void returnGas() {
  server.send(200, "text/plain", String(gasValue));
}

void returnFire() {
  server.send(200, "text/plain", String(fireSensorValue));
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

  server.on("/", handleRoot);
  server.on("/checkTemp", returnTemp);
  server.on("/checkHum", returnHum);
  server.on("/checkGas", returnGas);
  server.on("/checkFire", returnFire);

  server.begin();
  Serial.println("Server started");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input.startsWith("101")) {
      sscanf(input.c_str(), "101 %f %f", &temperature, &humidity);
      Serial.println("Received Temperature and Humidity");
    } else if (input.startsWith("102")) {
      gasValue = input.toInt();
      Serial.println("Received Gas Value");
    } else if (input.startsWith("103")) {
      fireSensorValue = input.toInt();
      Serial.println("Received Fire Sensor Value");
    }
  }

  server.handleClient();
}
