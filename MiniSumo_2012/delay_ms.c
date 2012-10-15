/*
 * File Name : delay_ms.c
 * Purpose : For longer delays
 * Creation Date : 26-08-2012
 * Last Modified : mån 15 okt 2012 01:58:38
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */
#include "delay_ms.h"
void delay_ms(uint16_t ms)
{
	while (ms)
	{
		_delay_ms(1);
		ms--;
	}
}

