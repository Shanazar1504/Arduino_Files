#include <WiFiManager.h>
//#include <ESP8266WiFi.h>
#include <SocketIoClient.h>
#include <ArduinoJson.h>

const byte dimmerPin = 14; // GPIO pin connected to the dimmer module
int dimmerValue = 0;      // Remove "const" to allow modification
const byte relay1 = 4;
const byte relay1Inp = 12;
bool relay1Flag = 0;
const byte relay2 = 2;
const byte relay2Inp = 13;
bool relay2Flag = 0;
const int relay1Id = 2;
const int relay2Id = 3;
const int dimmerId = 4;
const String deviceType = "2relay1dimmer";
const int serial = 100;
SocketIoClient sc;
void setup() {
  Serial.begin(115200);
  WiFiManager wm;
  bool res = wm.autoConnect("smart");

  if (!res) {
    Serial.println("Failed to connect");
  }
  else {
    Serial.println("Connected to Wi-Fi");
  }
  pinMode(dimmerPin, OUTPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay1Inp, INPUT);
  pinMode(relay2Inp, INPUT);
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);

  sc.begin("192.168.14.1", 8000, "/socket.io/?transport=websocket&type=device");
  sc.on("deviceReceiver", handleDevice);
  sc.on("getId", handleDevice);
  initializeEmit(deviceType, serial);
}

void loop() {

  boolean switcher1 = digitalRead(relay1Inp);
  if (switcher1 == 1 && relay1Flag == 0 ) {
    relay1Flag = 1;
    digitalWrite(relay1, HIGH);
    deviceEmit(relay1Id, 1);
  }
  if (switcher1 == 0 && relay1Flag == 1) {
    relay1Flag = 0;
    digitalWrite(relay1, LOW);
    deviceEmit(relay1Id, 0);
  }
  boolean switcher2 = digitalRead(relay2Inp);
  if (switcher2 == 1 && relay2Flag == 0 ) {
    relay2Flag = 1;
    digitalWrite(relay2, HIGH);
    deviceEmit(relay2Id, 1);
  }
  if (switcher2 == 0 && relay2Flag == 1) {
    relay2Flag = 0;
    digitalWrite(relay2, LOW);
    deviceEmit(relay2Id, 0);
  }
  sc.loop();
}

void handleId(const char* payload, const size_t length) {
  StaticJsonDocument <200> doc;
  DeserializationError error = deserializeJson(doc, payload);
  if (error) {
    sc.emit("error", error.c_str());
  }
  JsonArray devices = doc.as<JsonArray>();
  for (JsonVariant v : devices) {
    Serial.println(v.as<String>());
  }
}
void handleDevice(const char* payload, const size_t length) {
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, payload);

  int id = doc["id"];
  int State = doc["state"];
  switch (id) {
    case relay1Id:
      digitalWrite(relay1, State);
      Serial.println("Relay1");
      Serial.println(State);
      break;
    case relay2Id:
      digitalWrite(relay2, State);
      Serial.println("Relay1");
      Serial.println(State);
      break;
    case dimmerId:
      analogWrite(dimmerPin, State);
      Serial.println("Dimmer");
      Serial.println(State);
      break;
  }
}
void initializeEmit(String dType, int seria) {
  String str = "{\"type\":\"" + dType + "\", \"serial\":" + String(seria) + "}";
  sc.emit("initialize", str.c_str());
}
const char * commandEmit(int id, int State) {
  String str = "{\"command\":" + String(id) + ", \"state\":" + String(State) + "}";
  return str.c_str();
}
void deviceEmit(int id, int State) {
  String str = "{\"id\":" + String(id) + ", \"state\":" + String(State) + "}";
  sc.emit("deviceSend", str.c_str());
}
