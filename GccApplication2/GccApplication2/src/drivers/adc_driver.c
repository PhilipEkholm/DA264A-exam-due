/*
 * adc_driver.c
 *
 * Created: 2018-03-12 06:53:15
 *  Author: Philip Ekholm, Aron Polner
 */

#include "adc_driver.h"

void adc_setup(void) {
	pmc_enable_periph_clk(ID_ADC);
	adc_init(ADC, sysclk_get_main_hz(), 20000000, 0);
	adc_configure_timing(ADC, 0, 0, 0);
	adc_set_resolution(ADC, ADC_MR_LOWRES_BITS_12);
	adc_enable_channel(ADC, ADC_CHANNEL_10);
	adc_configure_trigger(ADC, ADC_TRIG_SW, 0);
}

uint16_t adc_get_value(void) {
	adc_start(ADC);
	while((adc_get_status(ADC) & 0x1<<24)==0);  //Wait until DRDY get high
	
	/* Boost the value a little for better RMS-values */
	return ((adc_get_latest_value(ADC) * 106) / 100 );
}
