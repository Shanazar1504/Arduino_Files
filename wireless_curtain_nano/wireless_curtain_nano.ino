#include <IRremote.h>
#include <SoftwareSerial.h>
SoftwareSerial master (4, 5);
String stream;


#define in1 7
#define in2 8

const int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(9600);
  master.begin(115200);
  irrecv.enableIRIn();
  irrecv.blink13(true);
  pinMode(in2, OUTPUT);
  pinMode(in1, OUTPUT);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void loop() {
  if (master.available()) {
    stream = master.readStringUntil('\n');
    stream.trim();
    if (stream.length() > 0) {
      if (stream == "up") {
        up();
        delay(2500);
        stoppp();
        Serial.println("CURTAIN_UP");
      }
      else if (stream == "do") {
        down();
        delay(2500);
        stoppp();
        Serial.println("CURTAIN_DOWN");
      }
    }
  } else if (irrecv.decode(&results)) {
    Serial.println(results.value);
    irrecv.resume();
    if (results.value == 16187647) {
      up();
      delay(2500);
      stoppp();
      Serial.print("CURTAIN_UP");
    } else if (results.value == 16220287) {
      down();
      delay(2500);
      stoppp();
      Serial.print("CURTAIN_DOWN");
    }
  }
}

void up() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}

void down() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}

void stoppp() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}
