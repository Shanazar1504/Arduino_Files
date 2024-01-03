#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MFRC522.h>
#include <SPI.h>

#define RST_PIN         1          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int motor = 5;

void setup() {
  Serial.begin(9600);  // Initialize serial communications
  SPI.begin();         // Init SPI bus
  mfrc522.PCD_Init();  // Init MFRC522 card
  lcd.init();         // Initialize the I2C LCD
  lcd.backlight();     // Turn on the backlight

  pinMode(motor, OUTPUT);
  digitalWrite(motor, 0);
  Serial.println("RFID & LCD Initialized");
}

void loop() {
  getRFID();
}

void getRFID() {
  // Check if a new card is present
  if (mfrc522.PICC_IsNewCardPresent()) {
    // Select the RFID card
    if (mfrc522.PICC_ReadCardSerial()) {
      // Dump the card details
      dumpCardDetails();
      mfrc522.PICC_HaltA();    // Halt the card
    }
  } else {
    lcd.setCursor(2, 0);
      lcd.print("Karty");
      lcd.setCursor(6, 1);
      lcd.print("degirin");
  }
}

void dumpCardDetails() {

  // Get the card UID
  String cardUid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    cardUid.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
    cardUid.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  Serial.print("Card UID: ");
  Serial.println(cardUid);

  if (cardUid == "53510b80") {
    Serial.println("ok");
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print(" Ustunlikli!!!");
    digitalWrite(motor, 1);
    delay(500);
    digitalWrite(motor, 0);
        lcd.clear();
  }
}
