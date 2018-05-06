

void setup(){
   Serial.begin(9600);
   misc_setup();
   rfid_setup();
   bt_setup();
}


void loop(){
	rfid_loop();
	keypad_loop();
	bt_loop();

}
