#include <Keypad.h>

#define KEY_PIN_1         2
#define KEY_PIN_2         3
#define KEY_PIN_3         4
#define KEY_PIN_4         5

const byte ROWS = 2; //four rows
const byte COLS = 2; //four columns
char keys[ROWS][COLS] = {
  {'3','1'},
  {'4','2'},
};

byte key_rowPins[ROWS] = {KEY_PIN_2, KEY_PIN_1}; //connect to the row pinouts of the keypad
byte key_colPins[COLS] = {KEY_PIN_4, KEY_PIN_3}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), key_rowPins, key_colPins, ROWS, COLS );

char pinCode[4] = {'2','1','3','2'};

char enteredCode[4] = {'0','0','0','0'};

int pin_iteration = 0;

void keypad_loop(){
  char key = keypad.getKey();
  if (key){
     if(pin_iteration == 0){
       Serial.println("PIN_ENTER_STARTED");
     }
     error_alert();
     enteredCode[pin_iteration] = key;
     Serial.println(key);
    
      if(pin_iteration == 3){
        for (int i = 0; i < 4; i++){
          if(enteredCode[i] != pinCode[i]){
              Serial.println("ERROR_PINCODE");
              bad_error_alert();
              pin_iteration = 0;
              return;
          }
        }
        
        Serial.println("PIN_IS_GOOD");
        try_login();
        success_alert();
        pin_iteration = 0;
        return;
      }  
    pin_iteration++;
  }
}
