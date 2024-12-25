#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9  // Configurable, check your RFID module's setup
#define SS_PIN 10

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);  // Initialize serial communication with computer
  SPI.begin();         // Init SPI bus
  mfrc522.PCD_Init();  // Init RFID module
}

void loop() {
  // Check if a new card is present
  if (!mfrc522.PICC_IsNewCardPresent()) return;

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) return;

  // Print the UID of the card
  String cardID = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    cardID += String(mfrc522.uid.uidByte[i], HEX);
  }

  Serial.println(cardID);  // Send card ID via Serial
  delay(1000);             // Small delay
}
