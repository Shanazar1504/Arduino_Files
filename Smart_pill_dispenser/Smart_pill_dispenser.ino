#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo myservo;
int pos = 45;

RTC_DS1307 rtc;

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Change 0x27 to your I2C address if different

const int buttonSetHour = 3;        // Pin for setting hours button
const int buttonSetMinute = 2;      // Pin for setting minutes button
const int buttonSetAlarm = 4;       // Pin for setting alarm button
const int buttonDrugDispenser = 5;  // Pin for drug dispenser button
const int buttonWaterDispenser = 6; // Pin for water dispenser button
const int buzzer = 7;               // Pin for buzzer

int alarmHour = 12;
int alarmMinute = 00;

bool drugDispenserTriggered = false;

void setup() {
  Serial.begin(9600);
  myservo.attach(9);
  myservo.write(0);
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // You can set the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  lcd.init();
  lcd.backlight();

  pinMode(buttonSetHour, INPUT_PULLUP);
  pinMode(buttonSetMinute, INPUT_PULLUP);
  pinMode(buttonSetAlarm, INPUT_PULLUP);
  pinMode(buttonDrugDispenser, INPUT_PULLUP);
  pinMode(buttonWaterDispenser, INPUT_PULLUP);
  pinMode(buzzer, INPUT);
}

void loop() {
  DateTime now = rtc.now();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  lcd.print(now.second(), DEC);

  lcd.setCursor(0, 1);
  lcd.print("Alarm: ");
  lcd.print(alarmHour);
  lcd.print(':');
  lcd.print(alarmMinute);

  // Check if it's time to sound the alarm
  if (now.hour() == alarmHour && now.minute() == alarmMinute) {
    if (!drugDispenserTriggered) {
      drugdispenser();
      drugDispenserTriggered = true;
    }
  } else {
    drugDispenserTriggered = false;
  }

  // Check for button presses
  if (digitalRead(buttonSetHour) == LOW) {
    delay(50);  // Debounce
    incrementHour();
  }

  if (digitalRead(buttonSetMinute) == LOW) {
    delay(50);  // Debounce
    incrementMinute();
  }

  if (digitalRead(buttonSetAlarm) == LOW) {
    delay(50);  // Debounce
    setAlarm();
  }

  if (digitalRead(buttonWaterDispenser) == LOW) {
    delay(50);  // Debounce
    waterdispenser();
  }

  if (digitalRead(buttonDrugDispenser) == LOW) {
    delay(50);  // Debounce
    if (!drugDispenserTriggered) {
      drugdispenser();
      drugDispenserTriggered = true;
    }
  }

  delay(500);  // Update every second
}

void incrementHour() {
  alarmHour = (alarmHour + 1) % 24;
}

void incrementMinute() {
  alarmMinute = (alarmMinute + 1) % 60;
}

void setAlarm() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Set Alarm");
  lcd.setCursor(0, 1);
  lcd.print("Use Hour/Min");

  while (digitalRead(buttonSetAlarm) == HIGH) {
    if (digitalRead(buttonSetHour) == LOW) {
      delay(50);  // Debounce
      incrementHour();
    }

    if (digitalRead(buttonSetMinute) == LOW) {
      delay(50);  // Debounce
      incrementMinute();
    }

    lcd.setCursor(0, 1);
    lcd.print("        ");  // Clear previous minute value
    lcd.setCursor(0, 1);
    lcd.print(alarmHour);
    lcd.print(':');
    lcd.print(alarmMinute);

    delay(200);  // Delay for button responsiveness
  }

  lcd.clear();
}

void waterdispenser() {
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("Water");
  lcd.setCursor(2, 1);
  lcd.print("dispensering");
  delay(1500);
}

void drugdispenser() {
  myservo.write(45);
  delay(200);
  myservo.write(0);
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("Drug");
  lcd.setCursor(2, 1);
  lcd.print("dispensing");
  digitalWrite(buzzer, 1);
  delay(1500);
  digitalWrite(buzzer, 0);
}
