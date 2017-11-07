/*
 * PT6311.h
 *
 *  Created on: 9 окт. 2017 г.
 *      Author: snibler
 *
 */
#include <Arduino.h>
#include "digits.h"
#include "alphabet.h"
#include "special.h"
#include "keys.h"

#ifndef PT6311_H_
#define PT6311_H_

//defining pins to witch MEGA connected
#define PT_CLK A5
#define PT_STB A4
#define PT_DATA A3

//COMMAND 1: DISPLAY MODE SETTING COMMANDS
#define DISPLAY_MODE_8_20  0b00000000	//0XXX: 8 digits, 20 segments
#define DISPLAY_MODE_9_19  0b00001000	//1000: 9 digits, 19 segments
#define DISPLAY_MODE_10_18 0b00001001	//1001: 10 digits, 18 segments
#define DISPLAY_MODE_11_17 0b00001010	//1010: 11 digits, 17 segments
#define DISPLAY_MODE_12_16 0b00001011	//1011: 12 digits, 16 segments
#define DISPLAY_MODE_13_15 0b00001100	//1100: 13 digits, 15 segments
#define DISPLAY_MODE_14_14 0b00001101	//1101: 14 digits, 14 segments
#define DISPLAY_MODE_15_13 0b00001110	//1110: 15 digits, 13 segments
#define DISPLAY_MODE_16_12 0b00001111	//1111: 16 digits, 12 segments
//COMMAND 2: DATA SETTING COMMANDS
#define WRITE_DATA_TO_DISPLAY  0b01000000 //0b01000001 - Increment Address after Data has been Written
#define WRITE_DATA_TO_LED_PORT 0b01000001 //0b01000101 - Fixed Address
#define READ_KEY			   0b01000010
#define READ_SW				   0b01000011
//COMMAND 3: ADDRESS SETTING COMMANDS 00H to 2FH (address of the display memory)
#define ADDRESS_BOTTOM 	0b11000000	//00H
#define ADDRESS1 0xC0
#define ADDRESS2 0xC3
#define ADDRESS3 0xC6
#define ADDRESS4 0xC9
#define ADDRESS5 0xCC
#define ADDRESS6 0xCF
#define ADDRESS7 0xD2
#define ADDRESS8 0xD5
#define ADDRESS9 0xD8
#define ADDRESS_TOP 	0b11101111	//2FH
//COMMAND 4: DISPLAY CONTROL COMMANDS
#define DISPLAY_OFF 		0b10000000	//Pulse width = 1/16, Key Scan Continues
#define DISPLAY_ON_1_16 	0b10001000	//Pulse width = 1/16
#define DISPLAY_ON_2_16  	0b10001001	//Pulse width = 2/16
#define DISPLAY_ON_4_16  	0b10001010	//Pulse width = 4/16
#define DISPLAY_ON_10_16  	0b10001011	//Pulse width = 10/16
#define DISPLAY_ON_11_16  	0b10001100	//Pulse width = 11/16
#define DISPLAY_ON_12_16  	0b10001101	//Pulse width = 12/16
#define DISPLAY_ON_13_16  	0b10001110	//Pulse width = 13/16
#define DISPLAY_ON_14_16  	0b10001111	//Pulse width = 14/16

class PT6311 {
private:

	void PT6311_writeByte(byte dat_com);
	void PT6311_writeCommand(byte command);
	void PT6311_writeData(byte data);

public:
	byte KeyData;
	PT6311();
	void PT6311_init();
	void Display_OFF();
	void Disk_Demo();
	void Display_Write(char numbers_or_text[],byte size, bool _dts, bool _RDS, bool _ST, bool _DOLBY,
			bool _TUNED, bool _PLAY, bool _FM, bool _MHz, bool _MEM, bool __3D, bool __2dp1,
			bool __2dp2, bool _dp1, bool _dp2);;
	void PT6311_readKey();
};

#endif /* PT6311_H_ */
