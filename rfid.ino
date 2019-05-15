
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
    //Serial.print("Card UID:");
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      inStringHex += String(mfrc522.uid.uidByte[i], HEX);
      inStringHexRev += String(mfrc522.uid.uidByte[mfrc522.uid.size - (i + 1)], HEX);
    }

    String WorkingStringA = inStringHex;
    long unsigned A = strtol(WorkingStringA.c_str(),NULL,16);
    Serial.println();
    Serial.println(F("long unsigned A:"));
    Serial.print(A);
    WorkingStringA = String(A);
  
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      Serial.print(mfrc522.uid.uidByte[i], DEC);
      Serial.print(F(" "));

    }

    inStringHex = "";
    inStringHexRev = "";
    Serial.println();
    Serial.print(WorkingStringA);


    delay(500);
  }
}
