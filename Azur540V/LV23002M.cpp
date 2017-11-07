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
}
void LV23002M::LV23002M_INmode(byte INmode, byte INdata1, byte INdata2, byte INdata3){
//	digitalWrite(LV_CE, LOW);
	PORTB &= ~(1 << PB2);
		_NOP();
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	SPI.transfer(INmode);
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
//	digitalWrite(LV_CE, HIGH);
	PORTB |= (1 << PB2);
	SPI.transfer(INdata1);
	SPI.transfer(INdata2);
	SPI.transfer(INdata3);
//	digitalWrite(LV_CE, LOW);
	PORTB &= ~(1 << PB2);
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	SPI.endTransaction();
}
void LV23002M::LV23002M_OUTmode(){
//	digitalWrite(LV_CE, LOW);
	PORTB &= ~(1 << PB2);
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	SPI.transfer(OUTmode);
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
//	digitalWrite(LV_CE, HIGH);
	PORTB |= (1 << PB2);
	OUTdata1 = SPI.transfer(0x00);
	OUTdata2 = SPI.transfer(0x00);
	OUTdata3 = SPI.transfer(0x00);
//	digitalWrite(LV_CE, LOW);
	PORTB &= ~(1 << PB2);
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	SPI.endTransaction();
}
