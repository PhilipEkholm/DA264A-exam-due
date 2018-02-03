/**
 * /file main.c
 * /author: Aron Polner, Philip Ekholm
 * /date 2018-02-02
 *
 */

#include <inttypes.h>
#include <stdio_serial.h>
#include <asf.h>

#include "drivers/consoleFunctions.h"
#include "drivers/DelayFunctions.h"

#include "drivers/LCDFunctions.h"
#include "drivers/lcdApplication.h"

int main(void)
{
	sysclk_init();	/* Insert system clock initialization code here (sysclk_init()). */
	board_init();

	delayInit();
	configureConsole();	/* Initialize the console UART used from within Atmel Studio*/
	lcdInit();
	lcdClearDisplay();
	
	lcdWrite4DigitNumber(1997);
	
	while(1){
		
	}
	
	return 0;
}
