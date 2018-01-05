/*
 *	delay.c
 *
 *	Create small busy wait delays
 *
 *	Created: 2018-01-05 12:51:31
 *  Author: Philip Ekholm, Aron Polner, Uek
 */

#include <asf.h>

#include "delay.h"

err_code delay_init(void)		/* Initializes the timer used for delays */
{
	pmc_enable_periph_clk(ID_TC0);	/* power on the peripheral clock for timers */
	tc_init(TC0,0,0);				/* TC0, channel 0, TCLK1 och capturemode */
	tc_set_block_mode(TC0,0);
	tc_stop(TC0,0);					/* making sure the timer does not run  */
	
	return ERROR_OK;
}

err_code delay_us(uint32_t us)		/* A simple implementation for a delay in us (not calibrated) */
{
	tc_start(TC0,0);
	while (tc_read_cv(TC0,0) < us*42);
	tc_stop(TC0,0);
	
	return ERROR_OK;
}
