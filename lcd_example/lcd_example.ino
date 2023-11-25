#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.print("Test");
  lcd.backlight();
}

void loop() {
  // Your main code goes here
}
