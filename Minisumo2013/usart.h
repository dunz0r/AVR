/*
 * File Name : uart.h
 * Purpose : Headers and defines for USART
 * Creation Date : 30-08-2012
 * Last Modified : Wed 09 Jan 2013 11:23:57 CET
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

void init_usart(void);
int usart0_sendbyte(char u8_data, FILE *stream);
#endif
