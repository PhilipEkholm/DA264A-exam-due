/*
 * signal_process.c
 *
 * Created: 2018-03-12 09:39:09
 *  Author: Philip Ekholm, Aron Polner
 */ 

#include <asf.h>

#include "signal_process.h"
#include "pin_mapper.h"
#include "drivers/adc_driver.h"

#define M             (50)
#define N             (4)
#define OFFSET_BUFFER (100)

static float xbuff[M + 1] = {0};
static float b[M + 1] = {
	0.002495668972398,-0.009326922325103, -0.01476885685777, -0.01468523807431,
	-0.005622447310856, 0.006582241110136,  0.01136102621987, 0.003636260467154,
	-0.00959023354916, -0.01438845972228,-0.003696436885928,  0.01356159997785,
	0.01915012680466, 0.003997453556677,  -0.0195229237472, -0.02647079708566,
	-0.004322365285215,  0.02963600868821,  0.03933098214157, 0.004587438733058,
	-0.0511354182298, -0.06992882304453,-0.004757015587571,   0.1347647696317,
	0.2777402748565,    0.338162287221,   0.2777402748565,   0.1347647696317,
	-0.004757015587571, -0.06992882304453,  -0.0511354182298, 0.004587438733058,
	0.03933098214157,  0.02963600868821,-0.004322365285215, -0.02647079708566,
	-0.0195229237472, 0.003997453556677,  0.01915012680466,  0.01356159997785,
	-0.003696436885928, -0.01438845972228, -0.00959023354916, 0.003636260467154,
	0.01136102621987, 0.006582241110136,-0.005622447310856, -0.01468523807431,
	-0.01476885685777,-0.009326922325103, 0.002495668972398
	}; /* FIR */

static int16_t samples[NUM_SAMPLES] = { 0 };
static int sample_index = 0;

static uint32_t dc_offset_buffer[OFFSET_BUFFER] = { 0 };
static uint16_t offset_index = 0;
static uint32_t dc_offset = 0;

static int16_t signal_process_convert_mv(int32_t raw_value) {
	return ((raw_value * 1000) / 1240);
}

void TC0_Handler(void) {
	ioport_set_pin_level(pin_mapper(13), 1);
	volatile uint32_t ul_dummy;
	uint32_t invalue, outvalue;
	float sum = 0;

	/* Clear status bit to acknowledge interrupt, otherwise interrupt will just loop */
	ul_dummy = tc_get_status(TC0, 0);	//The compare bit is cleared by reading the register, manual p. 915
	/* Avoid compiler warning */
	UNUSED(ul_dummy);
	
	/* Move all old values */
	for (int k = M - 1; k >= 0; k--) {
		xbuff[k + 1] = xbuff[k];
	}
	
	invalue = adc_get_value();
	xbuff[0] = (float)invalue;
	
	/* Apply the FIR-filter */
	for (uint8_t k = 0; k < M + 1; ++k) {
		sum += xbuff[k] * b[k];
	}
	
	outvalue = (uint32_t)sum;
	
	/* Keep saving signal values until we have enough */
	if (offset_index <= OFFSET_BUFFER) {
		dc_offset_buffer[offset_index++] = outvalue;
	}
	/* Have enough? calculate a new DC-offset */
	else {
		uint32_t signal_sum = 0;
		
		for (int i = 0; i < OFFSET_BUFFER; ++i) {
			signal_sum += dc_offset_buffer[i];
		}
		
		dc_offset = signal_sum / OFFSET_BUFFER;
		offset_index = 0;
	}
	
	if (sample_index < 100) {
		samples[sample_index++] = signal_process_convert_mv(outvalue - dc_offset);
	}

	ioport_set_pin_level(pin_mapper(13), 0);
}

/* Take the arg and set reference to the samples */
int16_t* signal_process_get_samples(void) {
	return samples;
}

int signal_process_get_sample_index(void) {
	return sample_index;
}

void signal_process_reset_sample_index(void) {
	sample_index = 0;
}