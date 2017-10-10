/*
 * PT6311.h
 *
 *  Created on: 9 окт. 2017 г.
 *      Author: snibler
 *
 */

#ifndef PT6311_H_
#define PT6311_H_

#include <stdint.h>

class PT6311 {
private:
	uint8_t data;
	void PT6311_write(uint8_t dat_com);
public:
	void PT6311_init();
	void PT6311_writeCommand(uint8_t command);
	void PT6311_writeData(uint8_t data);
	uint8_t PT6311_read();

};

#endif /* PT6311_H_ */
