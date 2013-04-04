/*
 * File Name : linesensors.h
 * Purpose : Linesensors etc
 * Creation Date : 30-01-2013
 * Last Modified : tor  4 apr 2013 18:08:43
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

// Header guard
#ifndef LINE_H
#define LINE_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "constants.h"

void init_linesensors(void);
#endif
