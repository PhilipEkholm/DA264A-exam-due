/*
 * delay.c
 * 
 * Author: Uek, Philip Ekholm
 */

#include "asf.h"
#include "delay.h"

int delay_init(void) {
	pmc_enable_periph_clk(ID_TC0);	/* power on the peripheral clock for timers */
	tc_init(TC0,0,0);				/* TC0, channel 0, TCLK1 och capturemode */
	tc_set_block_mode(TC0,0);
	tc_stop(TC0,0);					/* making sure the timer does not run  */
	return 0;						/* evertyhing is ok, typical response */
}

void delay_us(uint32_t us){
	tc_start(TC0,0);
	while (tc_read_cv(TC0,0) < us*42);
	tc_stop(TC0,0);
}

void delay_ms(uint32_t ms) {
	delay_us(1000 * ms);
}

void delay_s(uint32_t s) {
	delay_ms(1000 * s);
}