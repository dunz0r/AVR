/*
 * File Name : timer.h
 * Purpose : Timer1
 * Creation Date : 2013-01-16
 * Last Modified : tor  4 apr 2013 18:06:42
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

// Header guard
#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void init_timer1(void);

void start_timer1(void);

void stop_timer1(void);

#endif
