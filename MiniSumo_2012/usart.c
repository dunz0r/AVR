/*
 * File Name : uart.c
 * Purpose : Functions for USART
 * Creation Date : 30-08-2012
 * Last Modified : mån 15 okt 2012 02:14:34
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */
#include "usart.h"
void usart0_init(void)
{
	/* Set baud rate */
	UBRR0 = UBRR_VALUE;
	/* Set frame format to 8 data bits, no parity, 1 stop bit */
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ01);
	/* enable transmission and reception */
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
}

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
