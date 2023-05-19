const int lm35 = A0;
int input_val = 0;
float celsius = 0;

void setup() {
  Serial.begin(9600);  /* Define baud rate for serial communication */
}

void loop() {
  input_val = analogRead(lm35);
  celsius = (input_val * 500) / 1023;
  Serial.println("Temperature Reading:");
  Serial.print("\t\tCelsius:");
  Serial.println(celsius);
  delay(1000);
}

//
//float vref = 3.3;
//float resolution = vref/1023;
//
//void setup() {
// Serial.begin(9600);  /* Define baud rate for serial communication */
//}
//
//void loop() {
// float temperature = analogRead(A0);
// temperature = (temperature*resolution);
// temperature = temperature*100;
// Serial.println(temperature);
// delay(1000);
//}
