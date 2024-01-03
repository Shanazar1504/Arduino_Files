#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_NeoPixel.h>

// RTC
RTC_DS3231 rtc;

// WS2812B 7-segment display
#define LED_PIN 6
#define NUM_LEDS 58
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);

  // Initialize RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // Initialize WS2812B LED strip
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  Serial.begin(9600);
  DateTime now = rtc.now();

  // Extract hours, minutes, and seconds
  int hours = now.hour();
  int minutes = now.minute();
  int seconds = now.second();

  Serial.print("Hour: ");
  Serial.print(hours);
  Serial.print(", Minute: ");
  Serial.println(minutes);

  // Update the LED display
  updateLEDs(hours, minutes, seconds);

  // Delay for one second
  delay(1000);
}

void updateLEDs(int hours, int minutes, int seconds) {
  // Clear previous LED display
  strip.clear();

  // Display hours
  displayDigit(hours / 10, 0); // Tens place
  displayDigit(hours % 10, 4); // Ones place

  // Display minutes
  displayDigit(minutes / 10, 11); // Tens place
  displayDigit(minutes % 10, 18); // Ones place

  // Display seconds with blinking dots
  if (seconds % 2 == 0) {
    strip.setPixelColor(28, strip.Color(255, 0, 0)); // Blinking dot at position 31
    strip.setPixelColor(29, strip.Color(255, 0, 0)); // Blinking dot at position 32
  }

  strip.show(); // Update the LED display
}

void displayDigit(int digit, int position) {
  // Define patterns for each digit (0-9)
  const uint8_t digitPatterns[][7] = {
    {1, 1, 1, 1, 1, 1, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0}, // 1
    // ... patterns for 2-9
  };

  // Display the digit on the LED strip
  for (int i = 0; i < 7; i++) {
    if (digitPatterns[digit][i] == 1) {
      strip.setPixelColor(position + i, strip.Color(255, 0, 0)); // Set LED color (red in this example)
    }
  }
}
