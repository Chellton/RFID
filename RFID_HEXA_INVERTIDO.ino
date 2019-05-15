
#include <SPI.h>
#include <MFRC522.h>
#include <stdlib.h>


#define RST_PIN         9
#define SS_PIN          10

String inStringDec = "";
String inStringHex = "";
String inStringHexRev = "";

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
  Serial.begin(9600);   // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop() {
  // Look for new cards
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial())
  {
    Serial.print(mfrc522.uid.uidByte[2], HEX);
    Serial.print(mfrc522.uid.uidByte[1], HEX);
    Serial.print(mfrc522.uid.uidByte[0], HEX);
    inStringHex += String(mfrc522.uid.uidByte[2], HEX);
    inStringHex += String(mfrc522.uid.uidByte[1], HEX);
    inStringHex += String(mfrc522.uid.uidByte[0], HEX);
    inStringHexRev += String(mfrc522.uid.uidByte[mfrc522.uid.size - (2 + 1)], HEX);
    inStringHexRev += String(mfrc522.uid.uidByte[mfrc522.uid.size - (1 + 1)], HEX);
    inStringHexRev += String(mfrc522.uid.uidByte[mfrc522.uid.size - (0 + 1)], HEX);
    delay(500);
    Serial.println();
    String WorkingStringA = inStringHex;
    long unsigned A = strtol(WorkingStringA.c_str(), NULL, 16);
    // Serial.println();
    WorkingStringA = String(A);


    inStringHex = "";
    inStringHexRev = "";

    Serial.print("CODIGO DE ID:" );
    Serial.print(WorkingStringA);
    Serial.println();
  }



}
