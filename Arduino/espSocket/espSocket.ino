#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
 SoftwareSerial s(0, 2); // RX, TX
const char* ssid     = "rozetka";
const char* password = "12345678";


WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  s.begin(115200);
  delay(10);
 
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
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  if (request.indexOf("/relay/on") != -1)  {
    s.write("1");
    Serial.println("relay on");
  }
  
  if (request.indexOf("/relay/off") != -1)  {
    s.write("0");
    Serial.println("relay off");
  }
  
  if (request.indexOf("/relay2/on") != -1) {
    s.write("2");
    Serial.println("relay2 on");
  }

  if (request.indexOf("/relay2/off") != -1) {
    s.write("3");
    Serial.println("relay2 off");
  }
  
  if (request.indexOf("/relay3/on") != -1) {
    s.write("4");
    Serial.println("relay3 on");
  }
  
  if (request.indexOf("/relay3/off") != -1) {
    s.write("5");
    Serial.println("relay3 off");
  }
 

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one

 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
