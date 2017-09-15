/*
 * main.h
 *
 * Created: 2017. 09. 06. 17:09:45
 *  Author: vegtamas
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include "mp3.h"
#include "hw.h"
#include <avr/io.h>
#include <inttypes.h>
#include <avr/interrupt.h>

uint8_t switchState;

#define OK		1
#define FAIL	0

/*
	Simple delay.
	
	@param cnt
		delay rate
*/
void delay(uint16_t cnt);

//Returns the id of pushed button, started from top left with 1. If no button pushed returns 0xFF.
uint8_t checkButton();

int main(void);

#endif /* INCFILE1_H_ */