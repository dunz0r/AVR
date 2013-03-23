/*
 * File Name : timer.h
 * Purpose : Timer1
 * Creation Date : 2013-01-16
 * Last Modified : lör 23 mar 2013 17:59:56
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

// Header guard
#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "leds.h"
#include "motors.h"

void init_timer1(void);

void start_timer1(void);

void stop_timer1(void);

#endif
