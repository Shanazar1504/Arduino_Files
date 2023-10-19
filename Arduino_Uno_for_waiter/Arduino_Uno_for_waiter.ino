#include <SoftwareSerial.h>
SoftwareSerial master (4, 5);
String stream;

void setup() {
  Serial.begin(9600);
  master.begin(115200);
}

void loop() {
  if (master.available()) {
    stream = master.readStringUntil('\n');
    stream.trim();
    if (stream.length() > 0) {
      if (stream == "first") {
        Serial.println("St");
      }
      else if (stream == "second") {
        Serial.println("Stt");
      }
      else if (stream == "third") {
        Serial.println("Sttt");
      }
//      Serial.println(stream);
      stream = "";
    }
  }
}
