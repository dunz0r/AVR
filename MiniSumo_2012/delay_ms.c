/*
 * File Name : delay_ms.c
 * Purpose : For longer delays
 * Creation Date : 26-08-2012
 * Last Modified : sön 26 aug 2012 08:18:18
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */
#include <util/delay.h>
#include "delay_ms.h"
void delay_ms(uint16_t ms)
{
	while (ms)
	{
		_delay_ms(1);
		ms--;
	}
}

