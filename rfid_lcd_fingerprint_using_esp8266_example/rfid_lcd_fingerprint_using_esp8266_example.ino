#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MFRC522.h>
#include <Adafruit_Fingerprint.h>
#include <SPI.h>


#define SS_PIN D8
#define RST_PIN D3
MFRC522 rfid(SS_PIN, RST_PIN);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial);

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD address and size (change based on your display)

void setup() {
  Serial.begin(9600);
  lcd.begin();  // Initialize the LCD

  SPI.begin();  // Initialize SPI communication for the RFID module
  rfid.PCD_Init();  // Initialize the RFID module

  finger.begin(9600);  // Initialize fingerprint sensor
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor.");
  }

  lcd.clear();
  lcd.print("Ready to Use!");
}

void loop() {
  // Read RFID tags
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    lcd.clear();
    lcd.print("RFID Tag ID:");
    for (byte i = 0; i < rfid.uid.size; i++) {
      lcd.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
      lcd.print(rfid.uid.uidByte[i], HEX);
    }
    delay(2000);
    lcd.clear();
    lcd.print("Ready to Use!");
    rfid.PICC_HaltA();
  }

  // Scan fingerprints
  if (finger.getImage()) {
    int fingerprintID = finger.fingerFastSearch();
    if (fingerprintID >= 0) {
      lcd.clear();
      lcd.print("Fingerprint ID:");
      lcd.print(fingerprintID);
      delay(2000);
      lcd.clear();
      lcd.print("Ready to Use!");
    } else {
      lcd.clear();
      lcd.print("Fingerprint not found!");
      delay(2000);
      lcd.clear();
      lcd.print("Ready to Use!");
    }
  }
}
