/*
 * adcFunctions.c
 *
 * Created: 2015-06-16 09:00:18
 *  Author: Philip Ekholm, Aron Polner
 */ 

#include <inttypes.h>
#include <asf.h>

#include "adcFunctions.h"

#define ADC_CLOCK       1000000 /* 1MHz */

#define ADC_START_TIME  8
#define ADC_AUTOTRIG_EN 1

/* Converting pinNumbers to SAM ADC-channel */

static const uint8_t arduino_sam_adc_pin_mapping[] = {
	ADC_CHANNEL_7,
	ADC_CHANNEL_6,
	ADC_CHANNEL_5,
	ADC_CHANNEL_4,
	ADC_CHANNEL_3,
	ADC_CHANNEL_2,
	ADC_CHANNEL_1,
	ADC_CHANNEL_0,
	ADC_CHANNEL_10,
	ADC_CHANNEL_11,
	ADC_CHANNEL_12,
	ADC_CHANNEL_13,
};

err_code analogInit(int pinNumber)
{
	uint32_t res;
	/* 
	 * The pin number is the analog input pin on the DUe board, see http://www.arduino.cc/en/Hacking/PinMappingSAM3X
	 * Obviously it starts at analog 0 which is equivalent to the analog input on PA16
	 * so you need to figure out which AD channel this corresponds to
	 *
	 * See code example http://asf.atmel.com/docs/latest/sam.drivers.adc.adc_example.arduino_due_x/html/sam_adc_quickstart.html
	 * It is assumed that the AD-converter is using 12 bits
	 */
	
	pmc_enable_periph_clk(ID_ADC);	/* power the clock for the ADC with pmc_enable_periph_clk(ID_ADC) */
	
	res = adc_init(ADC, sysclk_get_main_hz(), ADC_CLOCK, ADC_START_TIME); 
	
	if (res != ERROR_OK)
		printf("Failed to init ADC");
		
	adc_configure_timing(ADC, 0, ADC_SETTLING_TIME_3, 1); 
	/* Set 12-bit resolution */
	adc_set_resolution(ADC, ADC_MR_LOWRES_BITS_12);
	/* Enable selected channel */
	adc_enable_channel(ADC, arduino_sam_adc_pin_mapping[0]);
	/* Enable interrupt for ADC */
	adc_enable_interrupt(ADC, ADC_IER_DRDY);
	/* Enable software trigger and autotrigger */ 
	adc_configure_trigger(ADC, ADC_TRIG_SW, ADC_AUTOTRIG_EN);
	
	return ERROR_OK;
}

uint32_t analogRead(int pinNumber)
{	
	uint32_t button_code = 0;

	//Check the ADC conversion status
	if ((adc_get_status(ADC) & ADC_ISR_DRDY) == ADC_ISR_DRDY)
		//Get latest digital data value from ADC and can be used by application
		button_code = adc_get_channel_value(ADC, arduino_sam_adc_pin_mapping[0]);

	return button_code;
}