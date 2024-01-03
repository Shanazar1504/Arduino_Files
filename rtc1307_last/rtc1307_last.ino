#include <FastLED.h>
#include <Wire.h>
#include "RTClib.h"

#define NUM_LEDS 30
#define DATA_PIN 6
CRGB LEDs[NUM_LEDS];

RTC_DS1307 rtc;

void setup() {
  // Initialize LED strip
  FastLED.delay(3000);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(LEDs, NUM_LEDS);

  Serial.begin(9600);
  while (!Serial) { /* Wait until serial is ready */ }

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  Serial.println("RTC set to the sketch compile time");
}

void loop() {
  DateTime now = rtc.now();

  int hh = now.hour();
  int mm = now.minute();
  int ss = now.second();

  Serial.print("Hour: ");
  Serial.print(hh, DEC);
  Serial.print(", Minute: ");
  Serial.print(mm, DEC);
  Serial.print(", Second: ");
  Serial.println(ss, DEC);

  displayTime(hh, mm, ss);

  FastLED.show();
  delay(1000);
}

void displayTime(int hours, int minutes, int seconds) {
  // Clear the LED array
  fill_solid(LEDs, NUM_LEDS, CRGB::Black);

  // Display hours in red
  int hrLED = map(hours, 0, 23, 0, NUM_LEDS - 1);
  LEDs[hrLED] = CRGB::Red;

  // Display minutes in green
  int minLED = map(minutes, 0, 59, 0, NUM_LEDS - 1);
  LEDs[minLED] = CRGB::Green;

  // Display seconds in blue
  int secLED = map(seconds, 0, 59, 0, NUM_LEDS - 1);
  LEDs[secLED] = CRGB::Blue;
}
