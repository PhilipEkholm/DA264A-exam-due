/*
 * usart_driver.c
 *
 * Created: 2018-02-24 11:03:11
 *  Author: Philip Ekholm
 */ 

#include "asf.h"
#include "delay.h"
#include "usart_driver.h"

#define TXEN0   6
#define CHRL1   7
#define CHRL0   6
#define USCLKS0 4
#define USCLKS1 5

/* Enable the USART0 (amazingly labeled as "RX1" and "TX1" on the board...) */
void usart0_init(void) {
	pmc_enable_periph_clk(ID_USART0);
	USART0->US_CR |= (1 << TXEN0); /* Enable the transmitter */
	USART0->US_MR |= (1 << CHRL1) | (1 << CHRL0); /* Send char length of 8 bits */
	USART0->US_MR &= ~((1 << USCLKS1) | (1 << USCLKS0)); /* Make sure we use the masterclock on 84 MHz */
	PIOA->PIO_PDR |= (PIO_PA10) | (PIO_PA11); /* In order for RX/TX1 to work we must disable the PIO for these pins */
	USART0->US_BRGR = 4375;	//Set baudrate(1200). (4375)
}

void usart0_write_char(unsigned char chr) {
	while(!((USART0->US_CSR) & (1u<<1)));

	USART0->US_THR = chr;
}

void usart0_write_str(char* str){
	while (*str != '\0'){
		usart0_write_char(*str);
		str++;
	}
}