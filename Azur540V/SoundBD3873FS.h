/*
 * BD3873FS.h
 *
 *  Created on: 21 нояб. 2017 г.
 *      Author: snibler
 */
#include <Arduino.h>

#ifndef BD3873FS_H_
#define BD3873FS_H_

#define BD_CLK	PD4
#define BD_DATA	PD5

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

#define SURR_ON		0x20
#define SURR_OFF	0x00

#define VOL_0dB			0x00
#define VOL_step_dB		0x08
#define VOL_step_1dB	0x10
#define VOL_87dB		0x3F8

#define BASS_0dB		0x00
#define BASS_14dB		0x3C0
#define BASS_step_1dB	0x40
#define BASS_step_2dB	0x80

#define TREBLE_0dB		0x00
#define TREBLE_12dB		0x3C
#define TREBLE_step_1dB	0x04
#define TREBLE_step_2dB	0x08

class SoundBD3873FS {
private:
	bool state_sur;
	word addr_data_10bits;
	int last_vposition;
	word last_volume;
	int last_bposition;
	word last_bass;
	int last_tposition;
	word last_treble;
	int last_sposition;
	int last_iposition;
	word current_input;
	void write_10bits_to_chip(word data);
	void volume_up();
	void volume_down();
	void bass_up();
	void bass_down();
	void treble_up();
	void treble_down();
public:
	bool state_inp;
	char * dispArray;
	SoundBD3873FS();
	void BD3873FS_init();
	void volume_control(int position);
	void bass_control(int position);
	void treble_control(int position);
	void surr_control(int position);
	void input_control(int position);
	char * toArray(char name[4]);
};

#endif /* BD3873FS_H_ */
