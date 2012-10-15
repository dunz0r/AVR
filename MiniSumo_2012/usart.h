/*
 * File Name : uart.h
 * Purpose : Headers and defines for USART
 * Creation Date : 30-08-2012
 * Last Modified : mån 15 okt 2012 02:14:51
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

/* Header guard */

#ifndef USART_H

#define USART_H
#include <stdio.h>
#include <avr/io.h>
/*
 * Defines for USART
 *
 */
#define USART_BAUDRATE 9600
#define UBRR_VALUE ((( F_CPU / (USART_BAUDRATE * 16UL))) - 1)

void usart0_init(void);
int usart0_sendbyte(char u8_data, FILE *stream);
#endif
