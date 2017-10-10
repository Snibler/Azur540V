#include <Arduino.h>
#include <SPI.h>
#include "PT6311.h"
//#include "LV23002M.h"
//#include <SoftwareSerial.cpp>
//#include <SPI.cpp>

void setup() {
	// initialize digital pin LED_BUILTIN (13) as an output.
	pinMode (LED_BUILTIN, OUTPUT);
}

void loop() {
	  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
	  delay(1000);                       // wait for a second
	  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
	  delay(1000);                       // wait for a second
}
