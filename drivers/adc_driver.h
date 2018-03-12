/*
 * adc_driver.h
 *
 * Created: 2018-03-12 06:54:05
 *  Author: Philip Ekholm, Aron Polner
 */ 

#pragma once

#include <asf.h>

void adc_setup(void);
uint16_t adc_get_value(void);
uint16_t adc_get_value_mv(void);
