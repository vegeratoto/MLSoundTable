/*
 * main.c
 *
 * Created: 2017. 09. 06. 13:05:42
 * Author : vegtamas
 */ 

/*	No optimization is allowed.

MLSoundTable is a device playing MP3 files according to button pushes.
There is a table with 30 button (5 rows, 6 columns), a toggle switch and 2 feedback LEDs.
You can select the directory on microSD card with the toggle switch (in original application: select language) and see on LEDs which one is choosen.
If a button is pushed an MP3 is played.

Microcontroller: ATmega8 on 18.432 MHz, from externcal osc.
MP3 module: DFPlayer mini + 2gb microSD
Buttons: cheapest one from local store.

Bitcoin donate: 133Wqs53R3MZTyRyAz5LZp6QjPPyHwu6eH
*/

#include "main.h"

// create arrays from pins of rows and columns
uint8_t rowPins[NO_ROWS] = {ROW0_PIN, ROW1_PIN, ROW2_PIN, ROW3_PIN, ROW4_PIN};
uint8_t colPins[NO_COLS] = {COL0_PIN, COL1_PIN, COL2_PIN, COL3_PIN, COL4_PIN, COL5_PIN};
		
void delay(uint16_t cnt){
	uint16_t i;
	while(cnt--)
		for(i=1000; i; i--);
}

uint8_t checkButton()
{
	uint8_t rowCnt,colCnt, retVal;
	
	retVal = 0xFF;
	
	for(rowCnt=0; rowCnt<NO_ROWS; rowCnt++)
	{
		ROW_PORT &= ~(1<<rowPins[rowCnt]);					// given row switch to 0
		for(colCnt=0; colCnt<NO_COLS; colCnt++)
		{
			if((COL_PINx & (1<<colPins[colCnt])) == 0)		// check whether a button is pushed in the row
				retVal = (NO_COLS * rowCnt + colCnt + 1);		// if pushed, store the button id
		}
		ROW_PORT |= (1<<rowPins[rowCnt]);					// given row switch back to 1
	}
	return retVal;
}

int main(void)
{
	uint8_t button;
	
	hwInit();
    
	delay(2000);		// wait for MP3 module to init
	
	mp3SendCmd(CMD_SOURCE, SOURCE_TF);		// send source command to MP3, to play from microSD card

	while(1)
	{
		button = checkButton();

		if(button != 0xFF)
		{
			if(switchState)				// language selection from toggleSwitch
			{
				mp3SendCmd(CMD_FOLDER_PLAY, 0x200 + button);		// play MP3 from directory 02
				yellowLED(OFF);										// turn off yellow feedback LED
			}
			else
			{
				mp3SendCmd(CMD_FOLDER_PLAY, 0x100 + button);		// play MP3 from directory 01
				redLED(OFF);										// turn off red feedback LED
			}
			delay(200);												// not so pretty debouncing to buttons
			if(switchState)	yellowLED(ON);
			else redLED(ON);
		}	
	}
}

