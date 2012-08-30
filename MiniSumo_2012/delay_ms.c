/*
 * File Name : delay_ms.c
 * Purpose : For longer delays
 * Creation Date : 26-08-2012
 * Last Modified : tor 30 aug 2012 13:54:17
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */
#include "delay_ms.h"
void delay_ms(uint8_t ms)
{
	while (ms)
	{
		_delay_ms(1);
		ms--;
	}
}

