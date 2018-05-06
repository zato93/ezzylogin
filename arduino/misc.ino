

#define OUT_PIN_GREEN   7
#define OUT_PIN_RED     6
#define BUZZER 8


void misc_setup(){
  pinMode (OUT_PIN_GREEN, OUTPUT);
  pinMode (OUT_PIN_RED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
}

void error_alert(){
  digitalWrite (OUT_PIN_RED, HIGH);
  tone(BUZZER, 2000);  // 2KHz sound signal...
  delay (200);
  noTone(BUZZER);     // Stop sound...
  digitalWrite (OUT_PIN_RED, LOW);
}


void bad_error_alert(){
  digitalWrite (OUT_PIN_RED, HIGH);
  tone(BUZZER, 1000);  // 2KHz sound signal...
  delay (800);
  noTone(BUZZER);     // Stop sound...
  digitalWrite (OUT_PIN_RED, LOW);
}


void success_alert(){
  digitalWrite (OUT_PIN_GREEN, HIGH);
  
  tone(BUZZER, 6000); // 2KHz sound signal...
  delay (200);
  noTone(BUZZER);     // Stop sound...
  delay (200);
  
  tone(BUZZER, 2000); // 2KHz sound signal...
  delay (200);
  noTone(BUZZER);     // Stop sound...
  delay (200);
  
  tone(BUZZER, 6000); // 2KHz sound signal...
  delay (200);
  noTone(BUZZER);     // Stop sound...
  
  digitalWrite (OUT_PIN_GREEN, LOW);
}

void start_pc_lock(){
  for(int i = 0; i<3; i++){
    error_alert();
    delay(1000);
  }
  
   bad_error_alert();
   lock_pc();
}

void lock_pc(){
//rundll32.exe user32.dll, LockWorkStation
  Serial.println("lock_pc");
}

byte a_correctCard[4] = {0x24, 0x0B, 0x70, 0x8B};
void try_login(){
  dump_byte_array(a_correctCard, 4);
}


uint32_t id;
 void dump_byte_array(byte *buffer, byte bufferSize) {
  Serial.print(F(">ID:"));
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
  Serial.println();
  Serial.println(id);
  
     //mfrc522.PICC_HaltA();
     //mfrc522.PCD_StopCrypto1();
}
