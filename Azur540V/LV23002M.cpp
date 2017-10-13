/*
 * LV23002M.cpp
 *
 *  Created on: 13 окт. 2017 г.
 *      Author: snibler
 */

#include "LV23002M.h"

void LV23002M::LM23002M(){
	SPI.begin();

}
void LV23002M::LV23002M_INmode(byte INmode, byte INdata1, byte INdata2, byte INdata3){
	SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE1));
	digitalWrite(SS, LOW);
	SPI.transfer(INmode);
	digitalWrite(SS, HIGH);
	SPI.transfer(INdata1);
	SPI.transfer(INdata2);
	SPI.transfer(INdata3);
	SPI.endTransaction();
}
void LV23002M::LV23002M_OUTmode(){
	SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE0));
	digitalWrite(SS, LOW);
	SPI.transfer(OUTmode);
	digitalWrite(SS, HIGH);
	LV23002M::OUTdata1 = SPI.transfer(0x00);
	LV23002M::OUTdata2 = SPI.transfer(0x00);
	LV23002M::OUTdata3 = SPI.transfer(0x00);
	SPI.endTransaction();
}
