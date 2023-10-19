const int PIR = 4;
const int relay = 16;
int pir_val = 0;

void setup() {
  Serial.begin(9600);
  pinMode(PIR, INPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);

  // put your setup code here, to run once:

}

void loop() {
  pir_val = digitalRead(PIR);
  Serial.println(pir_val);
  if (pir_val == 1) {
    Serial.println(pir_val);
    digitalWrite(relay, HIGH);
  } else {
    Serial.println(pir_val);
    digitalWrite(relay, LOW);
  }
  // put your main code here, to run repeatedly:

}
