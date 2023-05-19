#include <ESP8266WiFi.h>

WiFiServer server(80);

void setup()
{
  Serial.begin(9600);
  WiFi.disconnect();
  delay(3000);
  Serial.println("START");
  WiFi.begin("2103");
  while((!(WiFi.status()==WL_CONNECTED))){
   delay(300);
    Serial.print("Please wait...");
  }Serial.println("Connected.My IP adress is:");
   Serial.println((WiFi.localIP()));
  server.begin();
  }

void loop(){
}
