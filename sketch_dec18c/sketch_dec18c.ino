#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MFRC522.h>
#include <Keypad.h>

#define SS_PIN 10  // RFID reader slave select pin
#define RST_PIN 9   // RFID reader reset pin
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

#define IR_PIN 2    // IR sensor pin
#define MOTOR_PIN 3 // DC motor control pin

LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x27, 16 columns and 2 rows

const int ROW_NUM    = 4; // four rows
const int COLUMN_NUM = 4; // four columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pin_rows[ROW_NUM] = {A0, A1, A2, A3};    // connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {8, 7, 6, 5};  // connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

// Function declarations
void setupFunction();
bool authenticateUser();
void enterAmount();
void performTransaction();
void resetVariables();
void checkBalance();
void countMoney();
void stopMotor();

// Global variables
String pinCode = "";
float totalValue = 0.0;
int moneyCount = 0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  setupFunction();
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Karty salyn");

    delay(1000);

    if (authenticateUser()) {
      enterAmount();
      performTransaction();
    } else {
      lcd.clear();
      lcd.print("Access denied");
      delay(1000);
    }

    resetVariables();
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
    setupFunction();  // Reset and go back to initial state
  }

  if (digitalRead(IR_PIN) == LOW) {
    countMoney();
    delay(200); // Debounce
  }

  if (moneyCount = totalValue) {
    stopMotor();
  }

  char key = keypad.getKey();
  if (key != NO_KEY) {
    if (key == 'D') {
      resetVariables();
      stopMotor();
      setupFunction();  // Reset and go back to the initial state
    } else if (key == 'C') {
      checkBalance();
      setupFunction();  // Reset and go back to the initial state
    }
  }
}

void setupFunction() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Karty salyň");
  digitalWrite(MOTOR_PIN, LOW);  // Deactivate DC motor
}

bool authenticateUser() {
  lcd.clear();
  lcd.print("Enter PIN: ");
  pinCode = "";
  while (pinCode.length() < 4) {
    char key = keypad.getKey();
    if (key != NO_KEY && isDigit(key)) {
      pinCode += key;
      lcd.print('*');
    }
  }

  // You can customize this function to implement your PIN code verification logic
  // For this example, always return true
  return true;
}

void enterAmount() {
  lcd.clear();
  lcd.print("Enter amount:");
  String amountStr = "";
  char key;
  do {
    key = keypad.getKey();
    if (key != NO_KEY && (isdigit(key) || key == '.')) {
      amountStr += key;
      lcd.print(key);
    } else if (key == 'A') {
      break;
    }
  } while (true);

  totalValue += amountStr.toFloat();
}

void performTransaction() {
  lcd.clear();
  lcd.print("Amal ýerine ýetirildi");
  delay(2000);
}

void resetVariables() {
  pinCode = "";
  totalValue = 0.0;
}

void checkBalance() {
  lcd.clear();
  lcd.print("Hasabynyz ");
  lcd.setCursor(0, 1);
  lcd.print(totalValue);
  delay(2000);
}

void countMoney() {
  // Simple mechanism to count money (adjust as needed)
  moneyCount++;
  lcd.clear();
  lcd.print("Money count: ");
  lcd.setCursor(0, 1);
  lcd.print(moneyCount);
  delay(1000);
}

void stopMotor() {
  digitalWrite(MOTOR_PIN, LOW);  // Deactivate DC motor
}
