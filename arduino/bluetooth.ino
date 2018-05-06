#include <SoftwareSerial.h>
SoftwareSerial ss(A5, A4);

void bt_setup(){
  //Serial.begin(9600);
  ss.begin(9600);
}

void bt_loop() {
  if (ss.available()){
    char ch = ss.read();
    Serial.println("message");
    switch (ch){
      case 'a':
        Serial.println("lock_pc");
        //lock_pc();
        //start_pc_lock();
        break;
      case 'b':
        try_login();
        //lock_pc();
        //start_pc_lock();
        break;
    }
  }
}
