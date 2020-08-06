#include <Arduino.h>
#include <TM1637Display.h>
#include <Keypad.h>
#include <MIDI.h>


#define MIDI_CHANNEL 0
#define DISP_CLK 2
#define DISP_DIO 3

const byte ROWS = 4; 
const byte COLS = 3; 

char hexaKeys[ROWS][COLS] = {
{'1', '2', '3'},
{'4', '5', '6'},
{'7', '8', '9'},
{'*', '0', '#'}
};

byte rowPins[ROWS] = {12,11, 10, 9}; 
byte colPins[COLS] = {8, 7, 6}; 

uint8_t ledPins[] = {22, 23, 24, 25, 26, 27, 28, 29, 30, 31};

uint8_t pChangeChan = 0xC0; // PC channel 0-F 0-16 1-16
uint8_t contChange = 0xB0; // CC Midi command
uint8_t contNum = 11; // CC# for expression on/off
uint8_t contOn = 127; // CC# value for FX on (64-127 on)
uint8_t contOff = 0; // CC# value for FX off (0-63 off)
uint8_t curbank = 0;
uint8_t sentpreset = 30; //initial value
uint8_t sentbank = 0;

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
TM1637Display display = TM1637Display(DISP_CLK, DISP_DIO);

const uint8_t DASH[] = {
    SEG_G,         // -
    SEG_G          // -
  };
const uint8_t UP[] = {
    SEG_C | SEG_D | SEG_E,         // -
    SEG_C | SEG_D | SEG_E        // -
  };
const uint8_t DOWN[] = {
    SEG_A | SEG_B | SEG_F,         // -
    SEG_A | SEG_B | SEG_F          // -
  };
const uint8_t SEG_INIT[] = {
    SEG_B | SEG_C,                                   // I
    SEG_C | SEG_E | SEG_G,                           // n
    SEG_B | SEG_C,                                   // I
    SEG_D | SEG_E | SEG_F | SEG_G            // t
  };

void effectOn(uint8_t pos){
  //Serial.println("START ON");
  Serial.write(pChangeChan + MIDI_CHANNEL);
  Serial.write(pos);
  //Serial.write(contChange);
  //Serial.write(contNum);
  //Serial.write(contOn);
  //Serial.println("END ON\n\n\n");
  delay(10);
}
void effectOff(uint8_t pos){
  Serial.write(pChangeChan + MIDI_CHANNEL);
  Serial.write(pos);
  Serial.write(contChange);
  Serial.write(contNum);
  Serial.write(contOff);
  delay(10);
}
void ledOn(uint8_t led_pin){
  digitalWrite(ledPins[led_pin],HIGH);
}
void ledOff(uint8_t led_pin){
  digitalWrite(ledPins[led_pin],LOW);
}
void ledsOn(){
  for(uint i = 0; i<10; i++){
    digitalWrite(ledPins[i],HIGH);
  }
}
void ledsOff(){
  for(uint i = 0; i<10; i++){
    digitalWrite(ledPins[i],LOW);
  }
}

void setup(){
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  delay(3000);
  for (int i = 0; i < 10; i++) pinMode(ledPins[i], OUTPUT);
  display.setBrightness(7);
  display.setSegments(SEG_INIT);
  delay(2000);
  display.clear();
  for(uint i = 0; i<10; i++){
    pinMode(ledPins[i],OUTPUT);
    digitalWrite(ledPins[i],LOW);
  }
  for(uint i=0; i<3; i++){
    ledsOn();
    delay(100);
    ledsOff();
  }
  
}

void loop(){
  if(sentpreset == 30){ //initial condition
    display.showNumberDec(curbank, true, 2, 0);  // Expect: 04__
    display.setSegments(DASH,2,2);
  } else{
    if(sentbank < curbank){
      display.showNumberDec(curbank, true, 2, 0);  // Expect: 04^^
      display.setSegments(UP,2,2);
    }else if(sentbank > curbank){
      display.showNumberDec(curbank, true, 2, 0);  // Expect: 04vv
      display.setSegments(DOWN,2,2);
    }else{
      display.showNumberDecEx(((curbank*100) + sentpreset),0x40,true);
    }
  }
	char customKey = customKeypad.waitForKey();
  //for (int i = 0; i < 10; i++) digitalWrite(ledPins[i], LOW);
	switch(customKey){
		case '0':{
			Serial.print("Bank ");
			Serial.print(curbank);
			Serial.print(" ,0 ON\n");
			//effectOn((curbank*10));
      ledsOff();
      ledOn(0);
      sentbank = curbank;
      sentpreset = 0;
		  break;
		}
		
		case '1':{
		  Serial.print("Bank ");
      Serial.print(curbank);
      Serial.print(" ,1 ON\n");
      //effectOn((curbank*10));
      ledsOff();
      ledOn(1);
      sentbank = curbank;
      sentpreset = 1;
		  break;
		}
		case '2':{
      Serial.print("Bank ");
      Serial.print(curbank);
      Serial.print(" ,2 ON\n");
      //effectOn((curbank*10));
      ledsOff();
      ledOn(2);
      sentbank = curbank;
      sentpreset = 2;
		  break;
		}
		case '3':{
      Serial.print("Bank ");
      Serial.print(curbank);
      Serial.print(" ,3 ON\n");
      //effectOn((curbank*10));
      ledsOff();
      ledOn(3);
      sentbank = curbank;
      sentpreset = 3;
			break;
		}
		case '4':{
      Serial.print("Bank ");
      Serial.print(curbank);
      Serial.print(" ,4 ON\n");
      //effectOn((curbank*10));
      ledsOff();
      ledOn(4);
      sentbank = curbank;
      sentpreset = 4;
			break;
		}
		case '5':{
      Serial.print("Bank ");
      Serial.print(curbank);
      Serial.print(" ,5 ON\n");
      //effectOn((curbank*10));
      ledsOff();
      ledOn(5);
      sentbank = curbank;
      sentpreset = 5;
			break;
		}

		case '6':{
      Serial.print("Bank ");
      Serial.print(curbank);
      Serial.print(" ,6 ON\n");
      //effectOn((curbank*10));
      ledsOff();
      ledOn(6);
      sentbank = curbank;
      sentpreset = 6;
			break;
		}
		case '7':{
      Serial.print("Bank ");
      Serial.print(curbank);
      Serial.print(" ,7 ON\n");
      //effectOn((curbank*10));
      ledsOff();
      ledOn(7);
      sentbank = curbank;
      sentpreset = 7;
			break;
		}
		case '8':{
			if(!(curbank==12)){     
			  Serial.print("Bank ");
        Serial.print(curbank);
        Serial.print(" ,8 ON\n");
        ledsOff();
        ledOn(8);
        //effectOn((curbank*10));
        sentbank = curbank;
        sentpreset = 8;
			}
			break;
		}
		case '9':{
			if(!(curbank==12)){
  			Serial.print("Bank ");
        Serial.print(curbank);
        Serial.print(" ,9 ON\n");
        ledsOff();
        ledOn(9);
        //effectOn((curbank*10));
        sentbank = curbank;
        sentpreset = 9;
			}
			break;
		}
		case '*':{
			//Serial.println("bank up");
			if(curbank<12){
				curbank++;
			}else{
        curbank = 0;
			}
			break;
		}    
		case '#':{
			//Serial.println("bank down");
			if(curbank>0){
				curbank--;
			}else{
        curbank = 12;
			}
			break;
		}
		default:{
		//Serial.println("error");
		//delay(1000);
		}
	}

}
