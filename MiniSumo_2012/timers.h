/*
 * File Name : timers.h
 * Purpose : Timer inits and functions
 * Creation Date : 23-09-2012
 * Last Modified : sön 11 nov 2012 21:57:34
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

/* Header guard */
#ifndef TIMERS_H

#define TIMERS_H
#include <avr/io.h>
void init_timer0(void);
void start_timer0(void);
void init_timer1(void);
#endif
