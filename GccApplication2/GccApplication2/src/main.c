#include <sam3x8e.h>
#include <asf.h>

#include <fastmath.h>

#include "drivers/delay.h"
#include "drivers/uart_driver.h"
#include "drivers/usart_driver.h"
#include "drivers/adc_driver.h"
#include "drivers/dac_driver.h"
#include "drivers/timer_driver.h"

#include "pin_mapper.h"
#include "signal_process.h"

double calculate_rms(int16_t n[], uint16_t length){
	double rms = 0;

	for (int i = 0; i < length; ++i) {
		rms += (n[i] * n[i]);
	}

	rms /= length;

	return (sqrt(rms) / 1000);
}

int main (void)
{
	sysclk_init();
	board_init();

	ioport_init();
	delay_init();
	uart0_init();
	usart0_init();
	adc_setup();
	dac_setup();
	timer_init();

	char	str1[5],
			str2[5];
	double v_eff;
	int16_t *p_samples;
	uint16_t power_mW;
	double resistance = 10;
	
	ioport_enable_pin(pin_mapper(13));
	ioport_set_pin_dir(pin_mapper(13), IOPORT_DIR_OUTPUT);

	while(1) {
		/* Got enough samples? calculate RMS */
		if (signal_process_get_sample_index() >= NUM_SAMPLES) {
			/* Stop the timer to collect samples */
			tc_stop(TC0, 0);

			p_samples = signal_process_get_samples();
			v_eff = calculate_rms(p_samples, NUM_SAMPLES);
			
			power_mW = round(1000 * ((v_eff * v_eff) / resistance));
			
			/* Make sure we don't print out a too big value */
			if (power_mW >= 100) {
				power_mW = 99;
			}
			else if (power_mW <= 10) {
				power_mW = 11;
			}
			
			sprintf(str1, "%d\n", power_mW);
			sprintf(str2, "-%d", power_mW);
			
			uart0_write_str(str1);
			usart0_putString(str2);
			
			/* Reset the index and then start timer for another round */
			signal_process_reset_sample_index();
			tc_start(TC0, 0);
		}
	}
}
