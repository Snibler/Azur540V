/*
 * vars.h
 *
 *  Created on: 9 янв. 2018 г.
 *      Author: snibler
 */

#ifndef VARS_H_
#define VARS_H_

char * toArray(word number);
char * numberArray = calloc(7, 1);
word Freq;
int position  = 0;
int position_ir = 0;
int newPosition;
unsigned long currentMillis;
unsigned long previousMillis = 0;
#define INTERVAL 3000
enum Function_switch {VOLUME, BASS, TREBLE, SURROUND, AUX};
bool mute_state = false;
bool surr_state = false;
bool source_state = false;
bool ir_state = false;
bool dts 	= false;
bool RDS 	= false;
bool ST 	= false;
bool DOLBY 	= false;
bool TUNED 	= false;
bool PLAY 	= false;
bool FM 	= false;
bool MHz 	= false;
bool MEM 	= false;
bool _3D 	= false;
bool _2dp1	= false;
bool _2dp2	= false;
bool dp1	= false;
bool dp2	= false;

byte FUNC = VOLUME;

#endif /* VARS_H_ */
