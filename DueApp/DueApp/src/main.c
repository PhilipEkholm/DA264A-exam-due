/* 
 * main.c
 * 
 * Created: 2017-01-05 12:45
 * Author: Philip Ekholm, Aron Polner
*/

#include <asf.h>

#include "error.h"
#include "drivers/console.h"
#include "drivers/delay.h"

#include "common/pin_mapper.h"

int main (void)
{
	err_code result;

	/* Init system clock for the board */
	sysclk_init();
	board_init();

	/* Init serial */
	console_init();
	
	/* Init GPIO Handler */
	ioport_init();
	
	ioport_enable_pin(arduino_to_sam(13));
	ioport_set_pin_dir(arduino_to_sam(13), IOPORT_DIR_OUTPUT);
	
	result = delay_init();
	if (result != ERROR_OK)
		printf("[ERROR]: Failed to init delay, err code: %0x", result);
	
	while(true){
		ioport_set_pin_level(arduino_to_sam(13), HIGH);
		delay_us(500000);
		ioport_set_pin_level(arduino_to_sam(13), LOW);
		delay_us(500000);
	}
	
	return 0;
}
