#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const int stopper = 4;
const int eng1 = 14;
const int eng2 = 12;
const int light = 5;
const int enbA = 16;
const int motA = 0;
const int motB = 5;


const char *ssid = "Pip";
const char *password = "bionics123";

const char *mqtt_broker = "192.168.43.1";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;

const char *topic = "device";

WiFiClient espClient;
PubSubClient client(espClient);


void setup() {
  Serial.begin(115200);
  pinMode(stopper, OUTPUT);
  pinMode(eng1, OUTPUT);
  pinMode(eng2, OUTPUT);
  pinMode(enbA, OUTPUT);
  pinMode(motA, OUTPUT);
  pinMode(motB, OUTPUT);
  digitalWrite(stopper, 0);
  digitalWrite(eng1, 0);
  digitalWrite(eng2, 0);
  digitalWrite(light, 0);
  digitalWrite(motA, 0);
  digitalWrite(motB, 0);

  // connecting to a WiFi network
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
  //   publish and subscribe
  //  client.publish(topic, "Baglandy");
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
  if (message == "1") {
    //    Serial.println("Mator yandy");
    digitalWrite(eng1, 1);
    digitalWrite(eng2, 0);
  }
  else if (message == "2") {
    //    Serial.println("Mator ocdi");
    digitalWrite(eng1, 0);
    digitalWrite(eng2, 0);
  }
  else if (message == "19") {
    accidenton();
  }
  else if (message == "20") {
    accidentoff();
  }
  else if (message == "13") {
    digitalWrite(light, 1);
  }
  else if (message == "14") {
    digitalWrite(light, 0);
  }
  else if (message == "00") {
    Serial.println("geldi");
    analogWrite(enbA, 0);
    digitalWrite(motA, 0);
    digitalWrite(motB, 0);
  }
  else if (message == "01") {
    Serial.println("mode1");
    analogWrite(enbA, 55);
    digitalWrite(motA, 1);
    digitalWrite(motB, 0);
  }
  else if (message == "02") {
    Serial.println("mode2");
    analogWrite(enbA, 130);
    digitalWrite(motA, 1);
    digitalWrite(motB, 0);
  }
  else if (message == "03") {
    Serial.println("mode3");
    analogWrite(enbA, 195);
    digitalWrite(motA, 1);
    digitalWrite(motB, 0);
  }
  else if (message == "04") {
    Serial.println("mode4");
    analogWrite(enbA, 255);
    digitalWrite(motA, 1);
    digitalWrite(motB, 0);
  }
}

void accidentoff () {
  digitalWrite(stopper, 1);
  delay(500);
  digitalWrite(stopper, 0);
  delay(500);
  digitalWrite(stopper, 1);
  delay(500);
  digitalWrite(stopper, 0);
  delay(500);
  digitalWrite(stopper, 1);
  delay(500);
  digitalWrite(stopper, 0);
  delay(500);
  digitalWrite(stopper, 1);
  delay(500);
  digitalWrite(stopper, 0);
  delay(500);
  digitalWrite(stopper, 1);
  delay(500);
  digitalWrite(stopper, 0);
  delay(500);
}

void accidenton() {
  digitalWrite(stopper, 0);
  Serial.println("ocdi");
}

void loop() {
  client.loop();
}
