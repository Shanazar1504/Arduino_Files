#include <FastLED.h>
#include <Wire.h>
#include <RTClib.h>

#define NUM_LEDS 30
#define DATA_PIN 6
CRGB LEDs[NUM_LEDS];

// Change this color if you want another color, for example CRGB::Red
CRGB color = CRGB::White;

RTC_DS1307 rtc;

unsigned long previousMillis = 0;
const long interval = 1000;  // Blink interval in milliseconds

void setup () {
  // Initialize LED strip
  FastLED.delay(3000);

  // Check if your LED strip is an RGB or GRB version (third parameter)
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(LEDs, NUM_LEDS);

  Serial.begin(9600);
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // You can set the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  }
}

void loop () {

  DateTime now = rtc.now();

  int hl = now.hour() / 10;
  int hr = now.hour() % 10;
  int ml = now.minute() / 10;
  int mr = now.minute() % 10;

  // Print the current hour and minute
  Serial.print("Hour: ");
  Serial.print(now.hour(), DEC);
  Serial.print(", Minute: ");
  Serial.println(now.minute(), DEC);

  displayTime(0, mr);
  displayTime(7, ml);
  displayTime(16, hr);
  displayTime(23, hl);

  FastLED.show();

  delay(1000 * 29);
}

void displayTime(int startindex, int number) {
  byte numbers[] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111, // 9
  };

  for (int i = 0; i < 7; i++) {
    LEDs[i + startindex] = ((numbers[number] & 1 << i) == 1 << i) ? color : CRGB::Black;
  }

  // Dots
  LEDs[14] = color; // Left dot
  LEDs[15] = color; // Right dot
}

void toggleDots() {
  // Toggle dots
  LEDs[14] = (LEDs[14] == CRGB::Black) ? color : CRGB::Black;
  LEDs[15] = (LEDs[15] == CRGB::Black) ? color : CRGB::Black;
}
