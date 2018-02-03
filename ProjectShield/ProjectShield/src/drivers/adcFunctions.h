/*
 * adcFunctions.h
 *
 * Created: 2015-06-16 08:59:27
 *  Author: Philip Ekholm, Aron Polner
 */ 


#ifndef ADCFUNCTIONS_H_
#define ADCFUNCTIONS_H_

#include "error.h"

#define ADC_BASE_ADDRESS 0x400C0000U

#include <inttypes.h>

err_code analogInit(int pinNumber);
uint32_t analogRead(int pinNumber);

#endif /* ADCFUNCTIONS_H_ */