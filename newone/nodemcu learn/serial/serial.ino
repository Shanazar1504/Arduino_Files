#include <ESP8266WiFi.h>
void setup(){
  Serial.begin(9600);
  delay(3000);
  WiFi.disconnect();
  Serial.println("START");
  WiFi.begin("2103");
  while((!(WiFi.status() == WL_CONNECTED)));
  delay(300);
  Serial.print("..");
  Serial.println("Connected");
  }
void loop()
{
  
}
