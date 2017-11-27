/*
 * BD3873FS.cpp
 *
 *  Created on: 21 нояб. 2017 г.
 *      Author: snibler
 */
#include "BD3873FS.h"

BD3873FS::BD3873FS(){
	addr_data_10bits = 0;
	last_vposition = 0;
	last_volume = VOL_A_mid;
	last_bposition = 0;
	last_bass = BASS_0dB;
	last_tposition = 0;
	last_treble = TREBLE_0dB;
	last_sposition = 0;
	last_iposition = 0;
	pinMode(BD_CLK, OUTPUT);
	pinMode(BD_DATA, OUTPUT);
	digitalWrite(BD_CLK, LOW);
	digitalWrite(BD_DATA, LOW);
}
void BD3873FS::BD3873FS_init(){
	addr_data_10bits = INPUT_B | INPUT_GAIN_18dB | SURR_OFF | INPUT_SURR_addr;
	BD3873FS::write_10bits_to_chip(addr_data_10bits);
	addr_data_10bits = VOL_A_87dB | VOL_B_0 | VOL_addr;
	BD3873FS::write_10bits_to_chip(addr_data_10bits);
	addr_data_10bits = BASS_0dB | TREBLE_0dB | BASS_TREBLE_addr;
	BD3873FS::write_10bits_to_chip(addr_data_10bits);
	addr_data_10bits = 0x03;
	BD3873FS::write_10bits_to_chip(addr_data_10bits);

	addr_data_10bits = VOL_A_mid | VOL_B_0 | VOL_addr;
	BD3873FS::write_10bits_to_chip(addr_data_10bits);
	addr_data_10bits = BASS_0dB | TREBLE_0dB | BASS_TREBLE_addr;
	BD3873FS::write_10bits_to_chip(addr_data_10bits);
}
void BD3873FS::input_control(int position){
	bool state;
	if(position > last_iposition) state = true;
		else if(position < last_iposition) state = false;
	if(state) addr_data_10bits = INPUT_A | INPUT_GAIN_18dB | SURR_OFF | INPUT_SURR_addr;
	else addr_data_10bits = INPUT_B | INPUT_GAIN_18dB | SURR_OFF | INPUT_SURR_addr;
	BD3873FS::write_10bits_to_chip(addr_data_10bits);
	addr_data_10bits = last_volume | VOL_addr;
	BD3873FS::write_10bits_to_chip(addr_data_10bits);
	last_iposition = position;
}
void BD3873FS::surr_control(int position){
	bool state;
	if(position > last_sposition) state = true;
		else if(position < last_sposition) state = false;
	if(state) addr_data_10bits = INPUT_B | INPUT_GAIN_18dB | SURR_ON | INPUT_SURR_addr;
	else addr_data_10bits = INPUT_B | INPUT_GAIN_18dB | SURR_OFF | INPUT_SURR_addr;
	BD3873FS::write_10bits_to_chip(addr_data_10bits);
	addr_data_10bits = last_volume | VOL_addr;
	BD3873FS::write_10bits_to_chip(addr_data_10bits);
	last_sposition = position;
}
void BD3873FS::volume_control(int position){
	if(position > last_vposition) volume_up();
	else if(position < last_vposition) volume_down();
	last_vposition = position;
	Serial.println(last_volume, HEX);
	Serial.println(last_bass, HEX);
	Serial.println(last_treble, HEX);
}
void BD3873FS::volume_up(){
	if(last_volume > 0){
		word volume = last_volume - VOL_A_step_1dB;
		addr_data_10bits = volume | VOL_addr;
		BD3873FS::write_10bits_to_chip(addr_data_10bits);
		last_volume = volume;
		} else _NOP();
}
void BD3873FS::volume_down(){
	if(last_volume < VOL_A_O_0dB){
		word volume = last_volume + VOL_A_step_1dB;
		addr_data_10bits = volume | VOL_addr;
		BD3873FS::write_10bits_to_chip(addr_data_10bits);
		last_volume = volume;
		} else _NOP();
}
void BD3873FS::bass_control(int position){
	if(position > last_bposition) bass_up();
		else if(position < last_bposition) bass_down();
		last_bposition = position;
		addr_data_10bits = last_volume | VOL_addr;
		BD3873FS::write_10bits_to_chip(addr_data_10bits);
		Serial.println(last_volume, HEX);
		Serial.println(last_bass, HEX);
		Serial.println(last_treble, HEX);
}
void BD3873FS::bass_up(){
	if(last_bass < BASS_14dB){
			word bass = last_bass + BASS_step_2dB;
			addr_data_10bits = bass | last_treble | BASS_TREBLE_addr;
			BD3873FS::write_10bits_to_chip(addr_data_10bits);
			last_bass = bass;
			} else _NOP();
}
void BD3873FS::bass_down(){
	if(last_bass > 0){
			word bass = last_bass - BASS_step_2dB;
			addr_data_10bits = bass | last_treble | BASS_TREBLE_addr;
			BD3873FS::write_10bits_to_chip(addr_data_10bits);
			last_bass = bass;
			} else _NOP();
}
void BD3873FS::treble_control(int position){
	if(position > last_tposition) treble_up();
		else if(position < last_tposition) treble_down();
		last_tposition = position;
		addr_data_10bits = last_volume | VOL_addr;
		BD3873FS::write_10bits_to_chip(addr_data_10bits);
		Serial.println(last_volume, HEX);
		Serial.println(last_bass, HEX);
		Serial.println(last_treble, HEX);
}
void BD3873FS::treble_up(){
	if(last_treble < TREBLE_12dB){
			word treble = last_treble + TREBLE_step_2dB;
			addr_data_10bits = last_bass | treble | BASS_TREBLE_addr;
			BD3873FS::write_10bits_to_chip(addr_data_10bits);
			last_treble = treble;
			} else _NOP();
}
void BD3873FS::treble_down(){
	if(last_treble > 0){
			word treble = last_treble - TREBLE_step_2dB;
			addr_data_10bits = last_bass | treble | BASS_TREBLE_addr;
			BD3873FS::write_10bits_to_chip(addr_data_10bits);
			last_treble = treble;
			} else _NOP();
}
void BD3873FS::write_10bits_to_chip(word data){
	for (byte count = 0; count < 10; count++)
		   {
		    if((data<<count)&0x200)
		    	digitalWrite(BD_DATA,HIGH);
		    else
		    	digitalWrite(BD_DATA,LOW);
		    digitalWrite(BD_CLK,HIGH);
		    if(count == 9) digitalWrite(BD_DATA,HIGH);
		    digitalWrite(BD_CLK,LOW);
		   }
	digitalWrite(BD_DATA,LOW);
}

