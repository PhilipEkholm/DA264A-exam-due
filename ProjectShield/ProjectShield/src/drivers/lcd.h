//
//  LCDFunctions.h
//
//  Ulrik Eklund 2015
//  Philip Ekholm, Aron Polner 2017
//


#ifndef LCDFunctions_h
#define LCDFunctions_h

#include "asf.h"
#include "error.h"

#define LCD_RS PIO_PC22_IDX
#define LCD_Enable PIO_PC21_IDX

#define LCD_D4 PIO_PC26_IDX
#define LCD_D5 PIO_PC25_IDX
#define LCD_D6 PIO_PC24_IDX
#define LCD_D7 PIO_PC23_IDX

#define PIOC_BASE_ADDRESS 0x400E1200U

#define LCD_mask_D4_D7 (0b1111<<23)

enum LCD_write_state {
	INSTRUCTION = 0,
	CHARACTER,
	NBR_OF_LCD_WRITE_STATE
};

int lcd_init(void);
err_code lcd_write(uint8_t byte, bool type);
err_code lcd_clear(void);
err_code lcd_write_number(int number, uint8_t digits);
err_code lcd_write_str(const char *string);

#endif
