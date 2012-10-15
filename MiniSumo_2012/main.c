/*
 * File Name : main.c
 * Purpose : Defeat everything
 * Creation Date : 26-08-2012
 * Last Modified : mån 15 okt 2012 01:58:10
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */
/*{{{ Includes */
#include <avr/interrupt.h>
#include "adc.h"
#include "delay_ms.h"
#include "macros.h"
#include "timers.h"
#include "usart.h"
/*}}}*/
/*{{{ Defines */
#define LED 5,B
#define LED2 6,D
/*}}}*/
/*{{{ Main function */
//set stream pointer
FILE usart0_str = FDEV_SETUP_STREAM(usart0_sendbyte, NULL, _FDEV_SETUP_WRITE);
int main (void)
{
	double value;
	init_adc();
	usart0_init();
	// assign our stream to standard I/O streams
	stdout=&usart0_str;

	for(;;)
	{
		// Read ADC value on ADC-channel 0
		value=read_adc(0);
		// Print it to the terminal
		printf("Value: %u\n", (uint16_t)value);
		// Delay for 1s
		delay_ms(1000);
	}

}
/*}}}*/
