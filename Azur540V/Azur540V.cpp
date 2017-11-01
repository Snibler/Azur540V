#include "PT6311.h"
#include "LV23002M.h"

PT6311 disp;
LV23002M radio;

void setup() {
	SPI.begin();
	SPI.beginTransaction(SPISettings(500000, MSBFIRST, SPI_MODE0));
// initialize digital pin LED_BUILTIN (13) as an output.
//	pinMode (LED_BUILTIN, OUTPUT);
//init serial for debugging
	Serial.begin(9600);
//init display
	disp.PT6311_init();
	disp.Write_Display();
//	delay(1000);
//	disp.Display_OFF();
	radio.LV23002M_INmode(IN1mode,0xFF,0xFF,0xE0);
	radio.LV23002M_INmode(IN2mode,0x43,0x00,0x08);
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
//	  disp.PT6311_read();
//	  Serial.println(disp.data);
//	  delay(500);
//	radio.LV23002M_INmode(IN1mode,0xFF,0xFF,0xE0);
//	radio.LV23002M_INmode(IN2mode,0x43,0x00,0x08);
//	delay(1000);
	for(unsigned int i = 272; i <= 65535; i=i+10){
		radio.LV23002M_INmode(IN1mode,highByte(i),lowByte(i),0xE0);
		Serial.println(i);
		delay(100);
	}
	radio.LV23002M_OUTmode();
	delay(1000);
	Serial.println(radio.OUTdata1);
	Serial.println(radio.OUTdata2);
	Serial.println(radio.OUTdata3);
}
