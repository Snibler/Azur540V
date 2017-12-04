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
	FQcurrent = FQbottom;
	MEMstations = 30;
}
void LV23002M::playST(byte MEMstationCurrent){
	if(MEMstationCurrent != 0){
		byte highByteAddr = MEMstationCurrent + (MEMstationCurrent - 1);
		byte lowByteAddr = highByteAddr + 1;
		FQcurrent = 0;
		FQcurrent = EEPROM.read(highByteAddr);
		FQcurrent = (FQcurrent<<8);
		FQcurrent |= EEPROM.read(lowByteAddr);
		if (FQcurrent < FQbottom || FQcurrent > FQtop) FQcurrent = FQbottom;
		LV23002M::LV23002M_INmode(IN1mode,reverseByte(lowByte(FQcurrent)),reverseByte(highByte(FQcurrent)),0x41);
		LV23002M::LV23002M_INmode(IN2mode,0x57,0xA8,0x28);
	} else _NOP();
}
void LV23002M::writeMEM(){
	if(MEMstationCurrent < MEMstations)
			MEMstationCurrent += 1;
		else {
			MEMstationCurrent = 1;
		}
		byte highByteAddr = MEMstationCurrent + (MEMstationCurrent - 1);
		byte lowByteAddr = highByteAddr + 1;
		EEPROM.write(highByteAddr, highByte(FQcurrent));
		EEPROM.write(lowByteAddr, lowByte(FQcurrent));
}
void LV23002M::freq_m(){
	if(FQcurrent > FQbottom){
		FQcurrent -= 10;
		LV23002M::LV23002M_INmode(IN1mode,reverseByte(lowByte(FQcurrent)),reverseByte(highByte(FQcurrent)),0x41);
		LV23002M::LV23002M_INmode(IN2mode,0x57,0xA8,0x28);
	} else FQcurrent = FQtop;
}
void LV23002M::freq_p(){
	if(FQcurrent < FQtop){
		FQcurrent += 10;
		LV23002M::LV23002M_INmode(IN1mode,reverseByte(lowByte(FQcurrent)),reverseByte(highByte(FQcurrent)),0x41);
		LV23002M::LV23002M_INmode(IN2mode,0x57,0xA8,0x28);
	} else FQcurrent = FQbottom;
}
void LV23002M::playMEM_plus(){
	if(MEMstationCurrent < MEMstations)
			MEMstationCurrent += 1;
		else {
			MEMstationCurrent = 1;
		}
	LV23002M::playMEM();
}
void LV23002M::playMEM_minus(){
	if(MEMstationCurrent > 1)
			MEMstationCurrent -= 1;
		else {
			MEMstationCurrent = 1;
		}
	LV23002M::playMEM();
}
void LV23002M::playMEM(){
	byte highByteAddr = MEMstationCurrent + (MEMstationCurrent - 1);
	byte lowByteAddr = highByteAddr + 1;
	FQcurrent = 0;
	FQcurrent = EEPROM.read(highByteAddr);
	FQcurrent = (FQcurrent<<8);
	FQcurrent |= EEPROM.read(lowByteAddr);
	if (FQcurrent < FQbottom || FQcurrent > FQtop) FQcurrent = FQbottom;
	LV23002M::LV23002M_INmode(IN1mode,reverseByte(lowByte(FQcurrent)),reverseByte(highByte(FQcurrent)),0x41);
	LV23002M::LV23002M_INmode(IN2mode,0x57,0xA8,0x28);

}
void LV23002M::mute(){
	LV23002M::LV23002M_INmode(IN2mode,MUTE,0xA8,0x28);
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
	indicators = (OUTdata1>>4);
	IFcounterbin = 0;
	IFcounterbin = OUTdata1;
	IFcounterbin = (IFcounterbin<<8);
	IFcounterbin |= OUTdata2;
	IFcounterbin = (IFcounterbin<<8);
	IFcounterbin |= OUTdata3;
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
