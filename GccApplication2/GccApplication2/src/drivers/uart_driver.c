/*
 * uart.c
 *
 * Created: 2018-02-20 20:07:46
 *  Author: Philip Ekholm, Aron Polner
 */

#include "asf.h"
#include "delay.h"
#include "uart_driver.h"

void uart0_init(void){
	/* Enable TX0 */
	UART->UART_CR |= (1 << 6);
	/* Set baudrate at 9600 (546) */
	UART->UART_BRGR = 546;
}

void uart0_write_char(unsigned char chr){
	while(!(UART->UART_SR & (1u<<1)));

	UART->UART_THR = chr;
}

void uart0_write_str(char* str){
	while (*str != '\0'){
		uart0_write_char(*str);
		str++;
		delay_ms(1);
	}
}
