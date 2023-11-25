#include <ESP8266WiFi.h>
int openactive= D1;
int closeactive=  D2;
int stopp = D3;
int lsabove = D4;
int lsdown = D5;
int merkeropen1 = 0;
int merkerclose1 = 0;
int moa; // merker openaktive: Merker für gegenseitige Sperre
int mca; //merker closeaktive: Merker für Gegenseitige Sperre
int val;
int merkerlsdown = 1;
int merkerlsabove = 1;

const char* ssid = "WLANName";
const char* password = "Password";
 
// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);
 
void setup() {
  pinMode(openactive, OUTPUT);
  digitalWrite(openactive, HIGH);
  pinMode(closeactive, OUTPUT);
  digitalWrite(closeactive, HIGH);
  pinMode(lsabove, INPUT);
  pinMode(lsdown, INPUT);

  
  Serial.begin(115200);
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
  Serial.println(WiFi.localIP());
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    //Endschalter oben
  if(digitalRead(lsabove) == 1 && merkerlsabove == 1){
    merkerlsabove = 0;
    moa = 0;
    Serial.print("Endschalter oben");
    val = 1;
    digitalWrite(openactive, val);}
//Endschalter unten
  if(digitalRead(lsdown) == 1 && merkerlsdown == 1){
    merkerlsdown = 0;   
    mca = 0; 
    Serial.print("Endschalter unten");
    val = 1;
    digitalWrite(closeactive, val);}    
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  

//Runterfahren Button 1
  if (req.indexOf("closeactive") != -1 && moa == 0 /*&& digitalRead(lsdown) != 1*/){
    mca = 1;
    merkerlsabove = 1;
    merkerlsdown = 1;  
    val = 0;
    digitalWrite(closeactive, val);
    delay(1000);}
    

// Hochfahren Button 2
  else if (req.indexOf("openactive") != -1 && mca == 0 /*&& digitalRead(lsabove) != 1*/){ //merkercloseaktive
   moa = 1;
    merkerlsabove = 1;
    merkerlsdown = 1;
   val = 0;
   digitalWrite(openactive, val);
   delay(1000);}
   

//Stopp Button 3
  else if (req.indexOf("stopp") != -1){
    mca = 0;
    moa = 0;
    merkerlsabove = 1;
    merkerlsdown = 1;
    val = 1;
    Serial.print("Stopp");
    digitalWrite(closeactive, val);
    digitalWrite(openactive, val);}
  
  else {
    Serial.println("invalid request");
    client.stop();
    return;
  }
 
  
  
  client.flush();

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
  s += (val)?"high":"low";
  s += "</html>\n";
 
  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");
 
  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}
