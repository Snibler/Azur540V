#include "PT6311.h"
#include "LV23002M.h"

PT6311 disp;
LV23002M radio;

char * toArray(word number);
char * numberArray = calloc(7, 1);
word Freq;

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
//	Serial.begin(9600);
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
}

void loop() {
	delay(200);
	disp.PT6311_readKey();

	if (disp.KeyData == FUNCTION){
		disp.Disk_Demo();
//		Serial.println(radio.IFcounterbin);
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
