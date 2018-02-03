//
//  LCDFunctions.c
//  Code to be used in task 1401c
//
//	Ulrik Eklund 2014
//  Philip Ekholm & Aron Polner 2017
//
//

#include <inttypes.h>
#include <asf.h>

#include "lcd.h"
#include "delay.h"	/* The sam3x8e microcontroller can write faster than the LCD controller can handle its inputs */

#define LCD_REG_ENTRY_MODE  0x06
#define LCD_REG_CURSOR_ON   0x0F
#define LCD_REG_DISPLAY_CLR 0x01

int lcd_init(void) {
	int all_ok=1;		/* at the beginning assume nothing works */
	
	/* At power on */
	ioport_set_pin_dir(LCD_RS, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(LCD_Enable, IOPORT_DIR_OUTPUT);
	ioport_set_port_dir(IOPORT_PIOC, LCD_mask_D4_D7, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LCD_Enable, LOW);
	delay_us(30000);		/* wait > 15 ms */
	ioport_set_pin_level(LCD_RS, LOW);
	
	/* Function set (interface is 8 bit long) */
	ioport_set_pin_level(LCD_D4, HIGH);
	ioport_set_pin_level(LCD_D5, HIGH);
	ioport_set_pin_level(LCD_D6, LOW);
	ioport_set_pin_level(LCD_D7, LOW);
	ioport_set_pin_level(LCD_Enable, HIGH);
	delay_us(1);		/* wait 1 us */
	ioport_set_pin_level(LCD_Enable, LOW);
	delay_us(4100);	/* wait for more than 4,1 ms */
	ioport_set_pin_level(LCD_D4, HIGH);
	ioport_set_pin_level(LCD_D5, HIGH);
	ioport_set_pin_level(LCD_D6, LOW);
	ioport_set_pin_level(LCD_D7, LOW);
	ioport_set_pin_level(LCD_Enable, HIGH);
	delay_us(1);	/* delay 1 us */
	ioport_set_pin_level(LCD_Enable, LOW);
	delay_us(100);	/* wait 100 us */
	ioport_set_pin_level(LCD_D4, HIGH);
	ioport_set_pin_level(LCD_D5, HIGH);
	ioport_set_pin_level(LCD_D6, LOW);
	ioport_set_pin_level(LCD_D7, LOW);
	ioport_set_pin_level(LCD_Enable, HIGH);
	delay_us(1);	/* wait 1 us */
	ioport_set_pin_level(LCD_Enable, LOW);		
	delay_us(100);	/* wait 100 us */
		
	/* Set display to 4-bit input */
	ioport_set_pin_level(LCD_D4, LOW);
	ioport_set_pin_level(LCD_D5, HIGH);
	ioport_set_pin_level(LCD_D6, LOW);
	ioport_set_pin_level(LCD_D7, LOW);
	ioport_set_pin_level(LCD_Enable, HIGH);
	delay_us(1);
	ioport_set_pin_level(LCD_Enable, LOW);
	delay_us(100);
	lcd_write(0b00101000, LOW);		/* Two rows, small font */
	lcd_write(0b00001000, LOW);		/* Display off */
	lcd_write(0b00000001, LOW);		/* Display clear */
	delay_us(3000);
	lcd_write(0b00000110, LOW);		/* Entry mode set: move cursor right, no display shift */
	lcd_write(0b00001111 ,LOW);		/* Display on, cursor on, blinking on */

	all_ok = 0;					/* simple return statement showing that the initialization of the LCD has completed */
	return all_ok;
}


err_code lcd_write(uint8_t byte, bool type)		/* writes a byte to the LCD display */
/*
 *	writes the byte (8 bits) to the LCD display as two consecutive 4 bits 
 *	type = 0 controls the display
 *	type = 1 writes the content of the byte (usually interpreted as ASCII-code) to the display
 */
{
	/* In it's infinite wisdom the shield has the data pins in mirrored order compared to the Due board */
	uint8_t mirror_pin[16]={0b0000,0b1000,0b0100,0b1100,0b0010,0b1010,0b0110,0b1110,0b0001,0b1001,0b0101,0b1101,0b0011,0b1011,0b0111,0b1111};
	uint32_t byte32;
	uint8_t byte_orig;
	uint8_t mirrored_output = 0;

	byte_orig = byte;

	/* write the first 4 bits to the shield. */
	byte = byte>>4;
	byte = mirror_pin[byte];
	byte32 = (uint32_t)byte << 23;
	mirrored_output = byte<<4;
	
	ioport_set_pin_level(LCD_RS, type); 
	ioport_set_port_level(IOPORT_PIOC, LCD_mask_D4_D7, byte32);
	ioport_set_pin_level(LCD_Enable, HIGH);
	delay_us(1);
	ioport_set_pin_level(LCD_Enable, LOW);
	
	delay_us(100);
	
	/* write the second 4 bits to the shield. */
	byte = byte_orig;
	byte = byte & 0x0f;
	byte = mirror_pin[byte];
	byte32 = (uint32_t)byte<<23;
	mirrored_output = mirrored_output + byte;

	ioport_set_port_level(IOPORT_PIOC, LCD_mask_D4_D7, byte32);
	ioport_set_pin_level(LCD_Enable, HIGH);
	delay_us(1);
	ioport_set_pin_level(LCD_Enable, LOW);
	delay_us(100);
	
	return ERROR_OK;
}

err_code lcd_clear(void){
	lcd_write(LCD_REG_ENTRY_MODE, LOW);		/* Entry mode set: move cursor right, no display shift */
	delay_us(100);
	lcd_write(LCD_REG_CURSOR_ON ,LOW);		/* Display on, cursor on, blinking on */
	lcd_write(LCD_REG_DISPLAY_CLR, LOW);     /* Clear display */

	delay_us(3000);
	
	return ERROR_OK;
}

err_code lcd_write_number(int number, uint8_t digits)
{
	char nbr_str[digits + 1];

	sprintf(nbr_str, "%d", number);
	lcd_write_str(nbr_str);
	
	return ERROR_OK;
}

err_code lcd_write_str(const char *string)
/* writes an ascii string up to 40 characters on the LCD display */
{
	while(*string != '\0'){
		lcd_write(*string, CHARACTER);
		string++;
		delay_us(100);
	};
	
	return ERROR_OK;
}
