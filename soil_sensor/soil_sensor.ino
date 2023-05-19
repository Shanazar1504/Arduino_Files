#include <ESP8266WiFi.h>
#include <Wire.h>

const int sensor_pin = A0; 

void setup() {
   Serial.begin(115200);
}

void loop() 
{
  int moisture_percentage;
 
  moisture_percentage = ( 100.00 - ( (analogRead(sensor_pin)/1023.00) * 100.00 ) );
 
    Serial.print("Soil Moisture(in Percentage) = ");
    Serial.print(moisture_percentage);
    Serial.println("%");
}
