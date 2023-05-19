unsigned long previousMillisGetHR = 0;
unsigned long previousMillisHR = 0;

const long intervalGetHR = 10;
unsigned long intervalHR = 3000;



int PulseSensorPurplePin = A0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
int LED13 = 13;   //  The on-board Arduion LED


int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 600;            // Determine which Signal to "count as a beat", and which to ingore.
int cntHB = 0;
boolean ThresholdStat = true;
int BPMval = 0;


void GetHeartRate() {
  unsigned long currentMillisGetHR = millis();
  if (currentMillisGetHR - previousMillisGetHR >= intervalGetHR) {
    previousMillisGetHR = currentMillisGetHR;

    int PulseSensorHRVal = analogRead(PulseSensorPurplePin);
    
    if (PulseSensorHRVal > Threshold && ThresholdStat == true) {
      cntHB++;
      ThresholdStat = false;
    }
    if (PulseSensorHRVal < Threshold) {
      ThresholdStat = true;
    }
  }

  unsigned long currentMillisHR = millis();
  if (currentMillisHR - previousMillisHR >= intervalHR ) {
    previousMillisHR = currentMillisHR;

    BPMval = cntHB * 6;
    Serial.print("BPM:");
    Serial.println(BPMval);

    cntHB = 0;
  }
}

// The SetUp Function:
void setup() {
  pinMode(LED13, OUTPUT);        // pin that will blink to your heartbeat!
  Serial.begin(9600);         // Set's up Serial Communication at certain speed.

}

// The Main Loop Function
void loop() {
  GetHeartRate();
}

//  Signal = analogRead(PulseSensorPurplePin);  // Read the PulseSensor's value.
//  // Assign this value to the "Signal" variable.
//
//  Serial.println(Signal);                    // Send the Signal value to Serial Plotter.
//
//
//  if (Signal > Threshold) {                        // If the signal is above "550", then "turn-on" Arduino's on-Board LED.
//    digitalWrite(LED13, HIGH);
//  } else {
//    digitalWrite(LED13, LOW);               //  Else, the sigal must be below "550", so "turn-off" this LED.
//  }
//
//
//  delay(10);
//
//
//}
