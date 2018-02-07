/*
 * LV23002M.h
 *
 * Sample of divider calculation
 *
 * FM, step adjusting 50 kHz (DVS=1,SNS=*, input FMIN). Tuning frequency FM RF = 90 MHz (IF= +10.7 MHz),
 * frequency of geterodyne FM VCO = 100.7 MHz, PLL fref = 25 kHz (R0=1, R1=1, R2=0, R3=0).
 * Coefficient to be written in P0..P15 equal (divide on 2, because internal divider on 2 is ON):
 * FM VCO / (fref * 2) = 100700 / (25*2) = 2014 (07DEh).
 */

#include <Arduino.h>
#include <SPI.h>
#include <EEPROM.h>

#ifndef LV23002M_H_
#define LV23002M_H_

#define FQbottom	9820	//87.5MHz tuning step 10 кГц
#define FQtop		11870	//108MHz tuning step 10 кГц

//defining pins to witch MEGA connected
#define LV_CE PB2
#define LV_DI PB3
#define LV_CLK PB5
#define LV_DO PB4

//defining chip modes
#define IN1mode 0x14	//0b00010100
#define IN2mode 0x94	//0b10010100
#define OUTmode 0x54	//0b01010100

//defining INdata bytes
#define MUTE	0x08

class TunerLV23002M {
private:
		byte MEMstations;
		void LV23002M_INmode(byte INmode, byte INdata1, byte INdata2, byte INdata3);
		void LV23002M_OUTmode();
		unsigned char reverseByte(byte data);
public:
		byte MEMstationCurrent;
		word FQcurrent;
		byte indicators;
		unsigned long IFcounterbin;
		void LM23002M_init();
		void freq_m();
		void freq_p();
		void playMEM();
		void playMEM_plus();
		void playMEM_minus();
		void mute();
		void writeMEM();
		void playST(byte MEMstationCurrent);
};

#endif /* LV23002M_H_ */
