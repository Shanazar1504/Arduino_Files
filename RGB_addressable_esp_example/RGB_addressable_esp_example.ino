#include <FastLED.h>

#define NUM_LEDS 3

#define LED_PIN_1 2
#define LED_PIN_2 3
#define LED_PIN_3 4
#define LED_PIN_4 5

CRGB leds_1[NUM_LEDS];
CRGB leds_2[NUM_LEDS];
CRGB leds_3[NUM_LEDS];
CRGB leds_4[NUM_LEDS];

const int input = 9;

int val = 0;

void setup() {
  Serial.begin(9600);
  pinMode(input, INPUT);
  FastLED.addLeds<WS2812, LED_PIN_1, GRB>(leds_1, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_2, GRB>(leds_2, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_3, GRB>(leds_3, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_4, GRB>(leds_4, NUM_LEDS);
  FastLED.setBrightness(150); 
}

void loop() {
  
  val = digitalRead(input);
  Serial.println(val);
  
  if (val == 1) {
    Traffic10();
  }
  else if (val == 0) {
    Autonomus();
  }


}

void Autonomus() {
  // Set the first traffic light to red and the second traffic light to green
  leds_1[0] = CRGB::Red;
  leds_1[1] = CRGB::Black;
  leds_1[2] = CRGB::Black;

  leds_2[0] = CRGB::Black;
  leds_2[1] = CRGB::Black;
  leds_2[2] = CRGB::Green;

  leds_3[0] = CRGB::Black;
  leds_3[1] = CRGB::Black;
  leds_3[2] = CRGB::Green;

  leds_4[2] = CRGB::Red;
  leds_4[1] = CRGB::Black;
  leds_4[0] = CRGB::Black;

  FastLED.show();
  delay(5000);

  leds_1[0] = CRGB::Black;
  leds_1[1] = CRGB::Yellow;
  leds_1[2] = CRGB::Black;

  leds_2[0] = CRGB::Black;
  leds_2[1] = CRGB::Yellow;
  leds_2[2] = CRGB::Black;

  // Set the first traffic light to red and the second traffic light to green
  leds_3[0] = CRGB::Black;
  leds_3[1] = CRGB::Yellow;
  leds_3[2] = CRGB::Black;

  leds_4[2] = CRGB::Black;
  leds_4[1] = CRGB::Yellow;
  leds_4[0] = CRGB::Black;

  FastLED.show();
  delay(2000);

  // Set the first traffic light to green and the second traffic light to red
  leds_1[0] = CRGB::Black;
  leds_1[1] = CRGB::Black;
  leds_1[2] = CRGB::Green;

  leds_2[0] = CRGB::Red;
  leds_2[1] = CRGB::Black;
  leds_2[2] = CRGB::Black;

  leds_3[0] = CRGB::Red;
  leds_3[1] = CRGB::Black;
  leds_3[2] = CRGB::Black;

  leds_4[2] = CRGB::Black;
  leds_4[1] = CRGB::Black;
  leds_4[0] = CRGB::Green;

  FastLED.show();
  delay(5000);

  leds_1[0] = CRGB::Black;
  leds_1[1] = CRGB::Yellow;
  leds_1[2] = CRGB::Black;

  leds_2[0] = CRGB::Black;
  leds_2[1] = CRGB::Yellow;
  leds_2[2] = CRGB::Black;

  // Set the first traffic light to red and the second traffic light to green
  leds_3[0] = CRGB::Black;
  leds_3[1] = CRGB::Yellow;
  leds_3[2] = CRGB::Black;

  leds_4[2] = CRGB::Black;
  leds_4[1] = CRGB::Yellow;
  leds_4[0] = CRGB::Black;

  FastLED.show();
  delay(2000);
}

void Traffic10() {

  // Set the first traffic light to red and the second traffic light to green
  leds_1[0] = CRGB::Red;
  leds_1[1] = CRGB::Black;
  leds_1[2] = CRGB::Black;

  leds_2[0] = CRGB::Black;
  leds_2[1] = CRGB::Black;
  leds_2[2] = CRGB::Green;

  leds_3[0] = CRGB::Black;
  leds_3[1] = CRGB::Black;
  leds_3[2] = CRGB::Green;

  leds_4[2] = CRGB::Red;
  leds_4[1] = CRGB::Black;
  leds_4[0] = CRGB::Black;

  FastLED.show();
  delay(10000);

  leds_1[0] = CRGB::Black;
  leds_1[1] = CRGB::Yellow;
  leds_1[2] = CRGB::Black;

  leds_2[0] = CRGB::Black;
  leds_2[1] = CRGB::Yellow;
  leds_2[2] = CRGB::Black;

  // Set the first traffic light to red and the second traffic light to green
  leds_3[0] = CRGB::Black;
  leds_3[1] = CRGB::Yellow;
  leds_3[2] = CRGB::Black;

  leds_4[2] = CRGB::Black;
  leds_4[1] = CRGB::Yellow;
  leds_4[0] = CRGB::Black;

  FastLED.show();
  delay(2000);

  // Set the first traffic light to green and the second traffic light to red
  leds_1[0] = CRGB::Black;
  leds_1[1] = CRGB::Black;
  leds_1[2] = CRGB::Green;

  leds_2[0] = CRGB::Red;
  leds_2[1] = CRGB::Black;
  leds_2[2] = CRGB::Black;

  leds_3[0] = CRGB::Red;
  leds_3[1] = CRGB::Black;
  leds_3[2] = CRGB::Black;

  leds_4[2] = CRGB::Black;
  leds_4[1] = CRGB::Black;
  leds_4[0] = CRGB::Green;

  FastLED.show();
  delay(5000);

  leds_1[0] = CRGB::Black;
  leds_1[1] = CRGB::Yellow;
  leds_1[2] = CRGB::Black;

  leds_2[0] = CRGB::Black;
  leds_2[1] = CRGB::Yellow;
  leds_2[2] = CRGB::Black;

  // Set the first traffic light to red and the second traffic light to green
  leds_3[0] = CRGB::Black;
  leds_3[1] = CRGB::Yellow;
  leds_3[2] = CRGB::Black;

  leds_4[2] = CRGB::Black;
  leds_4[1] = CRGB::Yellow;
  leds_4[0] = CRGB::Black;

  FastLED.show();
  delay(2000);
}
