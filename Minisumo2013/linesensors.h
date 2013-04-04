/*
 * File Name : linesensors.h
 * Purpose : Linesensors etc
 * Creation Date : 30-01-2013
 * Last Modified : lör 30 mar 2013 12:54:01
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

// Header guard
#ifndef LINE_H
#define LINE_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "motors.h"
#include "constants.h"
#include "leds.h"

void init_linesensors(void);
#endif
