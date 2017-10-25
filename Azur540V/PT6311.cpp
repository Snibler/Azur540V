/*
 * PT6311.cpp
 *
 *  Created on: 9 окт. 2017 г.
 *      Author: snibler
 *
 */
#include "PT6311.h"

unsigned int Digits[10] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};

PT6311::PT6311(){
	data = 0;
	pinMode(PT_CLK, OUTPUT);
	pinMode(PT_STB, OUTPUT);
	pinMode(PT_DATA, OUTPUT);
	digitalWrite(PT_STB, HIGH);
	digitalWrite(PT_CLK, HIGH);
	digitalWrite(PT_DATA, HIGH);
}
void PT6311::Test_display(){
		PT6311::PT6311_writeCommand(WRITE_DATA_TO_DISPLAY);

		PT6311::PT6311_writeCommand(ADDRESS_BOTTOM|0x06);
				PT6311::PT6311_writeData((Digits[0]>>8) & 0xFF);
		PT6311::PT6311_writeCommand(ADDRESS_BOTTOM|0x07);
				PT6311::PT6311_writeData(Digits[0] & 0xFF);

		PT6311::PT6311_writeCommand(DISPLAY_MODE_9_19);
		PT6311::PT6311_writeCommand(DISPLAY_ON_14_16);
		digitalWrite(PT_STB, HIGH);
}
void PT6311::Display_OFF(){
		PT6311::PT6311_writeCommand(DISPLAY_OFF);
		digitalWrite(PT_STB, HIGH);
}
void PT6311::PT6311_init(){
	delay(200);
	PT6311::PT6311_writeCommand(WRITE_DATA_TO_DISPLAY);	//Command 2: Data Setting Commands
	PT6311::PT6311_writeCommand(ADDRESS_BOTTOM);		//Command 3: Address Setting Commands
	for(byte i = 0x00;i <= 0x19;i++){
		PT6311::PT6311_writeData(0x00);					//Data 0x00
		}
	PT6311::PT6311_writeCommand(DISPLAY_MODE_9_19);		//Command 1: Display Mode Commands
	PT6311::PT6311_writeCommand(DISPLAY_ON_14_16);		//Command 4: Display Control Commands
	digitalWrite(PT_STB, HIGH);
}

void PT6311::PT6311_writeCommand(byte command){
	digitalWrite(PT_STB, HIGH);
	delayMicroseconds(1);
	digitalWrite(PT_STB, LOW);
	PT6311::PT6311_write(command);
}

void PT6311::PT6311_writeData(byte data){
	PT6311::PT6311_write(data);
}

void PT6311::PT6311_read(){
	pinMode(PT_DATA, INPUT);
	delayMicroseconds(1);
		for (byte count = 0; count < 8; count++)
		   {
			if(digitalRead(PT_DATA)) PT6311::data |= 1;
			PT6311::data = PT6311::data<<1;
		    digitalWrite(PT_CLK, LOW);
			digitalWrite(PT_CLK, HIGH);
		   }
}

void PT6311::PT6311_write(byte data){
	pinMode(PT_DATA, OUTPUT);
	for (byte count = 0; count < 8; count++)
	   {
	    if( (data>>count)&0x01) digitalWrite(PT_DATA,HIGH);
	                       else digitalWrite(PT_DATA,LOW);
	   digitalWrite(PT_CLK, LOW);
	   digitalWrite(PT_CLK, HIGH);
	   }
}

//437ns
//	_NOP();
//	_NOP();
//	_NOP();
//	_NOP();
//	_NOP();
//	_NOP();
//	_NOP();
