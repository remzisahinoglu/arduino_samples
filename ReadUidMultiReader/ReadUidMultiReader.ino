/**
 * ----------------------------------------------------------------------------
 * This is a MFRC522 library example; see https://github.com/miguelbalboa/rfid
 * for further details and other examples.
 *
 * NOTE: The library file MFRC522.h has a lot of useful info. Please read it.
 *
 * Released into the public domain.
 * ----------------------------------------------------------------------------
 * This sample shows how to read and write data blocks on a MIFARE Classic PICC
 * (= card/tag).
 *
 * BEWARE: Data will be written to the PICC, in sector #1 (blocks #4 to #7).
 *
 *
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno           Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS 1    SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 *
 *
 *            rfid okuyucu kartın 3.3v beslemesi arduino micronun vcc pinine bağlanabilir
 */

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN        9           // Configurable, see typical pin layout above
#define SS_1_PIN        10          // Configurable, see typical pin layout above
#define SS_2_PIN        3          // Configurable, see typical pin layout above

#define NR_OF_READERS   2

byte ssPins[] = {SS_1_PIN, SS_2_PIN};

String mycardid = "66150172213";       // benim rfidcard ın idsi
String readcardid = "";      // okunan rfidcard idsi

MFRC522 mfrc522[NR_OF_READERS];   // Create MFRC522 instance.

/**
 * Initialize.
 */
void setup() {

  Serial.begin(115200); // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)

  SPI.begin();        // Init SPI bus

  Keyboard.begin();
    
  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN); // Init each MFRC522 card
  }
}

/**
 * Main loop.
 */
void loop() {
  delay(1);
  
    for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    // Look for new cards

    if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) {
      dump_byte_array(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size);
      
      // Halt PICC
      mfrc522[reader].PICC_HaltA();
      // Stop encryption on PCD
      mfrc522[reader].PCD_StopCrypto1();
    } //if (mfrc522[reader].PICC_IsNewC
  } //for(uint8_t reader

  if(readcardid == mycardid){
    readcardid = "";
    Serial.println("ok");
    Serial.flush();
    //Keyboard.write(0xB1);   // ekranın açılması için ESC tuşu
    //delay(200);
    Keyboard.println("Qa2015!mdfk");        // şifreyi buraya yaz

  }
}

/**
 * Helper routine to dump a byte array as hex values to Serial.
 */
void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    //Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    //Serial.print(buffer[i], HEX);
    //Serial.print(buffer[i]);

    readcardid += buffer[i];
  }
}
