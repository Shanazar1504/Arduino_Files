#include <ESP8266WiFi.h>
void setup(){
  Serial.begin(9600);
  WiFi.disconnect();
  Serial.println("START");
  WiFi.begin("2103");
  while((!(WiFi.status() == WL_CPNNECTED())));
  delay(300);
  Serial.println("Connected");
  Serial.println("Your ip is:");
  Serial.println((WiFi.localIP()));
  Serial.println("Your gateway is:");
  Serial.println(WiFi.gatewayIP().toString().c_str()));
  Serial.println("Your host name is:");
  Serial.println((WiFi.hostname()));
  
}
void loop()
{
  
}
