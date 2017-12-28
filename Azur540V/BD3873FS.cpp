/*
 * BD3873FS.cpp
 *
 *  Created on: 21 нояб. 2017 г.
 *      Author: snibler
 */
#include "BD3873FS.h"

BD3873FS::BD3873FS(){
	current_input = INPUT_B;
	state_sur = false;
	state_inp = false;
	addr_data_10bits = 0;
	last_vposition = 0;
	last_volume = 0x208;
	last_bposition = 0;
	last_bass = BASS_0dB;
	last_tposition = 0;
	last_treble = TREBLE_0dB;
	last_sposition = 0;
	last_iposition = 0;
	dispArray = calloc(7, 1);
	pinMode(BD_CLK, OUTPUT);
	pinMode(BD_DATA, OUTPUT);
	digitalWrite(BD_CLK, LOW);
	digitalWrite(BD_DATA, LOW);
}
void BD3873FS::BD3873FS_init(){
	addr_data_10bits = current_input | INPUT_GAIN_18dB | SURR_OFF | INPUT_SURR_addr;
	BD3873FS::write_10bits_to_chip(addr_data_10bits);
	addr_data_10bits = VOL_87dB | VOL_addr;
	BD3873FS::write_10bits_to_chip(addr_data_10bits);
	addr_data_10bits = BASS_0dB | TREBLE_0dB | BASS_TREBLE_addr;
	BD3873FS::write_10bits_to_chip(addr_data_10bits);
	addr_data_10bits = 0x03;
	BD3873FS::write_10bits_to_chip(addr_data_10bits);
	delayMicroseconds(5);
	addr_data_10bits = last_volume | VOL_addr;
	BD3873FS::write_10bits_to_chip(addr_data_10bits);
}
void BD3873FS::input_control(int position){
	if(position > last_iposition) state_inp = true;
		else if(position < last_iposition) state_inp = false;
	if(state_inp) current_input = INPUT_A;
	else current_input = INPUT_B;
	addr_data_10bits = current_input | INPUT_GAIN_18dB | SURR_OFF | INPUT_SURR_addr;
	BD3873FS::write_10bits_to_chip(addr_data_10bits);
	addr_data_10bits = last_volume | VOL_addr;
	BD3873FS::write_10bits_to_chip(addr_data_10bits);
	last_iposition = position;
}
void BD3873FS::surr_control(int position){
	if(position > last_sposition) state_sur = true;
		else if(position < last_sposition) state_sur = false;
	if(state_sur) addr_data_10bits = current_input | INPUT_GAIN_18dB | SURR_ON | INPUT_SURR_addr;
	else addr_data_10bits = current_input | INPUT_GAIN_18dB | SURR_OFF | INPUT_SURR_addr;
	BD3873FS::write_10bits_to_chip(addr_data_10bits);
	addr_data_10bits = last_volume | VOL_addr;
	BD3873FS::write_10bits_to_chip(addr_data_10bits);
	last_sposition = position;
}
void BD3873FS::volume_control(int position){
	if(position > last_vposition) volume_up();
	else if(position < last_vposition) volume_down();
	last_vposition = position;
}
void BD3873FS::volume_up(){
	if(last_volume > 0 && last_volume > VOL_step_dB){
		word volume = last_volume - VOL_step_1dB;
		addr_data_10bits = volume | VOL_addr;
		BD3873FS::write_10bits_to_chip(addr_data_10bits);
		last_volume = volume;
		} else if(last_volume == VOL_step_dB){
			word volume = last_volume - VOL_step_dB;
			addr_data_10bits = volume | VOL_addr;
			BD3873FS::write_10bits_to_chip(addr_data_10bits);
			last_volume = volume;
		}
		else _NOP();
}
void BD3873FS::volume_down(){
	if(last_volume < VOL_87dB && last_volume >= VOL_step_dB){
		word volume = last_volume + VOL_step_1dB;
		addr_data_10bits = volume | VOL_addr;
		BD3873FS::write_10bits_to_chip(addr_data_10bits);
		last_volume = volume;
		} else if(last_volume == 0){
			word volume = last_volume + VOL_step_dB;
			addr_data_10bits = volume | VOL_addr;
			BD3873FS::write_10bits_to_chip(addr_data_10bits);
			last_volume = volume;
		}
		else _NOP();
}
void BD3873FS::bass_control(int position){
	if(position > last_bposition) bass_up();
		else if(position < last_bposition) bass_down();
		last_bposition = position;
		addr_data_10bits = last_volume | VOL_addr;
		BD3873FS::write_10bits_to_chip(addr_data_10bits);
}
void BD3873FS::bass_up(){
	if(last_bass < BASS_14dB && last_bass >= BASS_step_1dB){
			word bass = last_bass + BASS_step_2dB;
			addr_data_10bits = bass | last_treble | BASS_TREBLE_addr;
			BD3873FS::write_10bits_to_chip(addr_data_10bits);
			last_bass = bass;
			} else if(last_bass == 0){
				word bass = last_bass + BASS_step_1dB;
				addr_data_10bits = bass | last_treble | BASS_TREBLE_addr;
				BD3873FS::write_10bits_to_chip(addr_data_10bits);
				last_bass = bass;
			}
			else _NOP();
}
void BD3873FS::bass_down(){
	if(last_bass > 0 && last_bass > BASS_step_1dB){
			word bass = last_bass - BASS_step_2dB;
			addr_data_10bits = bass | last_treble | BASS_TREBLE_addr;
			BD3873FS::write_10bits_to_chip(addr_data_10bits);
			last_bass = bass;
			} else if(last_bass == BASS_step_1dB){
				word bass = last_bass - BASS_step_1dB;
				addr_data_10bits = bass | last_treble | BASS_TREBLE_addr;
				BD3873FS::write_10bits_to_chip(addr_data_10bits);
				last_bass = bass;
			}
			else _NOP();
}
void BD3873FS::treble_control(int position){
	if(position > last_tposition) treble_up();
		else if(position < last_tposition) treble_down();
		last_tposition = position;
		addr_data_10bits = last_volume | VOL_addr;
		BD3873FS::write_10bits_to_chip(addr_data_10bits);
}
void BD3873FS::treble_up(){
	if(last_treble < TREBLE_12dB && last_treble >= TREBLE_step_1dB){
			word treble = last_treble + TREBLE_step_2dB;
			addr_data_10bits = last_bass | treble | BASS_TREBLE_addr;
			BD3873FS::write_10bits_to_chip(addr_data_10bits);
			last_treble = treble;
			} else if(last_treble == 0){
				word treble = last_treble + TREBLE_step_1dB;
				addr_data_10bits = last_bass | treble | BASS_TREBLE_addr;
				BD3873FS::write_10bits_to_chip(addr_data_10bits);
				last_treble = treble;
			}
			else _NOP();
}
void BD3873FS::treble_down(){
	if(last_treble > 0 && last_treble > TREBLE_step_1dB){
			word treble = last_treble - TREBLE_step_2dB;
			addr_data_10bits = last_bass | treble | BASS_TREBLE_addr;
			BD3873FS::write_10bits_to_chip(addr_data_10bits);
			last_treble = treble;
			} else if(last_treble == TREBLE_step_1dB){
				word treble = last_treble - TREBLE_step_1dB;
				addr_data_10bits = last_bass | treble | BASS_TREBLE_addr;
				BD3873FS::write_10bits_to_chip(addr_data_10bits);
				last_treble = treble;
			}
			else _NOP();
}
char * BD3873FS::toArray(char name[4]){
	dispArray[0] = name[0];
	dispArray[1] = name[1];
	dispArray[2] = name[2];
	if(name[0] == 'V'){
		byte bars = 12 - last_volume/0x54;
		if(last_volume == 0){
			dispArray[3] = 0;
			dispArray[4] = 'M';
			dispArray[5] = 'A';
			dispArray[6] = 'X';
		} else if(last_volume == 0x3F8){
			dispArray[3] = 0;
			dispArray[4] = 'M';
			dispArray[5] = 'I';
			dispArray[6] = 'N';
		} else
		for(byte i = 0; i < 4; i++){
			if(bars == 0){
				dispArray[3 + i] = 0;
			} else if(bars < 3){
				if(bars == 2){
					dispArray[3 + i] = '$';
					bars -= 2;
				} else if(bars == 1){
					dispArray[3 + i] = '#';
					bars -= 1;
				}
			} else if(bars > 3 && bars % 3 != 0){
				dispArray[3 + i] = '%';
				bars -= 3;
			} else if(bars % 3 == 0){
				dispArray[3 + i] = '%';
				bars -= 3;
			}
		}
	} else if(name[0] == 'B'){
		byte numb = last_bass/0x80;
		if(numb == 0) 		{dispArray[3] = 0;  dispArray[4] = '0';}
		else if(numb == 1) 	{dispArray[3] = 0;  dispArray[4] = '2';}
		else if(numb == 2) 	{dispArray[3] = 0;  dispArray[4] = '4';}
		else if(numb == 3) 	{dispArray[3] = 0;  dispArray[4] = '6';}
		else if(numb == 4) 	{dispArray[3] = 0;  dispArray[4] = '8';}
		else if(numb == 5) {dispArray[3] = '1';dispArray[4] = '0';}
		else if(numb == 6) {dispArray[3] = '1';dispArray[4] = '2';}
		else if(numb == 7) {dispArray[3] = '1';dispArray[4] = '4';}
		dispArray[5] = 'd';
		dispArray[6] = 'B';
	} else if(name[0] == 'T'){
		byte numb = last_treble/0x08;
					 if(numb == 0) 	{dispArray[3] = 0;  dispArray[4] = '0';}
				else if(numb == 1) 	{dispArray[3] = 0;  dispArray[4] = '2';}
				else if(numb == 2) 	{dispArray[3] = 0;  dispArray[4] = '4';}
				else if(numb == 3) 	{dispArray[3] = 0;  dispArray[4] = '6';}
				else if(numb == 4) 	{dispArray[3] = 0;  dispArray[4] = '8';}
				else if(numb == 5) {dispArray[3] = '1';dispArray[4] = '0';}
				else if(numb == 6) {dispArray[3] = '1';dispArray[4] = '2';}
				else if(numb == 7) {dispArray[3] = '1';dispArray[4] = '2';}
				dispArray[5] = 'd';
				dispArray[6] = 'B';
	} else if(name[0] == 'S'){
		if(state_sur) {
			dispArray[3] = 0;
			dispArray[4] = 'O';
			dispArray[5] = 'N';
			dispArray[6] = 0;
		} else {
			dispArray[3] = 0;
			dispArray[4] = 'O';
			dispArray[5] = 'F';
			dispArray[6] = 'F';
		}
	} else if(name[0] == 'A'){
		if(state_inp) {
					dispArray[3] = 0;
					dispArray[4] = 'I';
					dispArray[5] = 'N';
					dispArray[6] = 0;
				} else {
					dispArray[3] = 0;
					dispArray[4] = 'F';
					dispArray[5] = 'M';
					dispArray[6] = 0;
				}
	}
	return dispArray;
}
void BD3873FS::write_10bits_to_chip(word data){
	for (byte count = 0; count < 10; count++)
		   {
		    if((data<<count)&0x200)
		    	//digitalWrite(BD_DATA,HIGH);
		    	PORTD |= (1 << PD5);
		    else
		    	//digitalWrite(BD_DATA,LOW);
		    	PORTD &= ~(1 << PD5);
		    //digitalWrite(BD_CLK,HIGH);
		    PORTD |= (1 << PD4);
		    if(count == 9) //digitalWrite(BD_DATA,HIGH);
		    				PORTD |= (1 << PD5);
		    //digitalWrite(BD_CLK,LOW);
		    PORTD &= ~(1 << PD4);
		   }
	//digitalWrite(BD_DATA,LOW);
	PORTD &= ~(1 << PD5);
}

