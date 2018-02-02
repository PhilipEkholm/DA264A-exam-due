/*
 *	console.c
 *
 *	Created: 2018-01-05 12:35:09
 *  Author: Philip Ekholm, Aron Polner
 */ 

#include <stdio_serial.h>
#include <asf.h>

#include "conf_board.h"
#include "drivers/console.h"

void console_init(void) {
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
		.paritytype = CONF_UART_PARITY
	};

	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);

	printf("Console initialized, running at %d baud\n", CONF_UART_BAUDRATE);
}
