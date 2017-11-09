/*
 * LV23002M.h
 *
 *  Created on: 9 окт. 2017 г.
 *      Author: snibler
 */
//#include <wiring.c>
#include <Arduino.h>
#include <SPI.h>

#ifndef LV23002M_H_
#define LV23002M_H_

#define FQbottom	1964	//87.5MHz
#define FQtop		2374	//108MHz

//defining pins to witch MEGA connected
#define LV_CE SS		//PB2
#define LV_DI MOSI		//PB3
#define LV_CLK SCK		//PB5
#define LV_DO MISO		//PB4

//defining chip modes
#define IN1mode 0x14	//0b00010100
#define IN2mode 0x94	//0b10010100
#define OUTmode 0x54	//0b01010100

//defining INdata bytes
#define MUTE	0x08

class LV23002M {
private:
		void LV23002M_INmode(byte INmode, byte INdata1, byte INdata2, byte INdata3);
		void LV23002M_OUTmode();
		unsigned char reverseByte(byte data);
public:
		unsigned int FQ;
		unsigned int FQcurrent;
		byte indicators;
		unsigned long IFcounterbin;
		void LM23002M_init();
		void autoscan();
		void freq_m();
		void freq_p();
		void playMEM();
		void mute();
		void readstatus();

};

#endif /* LV23002M_H_ */
