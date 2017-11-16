/*
 * PT6311.cpp
 *
 *  Created on: 9 окт. 2017 г.
 *      Author: snibler
 *
 */
#include "PT6311.h"

word converter(char symbol);

unsigned int Disk[10] = {DISK1, DISK2, DISK3, DISK4, DISK5, DISK6, DISK7, DISK8, DISK9, DISK10};

PT6311::PT6311(){
	position = 0;
	KeyData = 0;
	pinMode(PT_CLK, OUTPUT);
	pinMode(PT_STB, OUTPUT);
	pinMode(PT_DATA, OUTPUT);
//digitalWrite(PT_STB, HIGH);
	PORTC |= (1 << PC4);
//digitalWrite(PT_CLK, HIGH);
	PORTC |= (1 << PC5);
//digitalWrite(PT_DATA, HIGH);
	PORTC |= (1 << PC3);
}
void PT6311::Disk_Demo(){
	for (byte i = 0; i < 10; i++){
//Digit 9
		PT6311::PT6311_writeCommand(ADDRESS9);
					PT6311::PT6311_writeData(((Disk[i]>>8) & 0xFF) | DVD);
				PT6311::PT6311_writeCommand(ADDRESS9 + 1);
					PT6311::PT6311_writeData((Disk[i] & 0xFF) | MHzcode | MEMcode);
		delay(50);
	}
//Digit 9
				PT6311::PT6311_writeCommand(ADDRESS9);
						PT6311::PT6311_writeData(((DISK_FULL>>8) & 0xFF) | DVD);
				PT6311::PT6311_writeCommand(ADDRESS9 + 1);
					PT6311::PT6311_writeData((DISK_FULL & 0xFF) | MHzcode | MEMcode);

}
void PT6311::Display_Write(char numbers_or_text[],byte size, bool _dts, bool _RDS, bool _ST, bool _DOLBY,
		bool _TUNED, bool _PLAY, bool _FM, bool _MHz, bool _MEM, bool __3D, bool __2dp1, bool __2dp2, bool _dp1, bool _dp2){
word digit1 = 0x0;
word digit2 = 0x0;
word digit3 = 0x0;
word digit4 = 0x0;
word digit5 = 0x0;
word digit6 = 0x0;
word digit7 = 0x0;
word digits[7] = {digit7, digit6, digit5, digit4, digit3, digit2, digit1};
byte shift = 0;
byte length = size;
	for (byte i = 0; i < size; i++){
			if (numbers_or_text[i] == 46 && i == 3) {_dp1 = true; length--;}
			if (numbers_or_text[i] == 58 && i == 3) {__2dp1 = true; length--;}
			if (numbers_or_text[i] == 46 && i == 6) {_dp2 = true; length--;}
			if (numbers_or_text[i] == 58 && i == 6) {__2dp2 = true; length--;}
	}
	if(length <= 7)
		for (byte i = 0; i < 7; i++){
			if (numbers_or_text[i] == 46 || numbers_or_text[i] == 58){
				if(shift == 2) digits[i] = converter (numbers_or_text[i+2]);
				else digits[i] = converter (numbers_or_text[i+1]);
				shift++;
			} else {
				if(shift == 1){
					if(numbers_or_text[i+1] == 46 || numbers_or_text[i+1] == 58){
						digits[i] = converter (numbers_or_text[i+2]);
						shift++;
					}
					else digits[i] = converter (numbers_or_text[i+1]);
				}
				else
				digits[i] = converter (numbers_or_text[i]);
			}
	} else {
		for (byte j = 0; j < 7; j++){
			for(byte i = position; i < size; i++){
				digits[j] = converter (numbers_or_text[i]);
				break;
			}
			if(position == size) position = 0;
			else position++;
		}


	}
	PT6311::PT6311_writeCommand(WRITE_DATA_TO_DISPLAY);
	//Digit 1
			PT6311::PT6311_writeCommand(ADDRESS1);
					if(_dts) PT6311::PT6311_writeData(((digits[6]>>8) & 0xFF) | dtscode);
					else	PT6311::PT6311_writeData((digits[6]>>8) & 0xFF);
				PT6311::PT6311_writeCommand(ADDRESS1 + 1);
					PT6311::PT6311_writeData(digits[6] & 0xFF);
	//Digit 2
			PT6311::PT6311_writeCommand(ADDRESS2);
					if(_RDS) PT6311::PT6311_writeData(((digits[5]>>8) & 0xFF) | RDScode);
					else PT6311::PT6311_writeData((digits[5]>>8) & 0xFF);
				PT6311::PT6311_writeCommand(ADDRESS2 + 1);
					PT6311::PT6311_writeData(digits[5] & 0xFF);
	//Digit 3
			PT6311::PT6311_writeCommand(ADDRESS3);
					if(__2dp2) PT6311::PT6311_writeData(((digits[4]>>8) & 0xFF) | _2dpcode);
					else PT6311::PT6311_writeData((digits[4]>>8) & 0xFF);
				PT6311::PT6311_writeCommand(ADDRESS3 + 1);
					if(_dp2) PT6311::PT6311_writeData((digits[4] & 0xFF) | dpcode);
					else PT6311::PT6311_writeData(digits[4] & 0xFF);
	//Digit 4
			PT6311::PT6311_writeCommand(ADDRESS4);
					if(_ST) PT6311::PT6311_writeData(((digits[3]>>8) & 0xFF) | STcode);
					else PT6311::PT6311_writeData((digits[3]>>8) & 0xFF);
				PT6311::PT6311_writeCommand(ADDRESS4 + 1);
					if(_DOLBY) PT6311::PT6311_writeData((digits[3] & 0xFF) | DOLBYcode);
					else PT6311::PT6311_writeData(digits[3] & 0xFF);
	//Digit 5
			PT6311::PT6311_writeCommand(ADDRESS5);
					if(__2dp1) PT6311::PT6311_writeData(((digits[2]>>8) & 0xFF)| _2dpcode);
					else PT6311::PT6311_writeData((digits[2]>>8) & 0xFF);
				PT6311::PT6311_writeCommand(ADDRESS5 + 1);
					if(_dp1) PT6311::PT6311_writeData((digits[2] & 0xFF) | dpcode);
					else PT6311::PT6311_writeData((digits[2] & 0xFF));
	//Digit 6
			PT6311::PT6311_writeCommand(ADDRESS6);
					if(_TUNED){
						PT6311::PT6311_writeData(((digits[1]>>8) & 0xFF) | TUNEDcode);
					PT6311::PT6311_writeCommand(ADDRESS6 + 1);
						PT6311::PT6311_writeData((digits[1] & 0xFF) | two_coilscode);
					} else {
						PT6311::PT6311_writeData((digits[1]>>8) & 0xFF);
					PT6311::PT6311_writeCommand(ADDRESS6 + 1);
						PT6311::PT6311_writeData(digits[1] & 0xFF);
					}

	//Digit 7
			PT6311::PT6311_writeCommand(ADDRESS7);
					PT6311::PT6311_writeData(((digits[0]>>8) & 0xFF));
				PT6311::PT6311_writeCommand(ADDRESS7 + 1);
					PT6311::PT6311_writeData(digits[0] & 0xFF);
	//Digit 8
					if(_PLAY) {
						PT6311::PT6311_writeCommand(ADDRESS8);
							PT6311::PT6311_writeData(PLAYcode);
					} else {
						PT6311::PT6311_writeCommand(ADDRESS8);
							PT6311::PT6311_writeData(0x00);
						}
					if (_FM){
						PT6311::PT6311_writeCommand(ADDRESS8 + 1);
							PT6311::PT6311_writeData(FMcode);
					} else {
						PT6311::PT6311_writeCommand(ADDRESS8 + 1);
							PT6311::PT6311_writeData(0x00);
					}
	//Digit 9
			PT6311::PT6311_writeCommand(ADDRESS9);
					PT6311::PT6311_writeData(((DISK_FULL>>8) & 0xFF) | DVD);
				PT6311::PT6311_writeCommand(ADDRESS9 + 1);
				if(_MHz && _MEM && __3D) PT6311::PT6311_writeData((DISK_FULL & 0xFF) | MHzcode | MEMcode | _3Dcode);
				else if(_MHz && _MEM) PT6311::PT6311_writeData((DISK_FULL & 0xFF) | MHzcode | MEMcode);
				else if(_MHz && __3D) PT6311::PT6311_writeData((DISK_FULL & 0xFF) | MHzcode | _3Dcode);
				else if(_MEM) PT6311::PT6311_writeData((DISK_FULL & 0xFF) | MEMcode);
				else if(_MHz) PT6311::PT6311_writeData((DISK_FULL & 0xFF) | MHzcode);
				else if(__3D) PT6311::PT6311_writeData((DISK_FULL & 0xFF) | _3Dcode);
				else  PT6311::PT6311_writeData(DISK_FULL & 0xFF);

	PT6311::PT6311_writeCommand(DISPLAY_MODE_9_19);
	PT6311::PT6311_writeCommand(DISPLAY_ON_14_16);
//digitalWrite(PT_STB, HIGH);
		PORTC |= (1 << PC4);
}

void PT6311::Display_OFF(){
		PT6311::PT6311_writeCommand(DISPLAY_OFF);
//digitalWrite(PT_STB, HIGH);
		PORTC |= (1 << PC4);
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
//digitalWrite(PT_STB, HIGH);
	PORTC |= (1 << PC4);
}

void PT6311::PT6311_writeCommand(byte command){
//digitalWrite(PT_STB, HIGH);
	PORTC |= (1 << PC4);
//1.45us (1us ~ 15 nop)
	    	_NOP();
	    	_NOP();
	    	_NOP();
	    	_NOP();
	    	_NOP();
	    	_NOP();
	    	_NOP();
	    	_NOP();
	    	_NOP();
	    	_NOP();
	    	_NOP();
	    	_NOP();
	    	_NOP();
	    	_NOP();
	    	_NOP();
	    	_NOP();
	    	_NOP();
	    	_NOP();
	    	_NOP();
	    	_NOP();
//digitalWrite(PT_STB, LOW);
	PORTC &= ~(1 << PC4);
	PT6311::PT6311_writeByte(command);
}

void PT6311::PT6311_writeData(byte data){
	PT6311::PT6311_writeByte(data);
}

void PT6311::PT6311_readKey(){
	PT6311::PT6311_writeCommand(READ_KEY);
//pinMode(PT_DATA, INPUT); zero to DDRx
	DDRC &= ~(1 << PC3);
	//1.45us
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		for (byte count = 0; count < 8; count++)
		   {
			if(/*digitalRead(PT_DATA)*/PINC & (1 << 3)) KeyData |= 1;
			KeyData = KeyData<<1;
//digitalWrite(PT_CLK, LOW);
		    PORTC &= ~(1 << PC5);
//1us
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
		    	_NOP();
//digitalWrite(PT_CLK, HIGH);
		    PORTC |= (1 << PC5);
		    	_NOP();
		    	_NOP();
		    	_NOP();
		   }

//digitalWrite(PT_STB, HIGH);
		PORTC |= (1 << PC4);
}

void PT6311::PT6311_writeByte(byte data){
//pinMode(PT_DATA, OUTPUT);
	DDRC |= (1 << PC3);
	for (byte count = 0; count < 8; count++)
	   {
	    if((data>>count)&0x01)
//digitalWrite(PT_DATA,HIGH);
	    	PORTC |= (1 << PC3);
	                       else
//digitalWrite(PT_DATA,LOW);
	                    	   PORTC &= ~(1 << PC3);
//digitalWrite(PT_CLK, LOW);
	    PORTC &= ~(1 << PC5);
//1us
   		    	_NOP();
   		    	_NOP();
   		    	_NOP();
   		    	_NOP();
   		    	_NOP();
   		    	_NOP();
   		    	_NOP();
   		    	_NOP();
   		    	_NOP();
   		    	_NOP();
   		    	_NOP();
   		    	_NOP();
   		    	_NOP();
   		    	_NOP();
//digitalWrite(PT_CLK, HIGH);
	    PORTC |= (1 << PC5);
	   }
}
word converter(char symbol){
	word result = 0;
	if(symbol == 32) result = sp;
//	if(symbol == 46) result = dpcode;
	if(symbol == 48) result = ZERO;
	if(symbol == 49) result = ONE;
	if(symbol == 50) result = TWO;
	if(symbol == 51) result = THREE;
	if(symbol == 52) result = FOUR;
	if(symbol == 53) result = FIVE;
	if(symbol == 54) result = SIX;
	if(symbol == 55) result = SEVEN;
	if(symbol == 56) result = EIGHT;
	if(symbol == 57) result = NINE;
//	if(symbol == 58) result = _2dpcode;
	if(symbol == 65 || symbol == 97)  result = A;
	if(symbol == 66 || symbol == 98)  result = B;
	if(symbol == 67 || symbol == 99)  result = C;
	if(symbol == 68 || symbol == 100) result = D;
	if(symbol == 69 || symbol == 101) result = E;
	if(symbol == 70 || symbol == 102) result = F;
	if(symbol == 71 || symbol == 103) result = G;
	if(symbol == 72 || symbol == 104) result = H;
	if(symbol == 73 || symbol == 105) result = I;
	if(symbol == 74 || symbol == 106) result = J;
	if(symbol == 75 || symbol == 107) result = K;
	if(symbol == 76 || symbol == 108) result = L;
	if(symbol == 77 || symbol == 109) result = M;
	if(symbol == 78 || symbol == 110) result = N;
	if(symbol == 79 || symbol == 111) result = O;
	if(symbol == 80 || symbol == 112) result = P;
	if(symbol == 81 || symbol == 113) result = Q;
	if(symbol == 82 || symbol == 114) result = R;
	if(symbol == 83 || symbol == 115) result = S;
	if(symbol == 84 || symbol == 116) result = T;
	if(symbol == 85 || symbol == 117) result = U;
	if(symbol == 86 || symbol == 118) result = V;
	if(symbol == 87 || symbol == 119) result = W;
	if(symbol == 88 || symbol == 120) result = X;
	if(symbol == 89 || symbol == 121) result = Y;
	if(symbol == 90 || symbol == 122) result = Z;
	return result;
}
