#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

// Control pin for smart socket
const int sensorIn = A0;



//Current sensor data
int mVperAmp = 60; // use 185 for 5A, 100 for 20A Module and 66 for 30A Module
double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;

//Static IP address configuration
IPAddress staticIP(192, 168, 1, 151); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 8, 8);  //DNS

const char* ssid = "Akylly_Ahal_1";
const char* password = "akylly_ahal_1";
const char* deviceName = "Watt and control";
String serverUrl = "192.168.1.252";
String payload;
String device_key = "watt_and_control";
String command = "watt_measure";


ESP8266WebServer server(80);
String stream;


void handlePong() {
  server.send(200, "text/html", device_key);
}


void setup() {
  pinMode(A0, INPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");
  WiFi.disconnect();
  WiFi.hostname(deviceName);
  WiFi.config(staticIP, subnet, gateway, dns);
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);

  //
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }


  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/ping/", handlePong);
  server.on("/control/", handleDevice);

  server.begin();
  Serial.println("HTTP server started");
}


void loop() {
  server.handleClient();
  //sendDataFromMaster();

  Voltage = getVPP();
  VRMS = (Voltage / 2.0) * 0.707; // sq root
  AmpsRMS = (VRMS * 1000) / mVperAmp;
  float Wattage = (220 * AmpsRMS) - 18;
  String argument_data = "?device_key=" + device_key + "&command=" + command + "&value=" + String(Wattage);
  sendRequest("http://" + serverUrl + "/esp/ArgToDB/", argument_data);
  
}

float getVPP()
{
  float result;
  int readValue;
  int maxValue = 0;
  int minValue = 1024;
  uint32_t start_time = millis();

  while ((millis() - start_time) < 1000) //sample for 1 Sec
  {
    readValue = analogRead(sensorIn);
    if (readValue > maxValue)
    {
      maxValue = readValue;
    }
    if (readValue < minValue)
    {
      minValue = readValue;
    }
  }
  result = ((maxValue - minValue) * 5) / 1024.0;

  return result;
}

void sendRequest(String path, String sendingData) {
  if (WiFi.status() == WL_CONNECTED) {
    String serverPath = path + sendingData;
    Serial.println(serverPath);
    payload = httpGETRequest(serverPath.c_str());
    Serial.println(payload);
  }
  else {
    Serial.println("WiFi Disconnected");
  }
}


String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
  http.begin(client, serverName);
  int httpResponseCode = http.GET();
  String payload = "{}";
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
  return payload;
}
