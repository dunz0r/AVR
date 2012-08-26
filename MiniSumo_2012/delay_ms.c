/*
 * File Name : delay_ms.c
 * Purpose : For longer delays
 * Creation Date : 26-08-2012
 * Last Modified : sön 26 aug 2012 16:11:22
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

void delay_ms(uint8_t ms)
{
	while (ms)
	{
		_delay_ms(1);
		ms--;
	}
}

