/*
 * PT6311.cpp
 *
 *  Created on: 9 окт. 2017 г.
 *      Author: snibler
 *
 */
#include <Arduino.h>
#include "PT6311.h"

//defining pins to witch MEGA connected
#define PT_CLK A6
#define PT_STB A5
#define PT_DATA A4

void PT6311::PT6311_init(){
	pinMode(PT_CLK, OUTPUT);
	pinMode(PT_STB, OUTPUT);
	pinMode(PT_DATA, OUTPUT);
	delay(200);
	PT6311::PT6311_writeCommand(WRITE_DATA_TO_DISPLAY);		//Command 2: Data Setting Commands
	PT6311::PT6311_writeCommand(ADDRESS_BOTTOM);			//Command 3: Address Setting Commands
	for(byte i = 0;i <= 0x2F;i++){
		PT6311::PT6311_writeData(0);						//Data 0x0
		}
	PT6311::PT6311_writeCommand(DISPLAY_MODE_15_13);		//Command 1: Display Mode Commands
	PT6311::PT6311_writeCommand(DISPLAY_ON_10_16);			//Command 4: Display Control Commands
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

byte PT6311::PT6311_read(){
	pinMode(PT_DATA, INPUT);
	delayMicroseconds(1);
	digitalWrite(PT_CLK, LOW);
		//437ns
			_NOP();
			_NOP();
			_NOP();
			_NOP();
			_NOP();
			_NOP();
			_NOP();
		for (byte count = 0; count < 8; count++)            //запись конфигурации
		   {
			if(digitalRead(PT_DATA)) PT6311::data |= 1;
			PT6311::data = PT6311::data<<1;
		    digitalWrite(PT_CLK,HIGH);
		    //437ns
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    digitalWrite(PT_CLK,LOW);
		    //437ns
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		   }
	return PT6311::data;
}

void PT6311::PT6311_write(byte data){
	pinMode(PT_DATA, OUTPUT);
	digitalWrite(PT_CLK, LOW);
	//437ns
		_NOP();
		_NOP();
		_NOP();
		_NOP();
		_NOP();
		_NOP();
		_NOP();
	for (byte count = 0; count < 8; count++)            //запись конфигурации
	   {
	    if( (data<<count)&0x80) digitalWrite(PT_DATA,HIGH);
	                       else digitalWrite(PT_DATA,LOW);
	    digitalWrite(PT_CLK,HIGH);
	    //437ns
	    	_NOP();
	    	_NOP();
	    	_NOP();
	    	_NOP();
	    	_NOP();
	    	_NOP();
	    	_NOP();
	    digitalWrite(PT_CLK,LOW);
	    //437ns
	    	_NOP();
	    	_NOP();
	    	_NOP();
	    	_NOP();
	    	_NOP();
	    	_NOP();
	    	_NOP();
	   }
}
