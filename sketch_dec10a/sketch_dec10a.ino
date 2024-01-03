const int b1 = 2;
const int b2 = 3;
const int b3 = 4;
const int b4 = 5;
const int b5 = 6;

int v1, v2, v3, v4, v5;

void setup() {
  Serial.begin(9600);
  pinMode(b1, INPUT_PULLUP);
  pinMode(b2, INPUT_PULLUP);
  pinMode(b3, INPUT_PULLUP);
  pinMode(b4, INPUT_PULLUP);
  pinMode(b5, INPUT_PULLUP);

}

void loop() {

  v1 = digitalRead(b1);
    delay(500);
  v2 = digitalRead(b2);
    delay(500);
  v3 = digitalRead(b3);
    delay(500);
  v4 = digitalRead(b4);
    delay(500);
  v5 = digitalRead(b5);
    delay(500);

  Serial.println(v1);
  Serial.println(v2);
  Serial.println(v3);
  Serial.println(v4);
  Serial.println(v5);
}
