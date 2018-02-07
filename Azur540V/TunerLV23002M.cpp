/*
 * LV23002M.cpp
 *
 *  Created on: 13 окт. 2017 г.
 *      Author: snibler
 */

#include "TunerLV23002M.h"


void TunerLV23002M::LM23002M_init(){
	SPI.begin();
	SPI.beginTransaction(SPISettings(500000, MSBFIRST, SPI_MODE0));
	FQcurrent = FQbottom;
	MEMstations = 30;
}
void TunerLV23002M::playST(byte MEMstationCurrent){
	if(MEMstationCurrent != 0){
		byte highByteAddr = MEMstationCurrent + (MEMstationCurrent - 1);
		byte lowByteAddr = highByteAddr + 1;
		FQcurrent = 0;
		FQcurrent = EEPROM.read(highByteAddr);
		FQcurrent = (FQcurrent<<8);
		FQcurrent |= EEPROM.read(lowByteAddr);
		if (FQcurrent < FQbottom || FQcurrent > FQtop) FQcurrent = FQbottom;
		TunerLV23002M::LV23002M_INmode(IN1mode,reverseByte(lowByte(FQcurrent)),reverseByte(highByte(FQcurrent)),0x41);
		TunerLV23002M::LV23002M_INmode(IN2mode,0x57,0xA8,0x28);
	} else _NOP();
}
void TunerLV23002M::writeMEM(){
	if(MEMstationCurrent < MEMstations)
		MEMstationCurrent += 1;
	else
		MEMstationCurrent = 1;
	byte highByteAddr = MEMstationCurrent + (MEMstationCurrent - 1);
	byte lowByteAddr = highByteAddr + 1;
	EEPROM.write(highByteAddr, highByte(FQcurrent));
	EEPROM.write(lowByteAddr, lowByte(FQcurrent));
}
void TunerLV23002M::freq_m(){
	if(FQcurrent > FQbottom){
		FQcurrent -= 10;
		TunerLV23002M::LV23002M_INmode(IN1mode,reverseByte(lowByte(FQcurrent)),reverseByte(highByte(FQcurrent)),0x41);
		TunerLV23002M::LV23002M_INmode(IN2mode,0x57,0xA8,0x28);
	} else FQcurrent = FQtop;
}
void TunerLV23002M::freq_p(){
	if(FQcurrent < FQtop){
		FQcurrent += 10;
		TunerLV23002M::LV23002M_INmode(IN1mode,reverseByte(lowByte(FQcurrent)),reverseByte(highByte(FQcurrent)),0x41);
		TunerLV23002M::LV23002M_INmode(IN2mode,0x57,0xA8,0x28);
	} else FQcurrent = FQbottom;
}
void TunerLV23002M::playMEM_plus(){
	if(MEMstationCurrent < MEMstations)
		MEMstationCurrent += 1;
	else
		MEMstationCurrent = 1;
	TunerLV23002M::playMEM();
}
void TunerLV23002M::playMEM_minus(){
	if(MEMstationCurrent > 1)
		MEMstationCurrent -= 1;
	else
		MEMstationCurrent = 1;
	TunerLV23002M::playMEM();
}
void TunerLV23002M::playMEM(){
	byte highByteAddr = MEMstationCurrent + (MEMstationCurrent - 1);
	byte lowByteAddr = highByteAddr + 1;
	FQcurrent = 0;
	FQcurrent = EEPROM.read(highByteAddr);
	FQcurrent = (FQcurrent << 8);
	FQcurrent |= EEPROM.read(lowByteAddr);
	if (FQcurrent < FQbottom || FQcurrent > FQtop) FQcurrent = FQbottom;
	TunerLV23002M::LV23002M_INmode(IN1mode,reverseByte(lowByte(FQcurrent)),reverseByte(highByte(FQcurrent)),0x41);
	TunerLV23002M::LV23002M_INmode(IN2mode,0x57,0xA8,0x28);

}
void TunerLV23002M::mute(){
	TunerLV23002M::LV23002M_INmode(IN2mode,MUTE,0xA8,0x28);
}
void TunerLV23002M::LV23002M_INmode(byte INmode, byte INdata1, byte INdata2, byte INdata3){
	PORTB &= ~(1 << LV_CE);
	delayMicroseconds(1);
	SPI.transfer(INmode);
	delayMicroseconds(1);
	PORTB |= (1 << LV_CE);
	SPI.transfer(INdata1);
	SPI.transfer(INdata2);
	SPI.transfer(INdata3);
	PORTB &= ~(1 << LV_CE);
	delayMicroseconds(1);
	SPI.endTransaction();
}
void TunerLV23002M::LV23002M_OUTmode(){
	PORTB &= ~(1 << LV_CE);
	delayMicroseconds(1);
	SPI.transfer(OUTmode);
	delayMicroseconds(1);
	PORTB |= (1 << LV_CE);
	byte OUTdata1 = SPI.transfer(0x00);
	byte OUTdata2 = SPI.transfer(0x00);
	byte OUTdata3 = SPI.transfer(0x00);
	PORTB &= ~(1 << LV_CE);
	delayMicroseconds(1);
	SPI.endTransaction();
	indicators = (OUTdata1 >> 4);
	IFcounterbin = 0;
	IFcounterbin = OUTdata1;
	IFcounterbin = (IFcounterbin << 8);
	IFcounterbin |= OUTdata2;
	IFcounterbin = (IFcounterbin << 8);
	IFcounterbin |= OUTdata3;
}
unsigned char TunerLV23002M::reverseByte(byte data){
	byte result = 0;
	for(byte i = 0;i < 8;i++){
		if (data & (1 << i)) result |= 1 << (7-i);
	}
	return result;
}
