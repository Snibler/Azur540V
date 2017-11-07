#include "PT6311.h"
#include "LV23002M.h"

unsigned char reverseByte(byte data);

PT6311 disp;
LV23002M radio;

#define startstr "FM TUNER"
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
	disp.Display_Write(startstr,sizeof(startstr)-1, dts,RDS,ST,DOLBY,TUNED,PLAY,FM,MHz,MEM,_3D,_2dp1,_2dp2,dp1,dp2);
//write to display test info
//	disp.Write_Display();
//init radio
	radio.LM23002M_init();
//write to radio 101.1FM "Радио Пятница"
//	radio.LV23002M_INmode(IN1mode,reverseByte(lowByte(2236)),reverseByte(highByte(2236)),0x40);
//	radio.LV23002M_INmode(IN2mode,0x57,0xA8,0x28);
//	do radio.LV23002M_OUTmode();
//		while (radio.OUTdata1 & (1 << 6));
//	radio.LV23002M_INmode(IN1mode,reverseByte(lowByte(2236)),reverseByte(highByte(2236)),0x60);
//	loop_until_bit_is_clear(PINB, 4);
//	delay(4);
//	radio.LV23002M_OUTmode();
//	delay(10000);
//write to radio 103.6FM "Радіо РОКС Україна"
//	radio.LV23002M_INmode(IN1mode,reverseByte(lowByte(2286)),reverseByte(highByte(2286)),0x40);
}

void loop() {

//	  disp.PT6311_readKey();
//	  delay(500);
//	  Serial.println(disp.KeyData);


}
unsigned char reverseByte(byte data){
	byte result = 0;
	for(byte i = 0;i < 8;i++){
		if (data & (1 << i))
			{
			result |= 1 << (7-i);
			}
	}
	return result;
}
