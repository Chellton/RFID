#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
// Definicoes pino modulo RC522
MFRC522 mfrc522(SS_PIN, RST_PIN);
unsigned long  Total = 0;                             // Variavel para guardar valores totois lidos
byte Etiqueta[4];                                     // Matriz para guardar bytes individuais.
//-----------------------------
void setup()
{
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
}
//----------------------
void loop()
{
  if ( ! mfrc522.PICC_IsNewCardPresent()) return;
  if ( ! mfrc522.PICC_ReadCardSerial())   return;
  for (byte i = 0; i < mfrc522.uid.size; i++)             // Le qtde de bytes identificados
  {
    Etiqueta[i] = mfrc522.uid.uidByte[i];                 // Le o byte 
    Total = (Total << 8) + Etiqueta[i];                   // Desloca um byte a esquerda e soma 
  }
  Serial.println();

  Serial.print(Total);                                    // Imprime valor em decimal 

  delay(1000);
}
