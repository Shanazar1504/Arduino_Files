#include <Arduino.h>
#include <ESP8266WiFi.h>

byte relON[] = {0xA0, 0x01, 0x01, 0xA2};
byte relOFF[] = {0xA0, 0x01, 0x00, 0xA1};


byte relON2[] = {0xA0, 0x02, 0x01, 0xA3};
byte relOFF2[] = {0xA0, 0x02, 0x00, 0xA2};

void setup() {
  Serial.begin(9600);
  Serial.write(relON, sizeof(relON));
  Serial.write(relON2, sizeof(relON2));

}
void loop() {
  
    Serial.write(relON, sizeof(relON));
    delay(1500);

    
    Serial.write(relON2, sizeof(relON2));
    delay(1500);
    
    Serial.write(relOFF, sizeof(relOFF));
    delay(1500);

    
    Serial.write(relOFF2, sizeof(relOFF2));
    delay(1500);
}
