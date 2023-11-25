#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 columns and 2 rows

const int coinSensor1 = 8; // IR sensor for coin detection - Sensor 1
const int coinSensor2 = 9; // IR sensor for coin detection - Sensor 2
const int coinSensor3 = 10; // IR sensor for coin detection - Sensor 3

const int button1 = 11; // Setting button 1
const int button2 = 12; // Setting button 2
const int button3 = 13; // Setting button 3

const int pump_1 = 4;
const int pump_2 = 5;
const int pump_3 = 6;

float totalCoins = 0.0; // Total amount of coins inserted

int val_50;
int val_100;
int val_200;

void setup() {
  Serial.begin(9600);
  lcd.init(); // Initialize the LCD
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print("Drink Vending");
  lcd.setCursor(2, 1);
  lcd.print("Insert coins");

  pinMode(coinSensor1, INPUT);
  pinMode(coinSensor2, INPUT);
  pinMode(coinSensor3, INPUT);

  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);

  pinMode(pump_1, OUTPUT);
  pinMode(pump_2, OUTPUT);
  pinMode(pump_3, OUTPUT);

  digitalWrite(pump_1, 0);
  digitalWrite(pump_2, 0);
  digitalWrite(pump_3, 0);

}

void loop() {
  val_50 = digitalRead(coinSensor1);
  val_100 = digitalRead(coinSensor2);
  val_200 = digitalRead(coinSensor3);

  Serial.println(val_50);
  Serial.println(val_100);
  Serial.println(val_200);

  if (val_50 == LOW) {
    totalCoins += 0.50; // Assuming a quarter (25 cents) is inserted
    delay(200);
    updateDisplay();
  }

  if (val_100 == LOW) {
    totalCoins += 1.0; // Assuming a dime (10 cents) is inserted
    delay(200);
    updateDisplay();
  }

  if (val_200 == LOW) {
    totalCoins += 2.0; // Assuming a nickel (5 cents) is inserted
    delay(200);
    updateDisplay();
  }

  if (totalCoins == 0.50) {
    if (digitalRead(button1) == LOW) {
      totalCoins = 0;
      lcd.clear();
      lcd.setCursor(6, 0);
      lcd.print("Coke");
      digitalWrite(pump_1, 1);
      delay(2000);
      digitalWrite(pump_1, 0);
      updateDisplay();
    }
    if (digitalRead(button2) == LOW) {
      totalCoins = 0;
      lcd.clear();
      lcd.setCursor(6, 0);
      lcd.print("Fanta");
      digitalWrite(pump_2, 1);
      delay(2000);
      digitalWrite(pump_2, 0);
      updateDisplay();
    }
    if (digitalRead(button3) == LOW) {
      totalCoins = 0;
      lcd.clear();
      lcd.setCursor(6, 0);
      lcd.print("Sprite");
      digitalWrite(pump_3, 1);
      delay(2000);
      digitalWrite(pump_3, 0);
      updateDisplay();
    }
  }

  if (totalCoins == 1.0) {
    if (digitalRead(button1) == LOW) {
      totalCoins = 0;
      lcd.clear();
      lcd.setCursor(6, 0);
      lcd.print("Coke");
      digitalWrite(pump_1, 1);
      delay(4000);
      digitalWrite(pump_1, 0);
      updateDisplay();
    }
    if (digitalRead(button2) == LOW) {
      totalCoins = 0;
      lcd.clear();
      lcd.setCursor(6, 0);
      lcd.print("Fanta");
      digitalWrite(pump_2, 1);
      delay(4000);
      digitalWrite(pump_2, 0);
      updateDisplay();
    }
    if (digitalRead(button3) == LOW) {
      totalCoins = 0;
      lcd.clear();
      lcd.setCursor(6, 0);
      lcd.print("Sprite");
      digitalWrite(pump_3, 1);
      delay(4000);
      digitalWrite(pump_3, 0);
      updateDisplay();
    }
  }

  if (totalCoins == 2.0) {
    if (digitalRead(button1) == LOW) {
      totalCoins = 0;
      lcd.clear();
      lcd.setCursor(6, 0);
      lcd.print("Coke");
      digitalWrite(pump_1, 1);
      delay(6000);
      digitalWrite(pump_1, 0);
      updateDisplay();
    }
    if (digitalRead(button2) == LOW) {
      totalCoins = 0;
      lcd.clear();
      lcd.setCursor(6, 0);
      lcd.print("Fanta");
      digitalWrite(pump_2, 1);
      delay(6000);
      digitalWrite(pump_2, 0);
      updateDisplay();
    }
    if (digitalRead(button3) == LOW) {
      totalCoins = 0;
      lcd.clear();
      lcd.setCursor(6, 0);
      lcd.print("Sprite");
      digitalWrite(pump_3, 1);
      delay(6000);
      digitalWrite(pump_3, 0);
      updateDisplay();
    }
  }
}

void updateDisplay() {
  lcd.clear();
  lcd.print("Total Coins:");
  lcd.print(totalCoins);
  lcd.setCursor(2, 1);
  lcd.print("Select drink");

}
