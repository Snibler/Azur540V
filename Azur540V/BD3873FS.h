/*
 * BD3873FS.h
 *
 *  Created on: 21 нояб. 2017 г.
 *      Author: snibler
 */
#include <Arduino.h>

#ifndef BD3873FS_H_
#define BD3873FS_H_

#define BD_CLK	4
#define BD_DATA	5

#define INPUT_SURR_addr 	0x0
#define VOL_addr 			0x01
#define BASS_TREBLE_addr 	0x02

#define INPUT_A	0x00	//Tuner
#define INPUT_B	0x100	//TAPE
#define INPUT_C	0x200	//CD

#define INPUT_GAIN_18dB	0x00
#define INPUT_GAIN_21dB	0x40
#define INPUT_GAIN_24dB	0x80
#define INPUT_GAIN_27dB	0xC0

#define SURR	0x20
//0 to –87dB/1dB step
#define VOL_A_null		0x00
#define VOL_A_bottom	0x20
#define VOL_A_top		0x3E0
#define VOL_A_step		0x20

#define VOL_B_null		0x00
#define VOL_B_bottom	0x08
#define VOL_B_top		0x18
#define VOL_B_step		0x08

#define BASS_0dB		0x00
#define BASS_14dB		0x380	//0x3C0
#define BASS_step_2dB	0x40

#define TREBLE_0dB		0x00
#define TREBLE_12dB		0x30	//0x3C
#define TREBLE_step_2dB	0x04

class BD3873FS {
private:
	word addr_data_10bits;
	void write_10bits_to_chip(word data);
public:
	BD3873FS();
	void BD3873FS_init();
};

#endif /* BD3873FS_H_ */
