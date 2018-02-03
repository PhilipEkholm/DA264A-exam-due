/*
 * error.h
 *
 * Created: 2017-11-22 19:34:05
 *  Author: Philip Ekholm, Aron Polner
 */ 

#include <stdint.h>

typedef uint32_t err_code;

#define ERROR_OK           0
#define ERROR_BASE         0x80000000