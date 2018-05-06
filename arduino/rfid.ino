#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_1_PIN        10         // Configurable, take a unused pin, only HIGH/LOW required, must be diffrent to SS 2


MFRC522 mfrc522;   // Create MFRC522 instance.

bool cardWasPresent = false;

void rfid_setup() {
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();        // Init SPI bus
  mfrc522.PCD_Init(SS_1_PIN, RST_PIN); // Init each MFRC522 card
}

byte correctCard[4] = {0x24, 0x0B, 0x70, 0x8B};

const int n = 4;
uint8_t counter[n] = {0, 0, 0, 0};
int index = 0;
bool  correct_card_inserted =false;
void rfid_loop() {
  //uint8_t x;
  uint8_t y;
  mfrc522.PICC_IsNewCardPresent();
  y = mfrc522.PICC_ReadCardSerial();
  counter[index % n] = y;
  index++;
  uint8_t sum = 0;
  for (uint8_t i = 0; i < n; i++)
    sum += counter[i];
  if (sum > 0){
    if (!cardWasPresent){
      Serial.print("card has been inserted");
      bool correct = true;
      for (uint8_t i = 0; i < 4; i++){
        if (correctCard[i] != mfrc522.uid.uidByte[i])
          correct = false;
      }
      if (correct){
        Serial.println(", correct card");
        Serial.println("2"); // unblock pc
        success_alert();
        try_login();
        correct_card_inserted = true;
        //Serial.print(mfrc522.uid.size);
        //dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
        
      }
      else {
        Serial.println(", incorrect card");
        correct_card_inserted = false;
        Serial.println("3"); // do not unblock pc
        error_alert();
      }
    }
    cardWasPresent = true;
  }
  else {
    if (cardWasPresent){
      Serial.println("card has been removed");
      Serial.println("1");
      if(correct_card_inserted){
        start_pc_lock();
        correct_card_inserted = false;
     }
      error_alert();
    }
    cardWasPresent = false;
    //Serial.println("card is not present");
  }


      //mfrc522.PICC_HaltA();
      //mfrc522.PCD_StopCrypto1();
  delay(20);
}
