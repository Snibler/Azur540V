/*
 * LV23002M.cpp
 *
 *  Created on: 13 окт. 2017 г.
 *      Author: snibler
 */

#include "LV23002M.h"


void LV23002M::LM23002M_init(){
	SPI.begin();
	SPI.beginTransaction(SPISettings(500000, MSBFIRST, SPI_MODE0));
	FQ = FQbottom;
	FQcurrent = FQbottom;
}
void LV23002M::autoscan(){

}
void LV23002M::freq_m(){
	if(FQ > FQbottom){
		FQ = FQcurrent - 10;
		LV23002M::LV23002M_INmode(IN1mode,reverseByte(lowByte(FQ)),reverseByte(highByte(FQ)),0x40);
		LV23002M::LV23002M_INmode(IN2mode,0x57,0xA8,0x28);
	} else _NOP();
}
void LV23002M::freq_p(){
	if(FQ < FQtop){
		FQ = FQcurrent + 10;
		LV23002M::LV23002M_INmode(IN1mode,reverseByte(lowByte(FQ)),reverseByte(highByte(FQ)),0x40);
		LV23002M::LV23002M_INmode(IN2mode,0x57,0xA8,0x28);
	} else _NOP();
}
void LV23002M::playMEM(){
//write to radio 101.1FM "Радио Пятница"
	LV23002M::LV23002M_INmode(IN1mode,reverseByte(lowByte(2236)),reverseByte(highByte(2236)),0x40);
	LV23002M::LV23002M_INmode(IN2mode,0x57,0xA8,0x28);
}
void LV23002M::mute(){
	LV23002M::LV23002M_INmode(IN2mode,MUTE,0xA8,0x28);
}
void LV23002M::readstatus(){
	do {
		LV23002M::LV23002M_OUTmode();
		delay(5);
		}
		while ((indicators & (1 << 2)) && (~indicators & (1 << 0)));
	LV23002M::LV23002M_INmode(IN1mode,reverseByte(lowByte(2236)),reverseByte(highByte(2236)),0x60);
	loop_until_bit_is_clear(PINB, 4);
	delay(5);
	LV23002M::LV23002M_OUTmode();
}
void LV23002M::LV23002M_INmode(byte INmode, byte INdata1, byte INdata2, byte INdata3){
//digitalWrite(LV_CE, LOW);
	PORTB &= ~(1 << PB2);
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
	SPI.transfer(INmode);
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
//digitalWrite(LV_CE, HIGH);
	PORTB |= (1 << PB2);
	SPI.transfer(INdata1);
	SPI.transfer(INdata2);
	SPI.transfer(INdata3);
//digitalWrite(LV_CE, LOW);
	PORTB &= ~(1 << PB2);
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
	SPI.endTransaction();
}
void LV23002M::LV23002M_OUTmode(){
//digitalWrite(LV_CE, LOW);
	PORTB &= ~(1 << PB2);
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
	SPI.transfer(OUTmode);
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
//digitalWrite(LV_CE, HIGH);
	PORTB |= (1 << PB2);
	byte OUTdata1 = SPI.transfer(0x00);
	byte OUTdata2 = SPI.transfer(0x00);
	byte OUTdata3 = SPI.transfer(0x00);
//digitalWrite(LV_CE, LOW);
	PORTB &= ~(1 << PB2);
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
	SPI.endTransaction();
	indicators = OUTdata1>>4;
	IFcounterbin |= OUTdata1;
	IFcounterbin = (IFcounterbin<<8)|OUTdata2;
	IFcounterbin = (IFcounterbin<<8)|OUTdata3;
	IFcounterbin = (IFcounterbin & 0x0FFF);
}
unsigned char LV23002M::reverseByte(byte data){
	byte result = 0;
	for(byte i = 0;i < 8;i++){
		if (data & (1 << i))
			{
			result |= 1 << (7-i);
			}
	}
	return result;
}
