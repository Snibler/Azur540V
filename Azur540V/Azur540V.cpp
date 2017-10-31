#include "PT6311.h"
//#include "LV23002M.h"

PT6311 disp;
//LV23002M radio;

void setup() {
// initialize digital pin LED_BUILTIN (13) as an output.
//	pinMode (LED_BUILTIN, OUTPUT);
//	pinMode(2, OUTPUT);
//init serial for debugging
	Serial.begin(9600, SERIAL_8N1);
//init display
	disp.PT6311_init();
	disp.Write_Display();
//	delay(1000);
//	disp.Display_OFF();
}

void loop() {
/*
	  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
	  delay(1000);                       // wait for a second
	  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
	  delay(1000);                       // wait for a second
*/
//	  disp.Disk_Demo();
//print key status
	  disp.PT6311_read();
	  Serial.println(disp.data);
	  delay(500);
}
