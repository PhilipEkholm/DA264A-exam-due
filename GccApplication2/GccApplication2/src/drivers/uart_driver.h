/*
 * uart_driver.h
 *
 * Created: 2018-02-24 10:07:51
 *  Author: nilss, Philip Ekholm
 */ 

#pragma once

void uart0_init(void);
void uart0_transmit(unsigned char data);
void uart0_putString(char* StringPtr);
