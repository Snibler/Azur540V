/*
 * BD3873FS.cpp
 *
 *  Created on: 21 нояб. 2017 г.
 *      Author: snibler
 */
#include "BD3873FS.h"

BD3873FS::BD3873FS(){
	addr_data_10bits = 0;
	pinMode(BD_CLK, OUTPUT);
	pinMode(BD_DATA, OUTPUT);
	digitalWrite(BD_CLK, LOW);
	digitalWrite(BD_DATA, LOW);
}
void BD3873FS::BD3873FS_init(){
	addr_data_10bits = INPUT_B | INPUT_GAIN_18dB | INPUT_SURR_addr;
	BD3873FS::write_10bits_to_chip(addr_data_10bits);
	addr_data_10bits = VOL_A_null | VOL_B_null | VOL_addr;
	BD3873FS::write_10bits_to_chip(addr_data_10bits);
	addr_data_10bits = BASS_0dB | TREBLE_0dB | BASS_TREBLE_addr;
	BD3873FS::write_10bits_to_chip(addr_data_10bits);
	addr_data_10bits = 0x03;
	BD3873FS::write_10bits_to_chip(addr_data_10bits);
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

