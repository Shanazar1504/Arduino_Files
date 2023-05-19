#include <ESP8266WiFi.h>

void setup()
{
  Serial.begin(9600);
  
  delay (3000);
  WiFi.disconnect();
  Serial.println("START");
  WiFi.begin("2103");
  while ((!(WiFi.status()==WL_CONNECTED))){
    delay(3000);
    Serial.println("Please wait...");
  
  }Serial.println("Connected");
   Serial.println("Your IP is:");
   Serial.println((WiFi.localIP()));
   Serial.println(" Your gateway is: ");
   Serial.println((WiFi.gatewayIP().toString().c_str()));
   Serial.println("Your host name is:");
   Serial.println((WiFi.hostname()));
  }
  void loop()
  {
  
  }
