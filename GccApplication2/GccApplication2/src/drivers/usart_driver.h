/*
 * usart_driver.h
 *
 * Created: 2018-02-24 11:03:28
 *  Author: Philip Ekholm
 */ 

#pragma once

void usart0_init(void);
void usart0_transmit(unsigned char data);
void usart0_putString(char* StringPtr);
