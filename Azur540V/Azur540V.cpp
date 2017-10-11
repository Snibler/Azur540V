#include <Arduino.h>
#include <SPI.h>
#include "PT6311.h"
//#include "LV23002M.h"
//#include <SoftwareSerial.cpp>
//#include <SPI.cpp>

PT6311 disp;

void setup() {
	// initialize digital pin LED_BUILTIN (13) as an output.
	pinMode (LED_BUILTIN, OUTPUT);
	//init serial for debugging
	//Serial.begin(9600);
	disp.PT6311_init();
}

void loop() {
	  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
	  delay(1000);                       // wait for a second
	  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
	  delay(1000);                       // wait for a second

	  disp.PT6311_writeCommand(WRITE_DATA_TO_DISPLAY);		//Command 2: Data Setting Commands
	  disp.PT6311_writeCommand(ADDRESS_BOTTOM);				//Command 3: Address Setting Commands
	  		for(byte i = 0;i <= 0x2F;i++){
	  			disp.PT6311_writeData(i);					//Data
	  		}
	  disp.PT6311_writeCommand(DISPLAY_MODE_15_13);			//Command 1: Display Mode Commands
	  disp.PT6311_writeCommand(DISPLAY_ON_10_16);			//Command 4: Display Control Commands
}
