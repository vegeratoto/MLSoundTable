/*
 * mp3.c
 *
 * Created: 2017. 09. 06. 16:51:32
 *  Author: vegtamas
 */ 

#include "mp3.h"

uint8_t	mp3InitMsg[MP3_MSG_LENGTH] = {0x7E, 0xFF, 0x06, 0x3F, 0x00, 0x00, 0x02, 0,0 , 0xEF};		// init message from MP3 module with microSD on
uint8_t mp3SendBuff[MP3_MSG_LENGTH] = {0x7E, 0xFF};

uint8_t MP3WaitForInit()
{
	uint8_t buffer[MP3_MSG_LENGTH], i;
	
	for(i=0; i<MP3_MSG_LENGTH; i++)
		buffer[i] = uartGetByte();
	
	for(i=0; i<MP3_MSG_LENGTH; i++)
		if(buffer[i] != mp3InitMsg[i] && i!=7 && i!=8)
			break;
	
	if(i==MP3_MSG_LENGTH)
		return OK;
	else
		return FAIL;
}

uint16_t mp3GetChecksum () {
	uint16_t sum = 0;
	for (int i=1; i<7; i++) {
		sum += mp3SendBuff[i];
	}
	
	return -sum;
}

void mp3SendCmd(uint8_t cmd, uint16_t arg)
{
	uint16_t temp_sum, i;
	 
	mp3SendBuff[2] = MP3_MSG_LENGTH - 4;
	mp3SendBuff[3] = cmd;
	mp3SendBuff[4] = 0;
	mp3SendBuff[5] = arg>>8;
	mp3SendBuff[6] = (uint8_t)arg;
	
	temp_sum = mp3GetChecksum();
	mp3SendBuff[7] = temp_sum>>8;
	mp3SendBuff[8] = (uint8_t)temp_sum;
	mp3SendBuff[9] = 0xEF;
	
	for(i=0; i<MP3_MSG_LENGTH; i++)
		uartSendByte(mp3SendBuff[i]);
}