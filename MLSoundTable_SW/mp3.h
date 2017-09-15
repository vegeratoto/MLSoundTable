/*
 * mp3.h
 *
 * Created: 2017. 09. 06. 16:51:46
 *  Author: vegtamas
 */ 


#ifndef MP3_H_
#define MP3_H_

#include "main.h"
#include <inttypes.h>

// DFPlayer mini commands
#define CMD_TRACK			0x03
#define CMD_FOLDER_PLAY		0x0F
#define CMD_SOURCE			0x09

#define SOURCE_TF		0x01
#define SOURCE_AUX		0x02
#define SOURCE_SLEEP	0x03
#define SOURCE_FLASH	0x04 

#define MP3_MSG_LENGTH	10

/*
	Blocking function. Waits for MP3 module initialization. Not used in the application.
*/
uint8_t MP3WaitForInit();

/*
	Return the checkSum of mp3SendBuff array.
*/
uint16_t mp3GetChecksum ();

/*
	Sends command to the MP3 module.
	@param cmd
		Command from above.
	@param arg
		Argumentum of the command. Check datasheet.
*/
void mp3SendCmd(uint8_t cmd, uint16_t arg);

#endif /* INCFILE1_H_ */