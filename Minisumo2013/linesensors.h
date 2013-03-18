/*
 * File Name : linesensors.h
 * Purpose : Linesensors etc
 * Creation Date : 30-01-2013
 * Last Modified : mån 18 mar 2013 22:57:32
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
#include "usart.h"

void init_linesensors(void);
#endif
