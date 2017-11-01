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
	digitalWrite(LV_CE, LOW);
	SPI.transfer(INmode);
	digitalWrite(LV_CE, HIGH);
	SPI.transfer(INdata1);
	SPI.transfer(INdata2);
	SPI.transfer(INdata3);
	digitalWrite(LV_CE, LOW);
	SPI.endTransaction();
}
void LV23002M::LV23002M_OUTmode(){
	digitalWrite(LV_CE, LOW);
	SPI.transfer(OUTmode);
	digitalWrite(LV_CE, HIGH);
	OUTdata1 = SPI.transfer(0x00);
	OUTdata2 = SPI.transfer(0x00);
	OUTdata3 = SPI.transfer(0x00);
	digitalWrite(LV_CE, LOW);
	SPI.endTransaction();
}
