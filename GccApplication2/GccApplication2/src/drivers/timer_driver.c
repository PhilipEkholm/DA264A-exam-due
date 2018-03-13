/*
 * timer_driver.c
 *
 * Created: 2018-03-12 09:47:20
 *  Author: Philip Ekholm, Aron Polner
 */ 

#include <asf.h>

#include "timer_driver.h"

/*
* Initialize the timer
*/

void timer_init(void)
{
	/* Configure PMC */
	pmc_enable_periph_clk(ID_TC0);

	/** Configure TC for a 10 kHz frequency and trigger on RC compare. */
	tc_init(TC0, 0, 0 | TC_CMR_CPCTRG);			//Timer_clock_1 - MCK/2 - 42 MHz
	tc_write_rc(TC0, 0, 7000);					//8400 corresponds to fs = 5 kHz

	/* Configure and enable interrupt on RC compare */
	NVIC_EnableIRQ((IRQn_Type) ID_TC0);
	tc_enable_interrupt(TC0, 0, TC_IER_CPCS);
	
	tc_start(TC0, 0);
}
