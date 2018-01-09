#include "PT6311.h"
#include "LV23002M.h"
#include "BD3873FS.h"
#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>
#include <IRremote.h>
#include "IRremoteCodes.h"
#include "vars.h"

#define AMP_MUTE 6
#define RECV_PIN 7

PT6311 disp;
LV23002M radio;
BD3873FS vol;
Encoder myEnc(3, 2);
IRrecv irrecv(RECV_PIN);
decode_results results;



void setup() {
//Mute ON
	pinMode(AMP_MUTE, OUTPUT);
	digitalWrite(AMP_MUTE, HIGH);
//init display
	disp.PT6311_init();
	disp.Display_Write(" TUNER",sizeof(" TUNER")-1, dts,RDS,ST,DOLBY,TUNED,PLAY,FM,MHz,MEM,_3D,_2dp1,_2dp2,dp1,dp2);
	delay(2000);
//init radio and tune station from mem
	radio.LM23002M_init();
	radio.mute();
	radio.MEMstationCurrent = EEPROM.read(0);
	radio.playST(radio.MEMstationCurrent);
	Freq = radio.FQcurrent-1070;
	disp.Display_Write(toArray(Freq),7, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
					MEM = true,_3D,_2dp1,_2dp2,dp1 = true,dp2);
//init volume controller
	vol.BD3873FS_init();
//init the receiver
	irrecv.enableIRIn();
//Mute OFF
	digitalWrite(AMP_MUTE, LOW);
}

void loop() {
//if received ir code undefined, clear buffer
	if(irrecv.decode(&results)) ir_state = true;
	if (ir_state && results.value != VOL_UP_IR 	&& results.value != VOL_DOWN_IR && results.value != CH_UP_IR
			 	 && results.value != CH_DOWN_IR && results.value != MUTE_IR 	&& results.value != SOURCE_IR
				 && results.value != STEREO_SUR_IR){
		irrecv.resume();
		ir_state = false;
	}
	if (ir_state && vol.state_inp && (results.value == CH_UP_IR || results.value == CH_DOWN_IR)){
			irrecv.resume();
			ir_state = false;
	}
//read buttons status
	disp.PT6311_readKey();
//return display current station after interval
		currentMillis = millis();
	if ((currentMillis - previousMillis) > INTERVAL){
		previousMillis = currentMillis;
		if(mute_state) 	disp.Display_Write(" MUTE",sizeof(" MUTE")-1, dts,RDS,ST = false,DOLBY,TUNED = false,PLAY = false,FM = true,MHz = true,
						MEM = false,_3D,_2dp1,_2dp2,dp1 = false,dp2);
		else if(!vol.state_inp){
		Freq = radio.FQcurrent-1070;
		disp.Display_Write(toArray(Freq),7, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
						MEM = true,_3D,_2dp1,_2dp2,dp1 = true,dp2);
		} else disp.Display_Write(vol.toArray("AUX"),7, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
						MEM = false,_3D,_2dp1,_2dp2,dp1 = false,dp2);
	}
//Function_switch
	switch(FUNC){
			case VOLUME:
				//scan enconer position
					newPosition = myEnc.read();
					if(newPosition != position){
							position = newPosition;
							digitalWrite(AMP_MUTE, HIGH);
							vol.volume_control(position);
							disp.Display_Write(vol.toArray("VOL"),7, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
											MEM = false,_3D,_2dp1,_2dp2,dp1 = false,dp2);
							previousMillis = millis();
							digitalWrite(AMP_MUTE, LOW);
							}
				break;
			case BASS:
				disp.Display_Write(vol.toArray("BAS"),7, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
										MEM = false,_3D,_2dp1,_2dp2,dp1 = false,dp2);
				//scan enconer position
					newPosition = myEnc.read();
					if(newPosition != position){
							position = newPosition;
							digitalWrite(AMP_MUTE, HIGH);
							vol.bass_control(position);
							disp.Display_Write(vol.toArray("BAS"),7, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
											MEM = false,_3D,_2dp1,_2dp2,dp1 = false,dp2);
							digitalWrite(AMP_MUTE, LOW);
							}
				break;
			case TREBLE:
				disp.Display_Write(vol.toArray("TRE"),7, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
											MEM = false,_3D,_2dp1,_2dp2,dp1 = false,dp2);
				//scan enconer position
					newPosition = myEnc.read();
					if(newPosition != position){
							position = newPosition;
							digitalWrite(AMP_MUTE, HIGH);
							vol.treble_control(position);
							disp.Display_Write(vol.toArray("TRE"),7, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
											MEM = false,_3D,_2dp1,_2dp2,dp1 = false,dp2);
							digitalWrite(AMP_MUTE, LOW);
							}
				break;
			case SURROUND:
				disp.Display_Write(vol.toArray("SUR"),7, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
											MEM = false,_3D,_2dp1,_2dp2,dp1 = false,dp2);
				//scan enconer position
					newPosition = myEnc.read();
					if(newPosition != position){
							position = newPosition;
							digitalWrite(AMP_MUTE, HIGH);
							vol.surr_control(position);
							disp.Display_Write(vol.toArray("SUR"),7, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
											MEM = false,_3D,_2dp1,_2dp2,dp1 = false,dp2);
							digitalWrite(AMP_MUTE, LOW);
							}
				break;
			case AUX:
				disp.Display_Write(vol.toArray("AUX"),7, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
											MEM = false,_3D,_2dp1,_2dp2,dp1 = false,dp2);
				//scan enconer position
				newPosition = myEnc.read();
				if(newPosition != position){
						position = newPosition;
						digitalWrite(AMP_MUTE, HIGH);
						vol.input_control(position);
						disp.Display_Write(vol.toArray("AUX"),7, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
										MEM = false,_3D,_2dp1,_2dp2,dp1 = false,dp2);
						digitalWrite(AMP_MUTE, LOW);
				}
				break;
	}
//if button code received
if(disp.KeyData != 0){
	if (disp.KeyData == FUNCTION){
		if(FUNC < AUX) FUNC++;
		else FUNC = VOLUME;
		disp.Disk_Demo();

	} else
	if (disp.KeyData == BAND && !vol.state_inp){
		EEPROM.write(0, radio.MEMstationCurrent);
		disp.Disk_Demo();
	} else
	if (disp.KeyData == TUNING_M && !vol.state_inp){
		radio.freq_m();
		Freq = radio.FQcurrent-1070;
		disp.Display_Write(toArray(Freq),7, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
				MEM = false,_3D,_2dp1,_2dp2,dp1 = true,dp2);
	} else
	if (disp.KeyData == TUNING_P && !vol.state_inp){
		radio.freq_p();
		Freq = radio.FQcurrent-1070;
		disp.Display_Write(toArray(Freq),7, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
				MEM = false,_3D,_2dp1,_2dp2,dp1 = true,dp2);
	} else
	if (disp.KeyData == OPEN_CLOSE && !vol.state_inp){
		radio.writeMEM();
		Freq = radio.FQcurrent-1070;
		disp.Display_Write(toArray(Freq),7, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
				MEM = true,_3D,_2dp1,_2dp2,dp1 = true,dp2);
		disp.Disk_Demo();
	} else
	if (disp.KeyData == PLAYB && !vol.state_inp){
		radio.playMEM_plus();
		Freq = radio.FQcurrent-1070;
		disp.Display_Write(toArray(Freq),7, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
				MEM = true,_3D,_2dp1,_2dp2,dp1 = true,dp2);
		disp.Disk_Demo();
	} else
	if (disp.KeyData == STOP){
			irrecv.resume();
			ir_state = false;
			if (mute_state){
				mute_state = false;
				radio.playMEM();
				Freq = radio.FQcurrent-1070;
				disp.Display_Write(toArray(Freq),7, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
								MEM = true,_3D,_2dp1,_2dp2,dp1 = true,dp2);
				digitalWrite(AMP_MUTE, LOW);
			}
			else {
				digitalWrite(AMP_MUTE, HIGH);
				mute_state = true;
				disp.Display_Write(" MUTE",sizeof(" MUTE")-1, dts,RDS,ST = false,DOLBY,TUNED = false,PLAY = false,FM = true,MHz = true,
								MEM = false,_3D,_2dp1,_2dp2,dp1 = false,dp2);
			}
			previousMillis = millis();
			disp.Disk_Demo();
		}
}
//if ir command received
if (ir_state){
	if (results.value == CH_UP_IR && !vol.state_inp){
		irrecv.resume();
		ir_state = false;
		radio.playMEM_plus();
		Freq = radio.FQcurrent-1070;
		disp.Display_Write(toArray(Freq),7, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
				MEM = true,_3D,_2dp1,_2dp2,dp1 = true,dp2);
		disp.Disk_Demo();
	} else
	if (results.value == CH_DOWN_IR && !vol.state_inp){
		irrecv.resume();
		ir_state = false;
		radio.playMEM_minus();
		Freq = radio.FQcurrent-1070;
		disp.Display_Write(toArray(Freq),7, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
				MEM = true,_3D,_2dp1,_2dp2,dp1 = true,dp2);
		disp.Disk_Demo();
	} else
	if (results.value == VOL_UP_IR){
		irrecv.resume();
		ir_state = false;
		position_ir ++;
		digitalWrite(AMP_MUTE, HIGH);
		vol.volume_control(position_ir);
		disp.Display_Write(vol.toArray("VOL"),7, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
							MEM = false,_3D,_2dp1,_2dp2,dp1 = false,dp2);
		digitalWrite(AMP_MUTE, LOW);
		disp.Disk_Demo();
	} else
	if (results.value == VOL_DOWN_IR){
		irrecv.resume();
		ir_state = false;
		position_ir --;
		digitalWrite(AMP_MUTE, HIGH);
		vol.volume_control(position_ir);
		disp.Display_Write(vol.toArray("VOL"),7, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
							MEM = false,_3D,_2dp1,_2dp2,dp1 = false,dp2);
		digitalWrite(AMP_MUTE, LOW);
		disp.Disk_Demo();
	} else
	if (results.value == STEREO_SUR_IR){
		irrecv.resume();
		ir_state = false;
		if(!surr_state) {
			position_ir ++;
			surr_state = true;
		}
		else {
			position_ir --;
			surr_state = false;
		}
		digitalWrite(AMP_MUTE, HIGH);
		vol.surr_control(position_ir);
		disp.Display_Write(vol.toArray("SUR"),7, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
							MEM = false,_3D,_2dp1,_2dp2,dp1 = false,dp2);
		previousMillis = millis();
		digitalWrite(AMP_MUTE, LOW);
		disp.Disk_Demo();
	} else
	if (results.value == SOURCE_IR){
		irrecv.resume();
		ir_state = false;
		if(!source_state) {
					position_ir ++;
					source_state = true;
				}
				else {
					position_ir --;
					source_state = false;
				}
		digitalWrite(AMP_MUTE, HIGH);
		vol.input_control(position_ir);
		disp.Display_Write(vol.toArray("AUX"),7, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
							MEM = false,_3D,_2dp1,_2dp2,dp1 = false,dp2);
		previousMillis = millis();
		digitalWrite(AMP_MUTE, LOW);
		disp.Disk_Demo();
	} else
	if (results.value == MUTE_IR){
				irrecv.resume();
				ir_state = false;
				if (mute_state){
					mute_state = false;
					radio.playMEM();
					Freq = radio.FQcurrent-1070;
					disp.Display_Write(toArray(Freq),7, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
									MEM = true,_3D,_2dp1,_2dp2,dp1 = true,dp2);
					digitalWrite(AMP_MUTE, LOW);
				}
				else {
					digitalWrite(AMP_MUTE, HIGH);
					mute_state = true;
					disp.Display_Write(" MUTE",sizeof(" MUTE")-1, dts,RDS,ST = false,DOLBY,TUNED = false,PLAY = false,FM = true,MHz = true,
									MEM = false,_3D,_2dp1,_2dp2,dp1 = false,dp2);
				}
				previousMillis = millis();
				disp.Disk_Demo();
			}
}
}	//end of loop()

//number to char array converter
char * toArray(word number)
    {
		numberArray[0] = 0;
        for (byte i = 0; i < 7; i++){
            if(i <= 4 && number != 0){
            	numberArray[4-i] = number % 10 + 48;
            	number /= 10;
            }
            else numberArray[i] = 0;
        }
        if(numberArray[0] == 48) numberArray[0] = 0;
        if(numberArray[4] == 0) numberArray[4] = 48;
        return numberArray;
    }
