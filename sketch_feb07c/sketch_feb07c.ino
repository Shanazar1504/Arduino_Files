#include <IRremote.h>

const int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    irrecv.resume();
    if (results.value == 16187647) {
      Serial.println("up");
    } else if (results.value == 16220287) {
      Serial.println("down");
    }
  }
}
