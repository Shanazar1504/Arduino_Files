#include <SoftwareSerial.h>
SoftwareSerial mys(2, 3);

void setup() {
  Serial.begin(9600);
  mys.begin(9600);// put your setup code here, to run once:
  delay(5000);

}

void loop() {
  String IncomingString = "";
  boolean StringReady = false;
  while (mys.available()) {
    IncomingString = mys.readString();
    StringReady = true;
  }
  if (StringReady) {
    Serial.println("Gelen sms:" + IncomingString );
  }
} 
