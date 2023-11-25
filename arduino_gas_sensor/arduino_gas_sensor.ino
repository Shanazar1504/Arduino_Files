#define gassensor A0
#define high 200


int gas;

const int buzzer = 4;

void setup() {
  Serial.begin(9600);
  pinMode(gassensor, INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  gasss();
}
void gasss() {
  gas = analogRead(gassensor);
  Serial.println(gas);
  if (gas >= high) {
    digitalWrite(buzzer, HIGH);
  }
  else {
    digitalWrite(buzzer, LOW);
  }
}
