/*
 * dac_driver.c
 *
 * Created: 2018-03-13 08:26:07
 *  Author: Philip Ekholm, Aron Polner
 */ 

#include <asf.h>

#include "dac_driver.h"

void dac_setup() {
	pmc_enable_periph_clk(ID_DACC);
	dacc_reset(DACC);
	dacc_set_transfer_mode(DACC, 0);
	dacc_set_timing(DACC,1,1,0);			//1 is shortest refresh period, 1 max. speed, 0 startup time
	
	dacc_set_channel_selection(DACC,0);		//Channel DAC0
	dacc_enable_channel(DACC, 0);			//enable DAC0
}