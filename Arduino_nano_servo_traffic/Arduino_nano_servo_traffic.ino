#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x27, 16 columns and 2 rows

const int servoMotorPin = 9; // Pin for the servo motor

Servo myServo;

int countDownTime = 10;
unsigned long previousMillis = 0;
const long interval = 1000; // Update interval in milliseconds

const int increaseButtonPin = 2; // Pin for the button to increase the timer
const int decreaseButtonPin = 3; // Pin for the button to decrease the timer
const int setButtonPin = 4;

void setup()
{
  Serial.begin(9600); // Initialize Serial Monitor
  lcd.init();
  lcd.backlight();
  lcd.println("Countdown Timer");
  myServo.attach(servoMotorPin);
  myServo.write(17);
  // Set up button pins
  pinMode(increaseButtonPin, INPUT_PULLUP);
  pinMode(decreaseButtonPin, INPUT_PULLUP);
  pinMode(setButtonPin, INPUT_PULLUP);
}

void loop()
{
  Serial.println(digitalRead(increaseButtonPin));
  Serial.println(digitalRead(decreaseButtonPin));
  Serial.println(digitalRead(setButtonPin));
  //  delay(1000);
  counter();
}
void counter()
{
  unsigned long currentMillis = millis();

  // Check if buttons are pressed
  if (digitalRead(increaseButtonPin) == LOW)
  {
    increaseTimer();
  }

  if (digitalRead(decreaseButtonPin) == LOW)
  {
    decreaseTimer();
  }

  if (digitalRead(setButtonPin) == LOW)
  {
    setTimer();
  }

  // Update countdown timer
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.println("Time: ");
    lcd.println(countDownTime);

    Serial.println("Time: ");
    Serial.println(countDownTime);

    if (countDownTime == 0)
    {
      lcd.setCursor(0, 1);
      lcd.println("Time's up!");
      Serial.println("Time's up!");
      myServo.write(0);
      delay(15000);
      myServo.write(17);
      // Reset countdown timer to the initial value
      countDownTime = 10;
    }
    else
    {
      countDownTime--;
    }
  }
}
void increaseTimer()
{
  countDownTime+=1;
  //  delay(500);  // Debounce delay
}

void decreaseTimer()
{
  if (countDownTime > 0)
  {
    countDownTime-=1;
  }
  //  delay(500);  // Debounce delay
}

void setTimer()
{
  // You can modify this part to set the timer to a specific value
  countDownTime = 15;
  //  delay(500);  // Debounce delay
}
