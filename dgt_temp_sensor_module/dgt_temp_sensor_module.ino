#define pin A0

void setup() {
  Serial.begin(9600);
}

void loop() {
int reading = analogRead(pin);
float voltage = reading*(5.0/1024.0);
float temp = voltage*100;
  Serial.println(temp, 1);
delay(1000);
}
