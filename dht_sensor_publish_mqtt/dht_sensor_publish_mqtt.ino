#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define wifi_ssid "TP-LINK_BF4C"
#define wifi_password "1020304050"

#define mqtt_server "192.168.0.125"
#define mqtt_user "login"
#define mqtt_password "password"

#define humidity_topic "humidity"
#define temperature_topic "temperature"
#define sub_topic "transfer"

#define DHTTYPE DHT11
#define DHTPIN  2

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHTPIN, DHTTYPE, 11); // 11 works fine for ESP8266
const int lamp = 13;


void setup() {
  Serial.begin(115200);
  dht.begin();
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  pinMode(lamp, OUTPUT);
  digitalWrite(lamp, LOW);
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    // If you do not want to use a username and password, change next line to
    // if (client.connect("ESP8266Client")) {
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }

 client.subscribe(sub_topic);
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
    digitalWrite(lamp, LOW);  // LED off
    Serial.println("LED OFF");
    client.publish(topic, "LED OFF");
  }
  if (message == "1") {
    digitalWrite(lamp, HIGH); // LED ON
    Serial.println("LED ON");
    client.publish(topic, "LED ON");
  }
 }

bool checkBound(float newValue, float prevValue, float maxDiff) {
  return !isnan(newValue) &&
         (newValue < prevValue - maxDiff || newValue > prevValue + maxDiff);
}

long lastMsg = 0;
float temp = 0.0;
float hum = 0.0;
float diff = 1.0;

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;

    float newTemp = dht.readTemperature();
    float newHum = dht.readHumidity();

    if (checkBound(newTemp, temp, diff)) {
      temp = newTemp;
      Serial.print("New temperature:");
      Serial.println(String(temp).c_str());
      client.publish(temperature_topic, String(temp).c_str(), true);
    }

    if (checkBound(newHum, hum, diff)) {
      hum = newHum;
      Serial.print("New humidity:");
      Serial.println(String(hum).c_str());
      client.publish(humidity_topic, String(hum).c_str(), true);
    }
  }
}
