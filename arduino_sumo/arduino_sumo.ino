#define enA 9
#define enB 8
#define in1 4
#define in2 5
#define in3 6
#define in4 7

int valSpeed = 255;

String readString;  // declaring string

void setup() {
  Serial.begin(9600);    // set up Serial library at 9600 bps
  Serial.println("*Robot Remote Control Mode*");

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);


}

void loop() {
  while (Serial.available() > 0) {
    char command = Serial.read();    // gets one byte from serial buffer
    Serial.println(command);

    switch (command) {
      case 'F':   // move forward
        analogWrite(enA, 255);
        analogWrite(enB, 255);
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);

        break;
      case 'B':   // move backward
        analogWrite(enA, 255);
        analogWrite(enB, 255);
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        break;
      case 'R':   // turn right
        analogWrite(enA, 255);
        analogWrite(enB, 255);
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        break;
      case 'L':   // turn left
        analogWrite(enA, 255);  
        analogWrite(enB, 255);
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        break;
      case 'S':   // stop
        analogWrite(enA, 0);
        analogWrite(enB, 0);
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        break;
    }
  }
}
