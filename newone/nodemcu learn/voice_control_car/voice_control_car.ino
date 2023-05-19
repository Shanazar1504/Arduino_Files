#include <WiFiClient.h> 
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

WiFiClient client;
WiFiServer server(80);
 

const char* ssid = "OGUZHAN";
const char* password = "1020304050";

String  data = ""; 


int leftMotorForward = 2;     /* GPIO2(D4) -> IN3   */
int rightMotorForward = 14;   /* GPIO15(D5) -> IN1  */
int leftMotorBackward = 0;    /* GPIO0(D3) -> IN4   */
int rightMotorBackward = 12;  /* GPIO13(D6) -> IN2  */
 
 
void setup()
{
  Serial.begin(115200);
 
  pinMode(leftMotorForward, OUTPUT);
  pinMode(rightMotorForward, OUTPUT);
  pinMode(leftMotorBackward, OUTPUT);
  pinMode(rightMotorBackward, OUTPUT);
 
  
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);
    
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
 
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    
    delay(3000);
  }
 
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());  
 
  
  server.begin();
}
 
void loop()
{
  
  client = server.available();
  if (!client) return;
  data = checkClient ();
 
  
  if (data == "forward") MotorForward();
  
  else if (data == "backward") MotorBackward();
  
  else if (data == "left") TurnLeft();
  
  else if (data == "right") TurnRight();
  
  else if (data == "stop") MotorStop();
}
 

void MotorForward(void)
{
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(rightMotorForward, HIGH);
  digitalWrite(leftMotorBackward, LOW);
  digitalWrite(rightMotorBackward, LOW);
}
 

void MotorBackward(void)
{
  digitalWrite(leftMotorBackward, HIGH);
  digitalWrite(rightMotorBackward, HIGH);
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(rightMotorForward, LOW);
}
 

void TurnLeft(void)
{
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(rightMotorForward, HIGH);
  digitalWrite(rightMotorBackward, LOW);
  digitalWrite(leftMotorBackward, HIGH);
}
 
void TurnRight(void)
{
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(rightMotorBackward, HIGH);
  digitalWrite(leftMotorBackward, LOW);
}
 

void MotorStop(void)
{
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(leftMotorBackward, LOW);
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(rightMotorBackward, LOW);
}
 

String checkClient (void)
{
  while (!client.available()) delay(1);
  String request = client.readStringUntil('\r');
  request.remove(0, 5);
  request.remove(request.length() - 9, 9);
  return request;
}
