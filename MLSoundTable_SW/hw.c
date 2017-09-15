/*
 * hw.c
 *
 * Created: 2017. 09. 06. 13:38:24
 *  Author: vegtamas
 */ 

#include "hw.h"

void uartInit()
{
	UBRRL = UBRR_VAL;
	UBRRH = (UBRR_VAL>>8);
	// async, 8 bit data, 0 parity, 1 stop
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
	UCSRB |= (1 << RXEN) | (1 << TXEN);
}

void hwInit()
{
	YELLOW_LED_DDR |= (1<<YELLOW_LED_PIN);		// yellow led port output
	RED_LED_DDR |=  (1<<RED_LED_PIN);			// red led port output
	
	SWITCH_PORT |= (1<<SWITCH_PIN);				// turn on internal pull-up resistor to toggle switch
	
	uartInit();

	ROW_DDR |= (1<<ROW0_PIN) | (1<<ROW1_PIN) | (1<<ROW2_PIN) | (1<<ROW3_PIN) | (1<<ROW4_PIN);					// rows are outputs
	ROW_PORT |= (1<<ROW0_PIN) | (1<<ROW1_PIN) | (1<<ROW2_PIN) | (1<<ROW3_PIN) | (1<<ROW4_PIN);					// and all rows have logic 1
	COL_PORT |= (1<<COL0_PIN) | (1<<COL1_PIN) | (1<<COL2_PIN) | (1<<COL3_PIN) | (1<<COL4_PIN) | (1<<COL5_PIN);	// columns are inputs with pull-up resistors
	
	// check toggle switch after init
	if(SWITCH_PINx & (1<<SWITCH_PIN))
	{
		switchState = 1;
		redLED(OFF);
		yellowLED(ON);
	}
	else
	{
		switchState = 0;
		redLED(ON);
		yellowLED(OFF);
	}
	
	// toggle switch connected to INT0 -> switchState will be set by interrupt
	// init interrupt
	GICR |= (1<<INT0);
	MCUCR |= (1<<ISC00);
	sei();
}

uint8_t uartGetByte()
{
	while(!(UCSRA & (1<<RXC)));
	return UDR;	
}

void uartSendByte(uint8_t data)
{
	while(!(UCSRA & (1<<UDRE)));
	UDR = data;	
}

void redLED(uint8_t state)
{
	if(state == ON)
		RED_LED_PORT |= (1<<RED_LED_PIN);
	else
		RED_LED_PORT &= ~(1<<RED_LED_PIN);
	
}

void yellowLED(uint8_t state)
{
	if(state == ON)
		YELLOW_LED_PORT |= (1<<YELLOW_LED_PIN);
	else
		YELLOW_LED_PORT &=~(1<<YELLOW_LED_PIN);
}

ISR(INT0_vect)
{
	if(SWITCH_PINx & (1<<SWITCH_PIN))
	{
		switchState = 1;
		redLED(OFF);
		yellowLED(ON);
	}
	else
	{
		switchState = 0;
		redLED(ON);
		yellowLED(OFF);
	}
}