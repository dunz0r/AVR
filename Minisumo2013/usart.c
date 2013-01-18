/*
 * File Name : uart.c
 * Purpose : Functions for USART
 * Creation Date : 30-08-2012
 * Last Modified : Wed 16 Jan 2013 21:30:00 CET
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */
#include "usart.h"

/*{{{ Initialize usart */
void init_usart(void)
{
	/* Set baud rate */
	UBRR0 = UBRR_VALUE;
	/* Set frame format to 8 data bits, no parity, 1 stop bit */
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ01);
	/* enable transmission and reception */
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
}
/*}}}*/

/*{{{ Sends a byte over usart0 */
int usart0_sendbyte(char u8_data, FILE *stream)
{
	if(u8_data == '\n')
	{
		usart0_sendbyte('\r', stream);
	}
	// wait while previous byte is completed
	while(!(UCSR0A&(1<<UDRE0)));
	UDR0 = u8_data;
	return 0;
}
/*}}}*/
