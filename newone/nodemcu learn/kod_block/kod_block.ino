#include <WiFiClient.h> 
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

WiFiClient client;
WiFiServer server(80);

const char* ssid = "210302";                 
const char* password = "2103";

String  data = "";
 

int leftMotorForward = 2;     /* GPIO2(D4) -> IN3   */
int rightMotorForward = 14;   /* GPIO15(D5) -> IN1  */
int leftMotorBackward = 0;    /* GPIO0(D3) -> IN4   */
int rightMotorBackward = 12;  /* GPIO13(D6) -> IN2  */
       
void  setup() 
{
    Serial.begin(115200);                 
    delay(10);
 
   
  pinMode(leftMotorForward, OUTPUT);
  pinMode(rightMotorForward, OUTPUT);
  pinMode(leftMotorBackward, OUTPUT);
  pinMode(rightMotorBackward, OUTPUT);
  
    Serial.println('\n');
     
    WiFi.begin(ssid,  password);                          //  Connect to  the network
    Serial.print("Connecting  to  ");
    Serial.print(ssid); Serial.println("  ...");
    int i = 0;
    while (WiFi.status()  !=  WL_CONNECTED) { //  Wait  for the Wi-Fi to  connect
        delay(1000);
        Serial.print(++i);  Serial.print('  ');
    }
    Serial.println('\n');
    Serial.println("Connection  established!");   
    Serial.print("IP  address:\t");
    Serial.println(WiFi.localIP());
    
      server.begin();

}

void  loop()
{ 
  
   client = server.available();
  if (!client) return;
   
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
