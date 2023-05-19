#include <ESP8266WiFi.h>
#include <PubSubClient.h>
int LED = 2;
// nodemcun oz cyrajygy 2 pin led dakmak hokman dall
// WiFi
const char *ssid = "ELECTRONICLAB"; // Enter your WiFi name
const char *password = "Electronic123";  // Enter WiFi password
// Enter WiFi password
// MQTT Broker
const char *mqtt_broker = "192.168.0.112";
const char *topic = "transfer";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;
WiFiClient espClient;
PubSubClient client(espClient);
void setup() {
  // Set software serial baud to 115200;
  Serial.begin(115200);
  // connecting to a WiFi network
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  //connecting to a mqtt broker
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
    String client_id = "esp8266-client-";
    client_id += String(WiFi.macAddress());
    Serial.println("Connecting to public emqx mqtt broker.....");
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Public emqx mqtt broker connected");
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
  // publish and subscribe
  client.publish(topic, "MQTT STARTED...");
  client.subscribe(topic);
}
void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  String message;
  for (int i = 0; i < length; i++) {
    message = message + (char) payload[i];
    // convert *byte to string
  }
  Serial.print(message);
  if (message == "0") {
    digitalWrite(LED, LOW);  // LED off
    Serial.println("LED OFF");
    client.publish(topic, "LED OFF");
  }
  if (message == "1") {
    digitalWrite(LED, HIGH); // LED ON
    Serial.println("LED ON");
    client.publish(topic, "LED ON");

  }
  if (message == "2") {
    digitalWrite(LED, LOW);  // LED off
    Serial.println("LED OFF");
    client.publish(topic, "LED OFF");
  }
  if (message == "3") {
    analogWrite(LED, 50);  
    Serial.println("level: 50");
    client.publish(topic, "50");
  }
  if (message == "4") {
    analogWrite(LED,100);  
    Serial.println("level: 100");
    client.publish(topic, "100");
  }
  if (message == "5") {
    analogWrite(LED, 150);  
    Serial.println("level: 150");
    client.publish(topic, "150");
  }
    if (message == "6") {
    analogWrite(LED, 200);  
    Serial.println("level: 200");
    client.publish(topic, "200");
  }
    if (message == "7") {
    analogWrite(LED, 255);  
    Serial.println("level: 255");
    client.publish(topic, "255");
  }
  
  Serial.println();
  Serial.println("---------------------- -");
}
void loop() {
  client.loop();
}
