#include "PT6311.h"
#include "LV23002M.h"
#include "BD3873FS.h"
#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>

PT6311 disp;
LV23002M radio;
BD3873FS vol;
Encoder myEnc(3, 2);

char * toArray(word number);
char * numberArray = calloc(7, 1);
word Freq;
int position  = 0;
int newPosition;
unsigned long currentMillis;
unsigned long previousMillis = 0;
#define INTERVAL 3000
byte Function_switch = 0;

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

void setup() {
//init serial for debugging
	Serial.begin(9600);
//init display
	disp.PT6311_init();
	disp.Display_Write(" TUNER",sizeof(" TUNER")-1, dts,RDS,ST,DOLBY,TUNED,PLAY,FM,MHz,MEM,_3D,_2dp1,_2dp2,dp1,dp2);
	delay(2000);
//init radio
	radio.LM23002M_init();
	radio.mute();
	radio.MEMstationCurrent = EEPROM.read(0);
	radio.playST(radio.MEMstationCurrent);
	Freq = radio.FQcurrent-1070;
	disp.Display_Write(toArray(Freq),7, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
					MEM = true,_3D,_2dp1,_2dp2,dp1 = true,dp2);
//init volume controller
	vol.BD3873FS_init();
}

void loop() {
	delay(200);
//read buttons status
	disp.PT6311_readKey();
//return display current station after interval
	currentMillis = millis();
	if ((currentMillis - previousMillis) > INTERVAL){
		previousMillis = currentMillis;
		Freq = radio.FQcurrent-1070;
		disp.Display_Write(toArray(Freq),7, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
						MEM = true,_3D,_2dp1,_2dp2,dp1 = true,dp2);
	}
//Function_switch
	switch(Function_switch){
			case 0:
				//scan enconer position
					newPosition = myEnc.read();
					if(newPosition != position){
							position = newPosition;
							vol.volume_control(position);
							disp.Display_Write(vol.toArray("VOL"),7, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
											MEM = false,_3D,_2dp1,_2dp2,dp1 = false,dp2);
							previousMillis = millis();
							}
				break;
			case 1:
				disp.Display_Write("BAS",sizeof("BAS")-1, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
										MEM = false,_3D,_2dp1,_2dp2,dp1 = false,dp2);
				//scan enconer position
					newPosition = myEnc.read();
					if(newPosition != position){
							position = newPosition;
							vol.bass_control(position);
							disp.Display_Write("BAS",sizeof("BAS")-1, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
											MEM = false,_3D,_2dp1,_2dp2,dp1 = false,dp2);
				//			previousMillis = millis();
							}
				break;
			case 2:
				disp.Display_Write("TRE",sizeof("TRE")-1, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
											MEM = false,_3D,_2dp1,_2dp2,dp1 = false,dp2);
				//scan enconer position
					newPosition = myEnc.read();
					if(newPosition != position){
							position = newPosition;
							vol.treble_control(position);
							disp.Display_Write("TRE",sizeof("TRE")-1, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
											MEM = false,_3D,_2dp1,_2dp2,dp1 = false,dp2);
				//			previousMillis = millis();
							}
				break;
			case 3:
				disp.Display_Write("SUR",sizeof("SUR")-1, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
											MEM = false,_3D,_2dp1,_2dp2,dp1 = false,dp2);
				//scan enconer position
					newPosition = myEnc.read();
					if(newPosition != position){
							position = newPosition;
							vol.surr_control(position);
							disp.Display_Write("SUR",sizeof("SUR")-1, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
											MEM = false,_3D,_2dp1,_2dp2,dp1 = false,dp2);
				//			previousMillis = millis();
							}
				break;
			case 4:
				disp.Display_Write("AUX",sizeof("AUX")-1, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
											MEM = false,_3D,_2dp1,_2dp2,dp1 = false,dp2);
				newPosition = myEnc.read();
				if(newPosition != position){
						position = newPosition;
						vol.input_control(position);
						disp.Display_Write("AUX",sizeof("AUX")-1, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
										MEM = false,_3D,_2dp1,_2dp2,dp1 = false,dp2);
				//			previousMillis = millis();
				}
				break;
	}
//button functions
	if (disp.KeyData == FUNCTION){
		if(Function_switch < 4) Function_switch++;
		else Function_switch = 0;
		disp.Disk_Demo();

	}
	if (disp.KeyData == BAND){
		EEPROM.write(0, radio.MEMstationCurrent);
		disp.Disk_Demo();
	}
	if (disp.KeyData == TUNING_M){
		radio.freq_m();
		Freq = radio.FQcurrent-1070;
		disp.Display_Write(toArray(Freq),7, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
				MEM = false,_3D,_2dp1,_2dp2,dp1 = true,dp2);
	}
	if (disp.KeyData == TUNING_P){
		radio.freq_p();
		Freq = radio.FQcurrent-1070;
		disp.Display_Write(toArray(Freq),7, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
				MEM = false,_3D,_2dp1,_2dp2,dp1 = true,dp2);
	}
	if (disp.KeyData == OPEN_CLOSE){
		radio.writeMEM();
		Freq = radio.FQcurrent-1070;
		disp.Display_Write(toArray(Freq),7, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
				MEM = true,_3D,_2dp1,_2dp2,dp1 = true,dp2);
		disp.Disk_Demo();
	}
	if (disp.KeyData == PLAYB){
		radio.playMEM();
		Freq = radio.FQcurrent-1070;
		disp.Display_Write(toArray(Freq),7, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
				MEM = true,_3D,_2dp1,_2dp2,dp1 = true,dp2);
		disp.Disk_Demo();
	}
	if (disp.KeyData == STOP){
		radio.mute();
		disp.Display_Write(" MUTE",sizeof(" MUTE")-1, dts,RDS,ST = false,DOLBY,TUNED = false,PLAY = false,FM = true,MHz = true,
				MEM = false,_3D,_2dp1,_2dp2,dp1 = false,dp2);
		radio.MEMstationCurrent -= 1;
		disp.Disk_Demo();
	}
}

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
