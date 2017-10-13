/*
 * LV23002M.h
 *
 *  Created on: 9 окт. 2017 г.
 *      Author: snibler
 */
#include <Arduino.h>
#include <SPI.h>

#ifndef LV23002M_H_
#define LV23002M_H_

//defining pins to witch MEGA connected
#define LV_CE SS
#define LV_DI MOSI
#define LV_CLK SCK
#define LV_DO MISO

//defining chip modes
#define IN1mode 0b00010100
#define IN2mode 0b10010100
#define OUTmode 0b01010100

class LV23002M {
private:
public:
	byte OUTdata1;
	byte OUTdata2;
	byte OUTdata3;
	void LV23002M_INmode(byte INmode, byte INdata1, byte INdata2, byte INdata3);
	void LV23002M_OUTmode();
	void LM23002M();
};

#endif /* LV23002M_H_ */
