/*
 * PT6311.cpp
 *
 *  Created on: 9 окт. 2017 г.
 *      Author: snibler
 *
 */
#include "PT6311.h"

unsigned int Digits[10] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
unsigned int Disk[10] = {DISK1, DISK2, DISK3, DISK4, DISK5, DISK6, DISK7, DISK8, DISK9, DISK10};

PT6311::PT6311(){
	data = 0;
	pinMode(PT_CLK, OUTPUT);
	pinMode(PT_STB, OUTPUT);
	pinMode(PT_DATA, OUTPUT);
	digitalWrite(PT_STB, HIGH);
	digitalWrite(PT_CLK, HIGH);
	digitalWrite(PT_DATA, HIGH);

}
void PT6311::Disk_Demo(){
	for (byte i = 0; i < 10; i++){
		PT6311::PT6311_writeCommand(ADDRESS_BOTTOM|0x18);
					PT6311::PT6311_writeData(~((Disk[i]>>8) & 0xFF) | DVD);
				PT6311::PT6311_writeCommand(ADDRESS_BOTTOM|0x19);
					PT6311::PT6311_writeData(~(Disk[i] & 0xFF) | MHz | kHz | MEM | _3D);
		delay(100);
	}
}
void PT6311::Write_Display(){
		PT6311::PT6311_writeCommand(WRITE_DATA_TO_DISPLAY);
//Digit 1
		PT6311::PT6311_writeCommand(ADDRESS1);
				PT6311::PT6311_writeData(((ZERO>>8) & 0xFF) | dts);
			PT6311::PT6311_writeCommand(ADDRESS1 + 1);
				PT6311::PT6311_writeData(ZERO & 0xFF);
//Digit 2
		PT6311::PT6311_writeCommand(ADDRESS2);
				PT6311::PT6311_writeData(((ZERO>>8) & 0xFF) | RDS);
			PT6311::PT6311_writeCommand(ADDRESS2 + 1);
				PT6311::PT6311_writeData(ZERO & 0xFF);
//Digit 3
		PT6311::PT6311_writeCommand(ADDRESS3);
				PT6311::PT6311_writeData(((ZERO>>8) & 0xFF) | _2dp);
			PT6311::PT6311_writeCommand(ADDRESS3 + 1);
				PT6311::PT6311_writeData((ZERO & 0xFF));		// | dp
//Digit 4
		PT6311::PT6311_writeCommand(ADDRESS4);
				PT6311::PT6311_writeData(((SIX>>8) & 0xFF) | ST);
			PT6311::PT6311_writeCommand(ADDRESS4 + 1);
				PT6311::PT6311_writeData((SIX & 0xFF) | DOLBY);
//Digit 5
		PT6311::PT6311_writeCommand(ADDRESS5);
				PT6311::PT6311_writeData(((THREE>>8) & 0xFF)| _2dp);
			PT6311::PT6311_writeCommand(ADDRESS5 + 1);
				PT6311::PT6311_writeData((THREE & 0xFF));		// | dp
//Digit 6
		PT6311::PT6311_writeCommand(ADDRESS6);
				PT6311::PT6311_writeData(((ZERO>>8) & 0xFF) | TUNED);
			PT6311::PT6311_writeCommand(ADDRESS6 + 1);
				PT6311::PT6311_writeData((ZERO & 0xFF) | two_coils);
//Digit 7
		PT6311::PT6311_writeCommand(ADDRESS7);
				PT6311::PT6311_writeData(((ONE>>8) & 0xFF));
			PT6311::PT6311_writeCommand(ADDRESS7 + 1);
				PT6311::PT6311_writeData(ONE & 0xFF);
//Digit 8
		PT6311::PT6311_writeCommand(ADDRESS8);
				PT6311::PT6311_writeData(PLAY);
			PT6311::PT6311_writeCommand(ADDRESS8 + 1);
				PT6311::PT6311_writeData(FM | AM | ALL);
//Digit 9
		PT6311::PT6311_writeCommand(ADDRESS9);
				PT6311::PT6311_writeData(((DISK_FULL>>8) & 0xFF) | DVD);
			PT6311::PT6311_writeCommand(ADDRESS9 + 1);
				PT6311::PT6311_writeData((DISK_FULL & 0xFF) | MHz | kHz | MEM | _3D);


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
	PT6311::PT6311_writeByte(command);
}

void PT6311::PT6311_writeData(byte data){
	PT6311::PT6311_writeByte(data);
}

void PT6311::PT6311_read(){
	PT6311::PT6311_writeCommand(READ_KEY);
	pinMode(PT_DATA, INPUT);
	delayMicroseconds(1);
		for (byte count = 0; count < 8; count++)
		   {
			if(digitalRead(PT_DATA)) data |= 1;
			data = data<<1;
		    digitalWrite(PT_CLK, LOW);
			digitalWrite(PT_CLK, HIGH);
		   }

	digitalWrite(PT_STB, HIGH);
}

void PT6311::PT6311_writeByte(byte data){
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
