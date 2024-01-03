const int irSensor1 = 4;  // Pin for IR Sensor 1
const int irSensor2 = 2;  // Pin for IR Sensor 2
const int irSensor3 = 3;  // Pin for IR Sensor 3

const int relay1 = 5;     // Pin for Relay 1
const int relay2 = 6;     // Pin for Relay 2
const int relay3 = 7;     // Pin for Relay 3

void setup() {
   Serial.begin(9600);  // Initialize serial communication
   
  pinMode(irSensor1, INPUT);
  pinMode(irSensor2, INPUT);
  pinMode(irSensor3, INPUT);

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);

  // Initialize relays to OFF state
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
}

void loop() {
  
  // Read the state of each IR sensor
  int state1 = digitalRead(irSensor1);
  int state2 = digitalRead(irSensor2);
  int state3 = digitalRead(irSensor3);

 // Print sensor states to the serial monitor
  Serial.print("Sensor 1: ");
  Serial.print(state1);
  Serial.print("\t Sensor 2: ");
  Serial.print(state2);
  Serial.print("\t Sensor 3: ");
  Serial.println(state3);
  
  // If any of the sensors detect an object (LOW state), turn on the corresponding relay
  if (state1 == LOW) {
    digitalWrite(relay1, HIGH);  // Turn on Relay 1
    delay(5000);
    digitalWrite(relay1, LOW);
  } else {
    digitalWrite(relay1, LOW);   // Turn off Relay 1
  }

  if (state2 == LOW) {
    digitalWrite(relay2, HIGH);  // Turn on Relay 2
    delay(5000);
    digitalWrite(relay2, LOW);
  } else {
    digitalWrite(relay2, LOW);   // Turn off Relay 2
  }

  if (state3 == LOW) {
    digitalWrite(relay3, HIGH);  // Turn on Relay 3
    delay(3000);
    digitalWrite(relay3, LOW);
  } else {
    digitalWrite(relay3, LOW);   // Turn off Relay 3
  }

  delay(100);  // Add a small delay to avoid rapid sensor readings
}
