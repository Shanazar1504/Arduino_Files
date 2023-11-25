#include <Wire.h>
#include <Adafruit_GFX.h>
#include <SimpleTimer.h>
#include <SoftwareSerial.h>

SimpleTimer timer;
SoftwareSerial master (4, 5);
String stream;

float calibration_value = 21.34 - 0.7;
int phval = A0;
unsigned long int avgval;
int buffer_arr[10], temp;

float ph_act;

const int button = 2;
int button_state = 0;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  master.begin(115200);
  pinMode(button, INPUT);

}
void loop() {
  button_state = digitalRead(button);
  timer.run(); // Initiates SimpleTimer


  if (button_state == 0) {
    for (int i = 0; i < 10; i++)
    {
      buffer_arr[i] = analogRead(A0);
      delay(30);
    }
    for (int i = 0; i < 9; i++)
    {
      for (int j = i + 1; j < 10; j++)
      {
        if (buffer_arr[i] > buffer_arr[j])
        {
          temp = buffer_arr[i];
          buffer_arr[i] = buffer_arr[j];
          buffer_arr[j] = temp;
        }
      }
    }
    avgval = 0;
    for (int i = 2; i < 8; i++)
      avgval += buffer_arr[i];
    float volt = (float)avgval * 5.0 / 1024 / 6;
    ph_act = -5.70 * volt + calibration_value;

    Serial.println("pH Val: ");
    Serial.println(ph_act);
    master.println(ph_act);
  }

}
