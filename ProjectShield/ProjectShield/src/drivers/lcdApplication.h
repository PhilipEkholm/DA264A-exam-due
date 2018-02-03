/*
 * lcdApplication.h
 *
 * Created: 2015-09-10 08:46:16
 *  Author: Ulrik, Philip Ekholm, Aron Polner
 */ 

#ifndef LCDAPPLICATION_H_
#define LCDAPPLICATION_H_

#include "error.h"

err_code lcdWrite4DigitNumber(int number);
err_code lcdWriteAsciiString(const char *string);

#endif /* LCDAPPLICATION_H_ */