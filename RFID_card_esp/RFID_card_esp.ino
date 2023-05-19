#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char *ssid = "ELECTRONICLAB";
const char *password = "Electronic000";

const char *mqtt_broker = "192.168.1.106";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;

const char *scale_topic = "scale";
const char *body_topic = "body";
const char *heart_topic = "heart";

String serialData;
String stream;
String sensorData[2];
int arrIndex = 0;


WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  
// connecting to a WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  //connecting to a mqtt broker
  client.setServer(mqtt_broker, mqtt_port);
//  client.setCallback(callback);
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
}

void loop() {
  client.loop();
  if (Serial.available() != 0) {
    serialData = Serial.readStringUntil('\n');
  }

  for (int i = 0; i < serialData.length(); i++) {
    if (serialData[i] == '+') {
      sensorData[0] = serialData.substring(0, i);
      sensorData[1] = serialData.substring(i + 1, serialData.length());
    }
  }
  Serial.println(sensorData[0]);
  Serial.println(sensorData[1]);

  client.publish(body_topic, String(sensorData[0]).c_str(), true);
  client.publish(heart_topic, String(sensorData[1]).c_str(), true);
}
