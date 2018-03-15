/*
 * uart_driver.h
 *
 * Created: 2018-02-24 10:07:51
 *  Author: Philip Ekholm, Aron Polner
 */ 

#pragma once

void uart0_init(void);
void uart0_write_char(unsigned char chr);
void uart0_write_str(char* str);

