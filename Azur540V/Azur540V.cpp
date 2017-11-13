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
//init radio
	radio.LM23002M_init();
//write to radio 101.1FM "Радио Пятница"
//	radio.LV23002M_INmode(IN1mode,reverseByte(lowByte(2236)),reverseByte(highByte(2236)),0x40);
//	radio.LV23002M_INmode(IN2mode,0x57,0xA8,0x28);

//	delay(10000);
//write to radio 103.6FM "Радіо РОКС Україна"
//	radio.LV23002M_INmode(IN1mode,reverseByte(lowByte(2286)),reverseByte(highByte(2286)),0x40);
}

void loop() {
	delay(100);
//	Serial.println(radio.IFcounterbin);
	disp.PT6311_readKey();
	if (disp.KeyData == FUNCTION){
		_NOP();
	}
	if (disp.KeyData == BAND){
		//radio.autoscan();
		_NOP();
	}
	if (disp.KeyData == TUNING_M){
		radio.freq_m();
		Freq = radio.FQcurrent-1070;
		disp.Display_Write(toArray(Freq),7, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,MEM = false,_3D,_2dp1,_2dp2,dp1 = true,dp2);
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
	}
	if (disp.KeyData == PLAYB){
		radio.playMEM();
		Freq = radio.FQcurrent-1070;
		disp.Display_Write(toArray(Freq),7, dts,RDS,ST = true,DOLBY,TUNED = true,PLAY = true,FM = true,MHz = true,
				MEM = true,_3D,_2dp1,_2dp2,dp1 = true,dp2);
	}
	if (disp.KeyData == STOP){
		radio.mute();
		ST = false;
		TUNED = false;
		PLAY = false;
		MEM = false;
		dp1 = false;
		disp.Display_Write(" MUTE",sizeof(" MUTE")-1, dts,RDS,ST,DOLBY,TUNED,PLAY,FM,MHz,MEM,_3D,_2dp1,_2dp2,dp1,dp2);
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
