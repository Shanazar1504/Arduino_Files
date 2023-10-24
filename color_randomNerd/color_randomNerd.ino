
#define S0_PIN A0
#define S1_PIN A1
#define S2_PIN A2
#define S3_PIN A3
#define OUT_PIN  2

void setup() {

  // Set the S0, S1, S2, S3 Pins as Output
  pinMode(S0_PIN, OUTPUT);
  pinMode(S1_PIN, OUTPUT);
  pinMode(S2_PIN, OUTPUT);
  pinMode(S3_PIN, OUTPUT);
  //Set OUT_PIN as Input
  pinMode(OUT_PIN, INPUT);

  // Set Pulse Width scaling to 20%
  analogWrite(S0_PIN, HIGH);
  analogWrite(S1_PIN, LOW);
  // Enable UART for Debugging
  Serial.begin(9600);
}

void loop()
{
  int r, g, b;
  r = process_red_value();
  delay(200);
  g = process_green_value();
  delay(200);
  b = process_blue_value();
  delay(200);
  Serial.print("r = ");
  Serial.print(r);
  Serial.print(" ");
  Serial.print("g = ");
  Serial.print(g);
  Serial.print(" ");
  Serial.print("b = ");
  Serial.print(b);
  Serial.print(" ");
  Serial.println();
  if (r < 79)
  {
    Serial.println("Colour Pink");
  }
  else if (g < 89)
  {
    Serial.println("Colour Green");
  }
  else if (b < 89)
  {
    Serial.println("Colour Blue");
  }
  else if (r < 79 && g < 89)
  {
    Serial.println("Colour Yellow");
  }
}

int process_red_value()
{
  analogWrite(S2_PIN, LOW);
  analogWrite(S3_PIN, LOW);
  int pulse_length = pulseIn(OUT_PIN, LOW);
  return pulse_length;
}
int process_green_value()
{
  analogWrite(S2_PIN, HIGH);
  analogWrite(S3_PIN, HIGH);
  int pulse_length = pulseIn(OUT_PIN, LOW);
  return pulse_length;
}
int process_blue_value()
{
  analogWrite(S2_PIN, LOW);
  analogWrite(S3_PIN, HIGH);
  int pulse_length = pulseIn(OUT_PIN, LOW);
  return pulse_length;
}
