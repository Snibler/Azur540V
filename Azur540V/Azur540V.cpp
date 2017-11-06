#include "PT6311.h"
#include "LV23002M.h"

unsigned char reverseByte(byte data);
PT6311 disp;
LV23002M radio;

void setup() {
//init serial for debugging
	Serial.begin(9600);
//init display
	disp.PT6311_init();
//init radio
	radio.LM23002M_init();
//write to display test info
	disp.Write_Display();
//write to radio 101.1FM "Радио Пятница"
	radio.LV23002M_INmode(IN1mode,reverseByte(lowByte(2236)),reverseByte(highByte(2236)),0x40);
	radio.LV23002M_INmode(IN2mode,0x57,0xA8,0x28);
	do radio.LV23002M_OUTmode();
		while (radio.OUTdata1 & (1 << 6));
	radio.LV23002M_INmode(IN1mode,reverseByte(lowByte(2236)),reverseByte(highByte(2236)),0x60);
	loop_until_bit_is_clear(PINB, 4);
	delay(4);
	radio.LV23002M_OUTmode();
	delay(10000);
//write to radio 103.6FM "Радіо РОКС Україна"
	radio.LV23002M_INmode(IN1mode,reverseByte(lowByte(2286)),reverseByte(highByte(2286)),0x40);
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
void loop() {

	  disp.Disk_Demo();

//print key status
//	  disp.PT6311_read();
//	  Serial.println(disp.data);
//	  delay(500);

	  Serial.println(radio.OUTdata1);
	  Serial.println(radio.OUTdata2);
	  Serial.println(radio.OUTdata3);

}
