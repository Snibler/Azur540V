/*
 * PT6311.h
 *
 *  Created on: 9 окт. 2017 г.
 *      Author: snibler
 *
 */

#ifndef PT6311_H_
#define PT6311_H_

class PT6311 {
private:
	void initDisplay();
	void write(uint8_t data);
	uint8_t read();
	void end();
public:
	PT6311(uint8_t COMMAND);
	~PT6311();

};

#endif /* PT6311_H_ */
