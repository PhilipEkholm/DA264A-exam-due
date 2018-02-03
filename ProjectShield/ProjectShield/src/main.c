/**
 * /file main.c
 * /author: Aron Polner, Philip Ekholm
 * /date 2018-02-02
 *
 */

#include <inttypes.h>
#include <stdio_serial.h>
#include <asf.h>

#include "pin_mapper.h"

#include "drivers/serial.h"
#include "drivers/delay.h"
#include "drivers/lcd.h"

int main(void)
{
	sysclk_init();
	board_init();

	ioport_init();
	delay_init();
	serial_init();
	lcd_init();
	lcd_clear();
	
	ioport_enable_pin(arduino_to_sam(13));
	ioport_set_pin_dir(arduino_to_sam(13), IOPORT_DIR_OUTPUT);

	uint8_t counter = 0;
	
	while(1){
		lcd_clear();
		lcd_write_str("Power: ");
		lcd_write_number(counter++, 3);
		ioport_set_pin_level(arduino_to_sam(13), HIGH);
		
		delay_ms(500);
		
		ioport_set_pin_level(arduino_to_sam(13), LOW);
		
		delay_ms(500);
	}
	
	return 0;
}
