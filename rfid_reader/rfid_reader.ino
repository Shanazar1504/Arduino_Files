#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN    D3    // Reset pin
#define SS_PIN     D8    // Slave Select pin

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create instance of the MFRC522 RFID reader

void setup() {
  Serial.begin(9600);
  SPI.begin();       // Initialize SPI communication
  mfrc522.PCD_Init();   // Initialize MFRC522

  Serial.println("Ready to read RFID card...");
}

void loop() {
  // Check if a new card is present
  if (mfrc522.PICC_IsNewCardPresent()) {
    // Select the RFID card
    if (mfrc522.PICC_ReadCardSerial()) {
      // Dump the card details
      dumpCardDetails();
      mfrc522.PICC_HaltA();    // Halt the card
    }
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

  // Get the card type
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  String cardType = mfrc522.PICC_GetTypeName(piccType);

  Serial.print("Card Type: ");
  Serial.println(cardType);
  Serial.println();
}
