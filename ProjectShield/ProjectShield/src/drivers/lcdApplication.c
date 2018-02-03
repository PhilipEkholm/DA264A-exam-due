/*
 * lcdApplication.c
 *
 * Created: 2015-09-10 08:44:50
 *  Author: Aron Polner, Philip Ekholm
 */ 

#include "lcdApplication.h"
#include "LCDFunctions.h"
#include "DelayFunctions.h"

err_code lcdWrite4DigitNumber(int number)
{
	char nbr_str[5];
	sprintf(nbr_str, "%d", number);
	lcdWriteAsciiString(nbr_str);
	
	return ERROR_OK;
}

err_code lcdWriteAsciiString(const char *string)
/* writes an ascii string up to 40 characters on the LCD display */
{
	while(*string != '\0'){
		lcdWrite(*string, CHARACTER);
		string++;
		delayMicroseconds(100);
	};
	
	return ERROR_OK;
}
