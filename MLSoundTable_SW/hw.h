/*
 * hw.h
 *
 * Created: 2017. 09. 06. 13:12:22
 *  Author: vegtamas
 */ 


#ifndef HW_H_
#define HW_H_

#include "main.h"
#include <inttypes.h>
#include <avr/interrupt.h>

// calculate register values according to baud rate and cpu freq
#define F_CPU			18432000UL
#define USART_BAUDRATE	9600
#define UBRR_VAL		((F_CPU / (USART_BAUDRATE * 16UL)) - 1) // UBRR

#define ON	1
#define OFF	0
#define MP3_BUSY_DDR	DDRB
#define MP3_BUSY_PORT	PORTB
#define MP3_BUSY_PIN	PINB0

#define YELLOW_LED_DDR	DDRB
#define YELLOW_LED_PORT	PORTB
#define YELLOW_LED_PIN	PINB1

#define RED_LED_DDR		DDRB
#define RED_LED_PORT	PORTB
#define RED_LED_PIN		PINB2

// don't change, it's on INT0 pin
#define SWITCH_DDR		DDRD
#define SWITCH_PORT		PORTD
#define SWITCH_PINx		PIND
#define SWITCH_PIN		PIND2

#define ROW_DDR			DDRD
#define ROW_PORT		PORTD
#define ROW0_PIN		PIND3
#define ROW1_PIN		PIND4
#define ROW2_PIN		PIND5
#define ROW3_PIN		PIND6
#define ROW4_PIN		PIND7

#define NO_ROWS			5

#define COL_DDR			DDRC
#define COL_PORT		PORTC
#define COL_PINx		PINC
#define COL0_PIN		PINC0
#define COL1_PIN		PINC1
#define COL2_PIN		PINC2
#define COL3_PIN		PINC3
#define COL4_PIN		PINC4
#define COL5_PIN		PINC5

#define NO_COLS			6

//Init UART hardware
void uartInit();

//Init all of the hardware parts
void hwInit();

// Simple UART read function. Not used.
uint8_t uartGetByte();

/*
	Blocking byte sending on UART
	
	@param data
		data to send, 1 byte
*/
void uartSendByte(uint8_t data);

/*
	Turn on-off red feedback LED.
	@param state
		ON, OFF
*/
void redLED(uint8_t state);

/*
	Turn on-off yellow feedback LED.
	@param state
		ON, OFF
*/
void yellowLED(uint8_t state);

/*
	Toggle switch interaction handler with interrupt.
	Set the switchState global variable.
*/
ISR(INT0_vect);

#endif /* INCFILE1_H_ */