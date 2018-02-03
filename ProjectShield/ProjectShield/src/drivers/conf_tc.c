/*
 * conf_tc.c
 *
 * Created: 2013-12-10 08:37:41
 *  Author: Tommy
 */ 

#include <asf.h>
#include "conf_tc.h"

/* NOTE: Must change channel before use, otherwise conflicts with delay.c */

void configure_tc(void)
{
	/* Enable clock for Timer Counter 0 */
	pmc_enable_periph_clk(ID_TC0);

	/** Configure TC for a 10 kHz frequency and trigger on RC compare. */
	tc_init(TC0, 0, 0 | TC_CMR_CPCTRG);			//Timer_clock_1 - MCK/2 - 42 MHz
	tc_write_rc(TC0, 0, 4200);					//4200 corresponds to fs = 10 kHz

	/* Configure and enable interrupt on RC compare */
	NVIC_EnableIRQ((IRQn_Type) ID_TC0);
	tc_enable_interrupt(TC0, 0, TC_IER_CPCS);

	tc_start(TC0, 0);
}
