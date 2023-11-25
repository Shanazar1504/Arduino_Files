#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>
#include <Servo.h>

// Initialize RTC module
RTC_DS1307 rtc;
Servo myservo;
int pos = 0;
// Initialize LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // the I2C address if necessary

// Define setting buttons
const int buttonSetHour = 2;
const int buttonSetMinute = 3;
const int buttonSetAlarm = 4;
const int buttonDispensePill = 5;

// Variables to store time and alarm values
int setHour = 0;
int setMinute = 0;
int setAlarm = 0;
int currentHour = 0;
int currentMinute = 0;

void setup() {
  // Set up LCD
  lcd.init();
  lcd.backlight();
  lcd.print("Smart Pill Org.");

  // Set up buttons
  pinMode(buttonSetHour, INPUT);
  pinMode(buttonSetMinute, INPUT);
  pinMode(buttonSetAlarm, INPUT);
  pinMode(buttonDispensePill, INPUT);

  // Initialize RTC module
  Wire.begin();
  rtc.begin();
  myservo.attach(9);

  // Uncomment the line below if you want to set the RTC to the current date and time
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  // Set initial time and alarm values
  setHour = rtc.now().hour();
  setMinute = rtc.now().minute();
  setAlarm = setHour * 100 + setMinute;

  // Display initial values on LCD
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Time: ");
  printTime(setHour, setMinute);
  lcd.setCursor(0, 1);
  lcd.print("Alarm: ");
  lcd.print(setHour, setMinute);
}

void loop() {
  // Check if the hour setting button is pressed
  if (digitalRead(buttonSetHour) == LOW) {
    delay(250);
    setHour++;
    if (setHour > 23) {
      setHour = 0;
    }
    lcd.setCursor(6, 0);
    printTime(setHour, setMinute);
    lcd.blink();
  }

  // Check if the minute setting button is pressed
  if (digitalRead(buttonSetMinute) == LOW) {
    delay(250);
    setMinute++;
    if (setMinute > 59) {
      setMinute = 0;
    }
    lcd.setCursor(11, 0);
    printTime(setHour, setMinute);
    lcd.blink();
  }

  // Check if the alarm setting button is pressed
  if (digitalRead(buttonSetAlarm) == LOW) {
    delay(250);
    if (setAlarm == (setHour * 100 + setMinute)) {
      setAlarm = -1;
    } else {
      setAlarm = setHour * 100 + setMinute;
    }
    lcd.setCursor(7, 1);
    if (setAlarm == -1) {
      lcd.print("OFF   ");
    } {
      printTime(setHour, setMinute);
    }
    lcd.blink();
  }

  // Check if the dispense button is pressed
  if (digitalRead(buttonDispensePill) == LOW) {
    delay(250);
    if (currentHour == setHour && currentMinute == setMinute) {
      dispensePill();
    }
  }

  // Update current time
  DateTime now = rtc.now();
  currentHour = now.hour();
  currentMinute = now.minute();
  lcd.setCursor(6, 0);
  printTime(currentHour, currentMinute);
}

// Function to format and print time on LCD
void printTime(int hour, int minute) {
  if (hour < 10) {
    lcd.print("0");
  }
  lcd.print(hour);
  lcd.print(":");
  if (minute < 10) {
    lcd.print("0");
  }
  lcd.print(minute);
}

// Function to simulate pill dispensing
void dispensePill() {
   myservo.write(90);              // tell servo to go to position in variable 'pos'
    delay(300);  
    myservo.write(90);   
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dispensing pill");
  // Code to control the dispenser motor
  delay(2000);  // Simulate time for pill dispensing
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pill dispensed!");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  lcd.print(currentHour, currentMinute);
  lcd.setCursor(0, 1);
  lcd.print("Alarm: ");
  if (setAlarm == -1) {
  }
}
