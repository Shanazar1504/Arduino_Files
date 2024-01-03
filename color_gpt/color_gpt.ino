#include <tcs3200.h>

enum Color { RED, GREEN, BLUE, PURPLE, ORANGE, YELLOW, WHITE, UNKNOWN };

tcs3200 tcs(A0, A1, A2, A3, 2); // (S0, S1, S2, S3, output pin)

int red, green, blue, white, ir_val;

Color previousColor = UNKNOWN;

void setup() {
  Serial.begin(9600);
  Serial.println("Serial is Listening ... ");
}

Color detectColor(int red, int green, int blue, int white) {
  if (blue >= 28 && green < 25 && red > 21 && white > 65 && white < 85 ) {
    return BLUE;
  } else if (blue >= 24 && blue <= 32 && red <= 33 && green <= 32 && white <= 85) {
    return GREEN;
  } else if (red >= 34  && red <= 40 && green <= 28 && red > green && white < 90) {
    return RED;
    //  } else if (green < 27 && blue < 27 && white < 82) {
    //    return ORANGE;
    //  } else if (red < 52 && red > 39 && green > 35 && blue > 35 && white > 55) {
    //    return WHITE;
    //  } else if (red > 29 && green >= 25 && white < 90) {
    //    return YELLOW;
  } else if (red > 26 && green < 25 && blue < 39 && white > 70 && white < 85) {
    return PURPLE;
  } else {
    return UNKNOWN;
  }
}

void loop() {
  red = tcs.colorRead('r');
  green = tcs.colorRead('g');
  blue = tcs.colorRead('b');
  white = tcs.colorRead('c');

  Serial.print("R= "); Serial.print(red); Serial.print("    ");
  Serial.print("G= "); Serial.print(green); Serial.print("    ");
  Serial.print("B= "); Serial.print(blue); Serial.print("    ");
  Serial.print("W(clear)= "); Serial.print(white); Serial.print("    ");

  switch (detectColor(red, green, blue, white)) {
    case RED:
      Serial.println("RED");
      break;
    case GREEN:
      Serial.println("GREEN");
      break;
    case BLUE:
      Serial.println("BLUE");
      break;
    case ORANGE:
      Serial.println("ORANGE");
      break;
    case WHITE:
      Serial.println("WHITE");
      break;
    case YELLOW:
      Serial.println("YELLOW");
      break;
    case PURPLE:
      Serial.println("PURPLE");
      break;
    default:
      Serial.println("UNKNOWN COLOR");
  }

  delay(1000);
}
