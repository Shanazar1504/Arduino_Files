#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address and dimensions (change if necessary)

void setup() {
  lcd.begin(16, 2);
  lcd.backlight();
  rtc.begin();

  // Uncomment the following line if you need to set the date and time on the RTC module
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  lcd.print("Clock Example");
}

void loop() {
  DateTime now = rtc.now();

  lcd.setCursor(0, 1);
  lcd.print(now.toString("yyyy-MM-dd"));

  lcd.setCursor(11, 1);
  lcd.print(now.toString("HH:mm:ss"));

  delay(1000);
}
