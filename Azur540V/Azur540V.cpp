#include "PT6311.h"
#include "LV23002M.h"

PT6311 disp;
LV23002M radio;

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
	delay(500);
	Serial.println(radio.IFcounterbin);
	disp.PT6311_readKey();
	if (disp.KeyData == FUNCTION) _NOP();
	if (disp.KeyData == BAND) radio.autoscan();
	if (disp.KeyData == TUNING_M) radio.freq_m();
	if (disp.KeyData == TUNING_P) radio.freq_p();
	if (disp.KeyData == OPEN_CLOSE) _NOP();
	if (disp.KeyData == PLAYB){
		radio.playMEM();
		radio.readstatus();
		if(bit_is_clear(radio.indicators, 2)){
			TUNED = true;
			PLAY = true;
			MHz = true;
		}
		if(bit_is_clear(radio.indicators, 3)) ST = true;
		disp.Display_Write(" TUNER",sizeof(" TUNER")-1, dts,RDS,ST,DOLBY,TUNED,PLAY,FM,MHz,MEM,_3D,_2dp1,_2dp2,dp1,dp2);
	}
	if (disp.KeyData == STOP){
		radio.mute();
		ST = false;
		TUNED = false;
		PLAY = false;
		MHz = false;
		disp.Display_Write(" MUTE",sizeof(" MUTE")-1, dts,RDS,ST,DOLBY,TUNED,PLAY,FM,MHz,MEM,_3D,_2dp1,_2dp2,dp1,dp2);
	}


}
