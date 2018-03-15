/*
 * usart_driver.h
 *
 * Created: 2018-02-24 11:03:28
 *  Author: Philip Ekholm
 */ 

#pragma once

void usart0_init(void);
void usart0_write_char(unsigned char chr);
void usart0_write_str(char* str);
