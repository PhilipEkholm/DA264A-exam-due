/*
 * signal_process.h
 *
 * Created: 2018-03-12 09:39:32
 *  Author: Philip Ekholm, Aron Polner
 */ 

#pragma once

#define NUM_SAMPLES 100

int16_t* signal_process_get_samples(void);
int signal_process_get_sample_index(void);
void signal_process_reset_sample_index(void);
