/*
 * File Name : motors.h
 * Purpose : Control of a motor via an L298N H-bridge
 * Creation Date : 2013-01-16
 * Last Modified : lör 23 mar 2013 12:36:57
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

// Header guard
#ifndef MOTORS_H
#define MOTORS_H

#include <avr/io.h>
#include "utils.h"
#include "constants.h"

/* {{{ Pins */

/* D6 */
#define ENABLE_A OCR0A
/* D5 */
#define ENABLE_B OCR0B
#define INPUT_1 0,B
#define INPUT_2 7,D
#define INPUT_3 3,B
#define INPUT_4 4,D
/* }}} */

void set_heading(int16_t speed, uint16_t difference);
void init_motors(void);
void set_motors(int16_t left_motor, int16_t right_motor);

#endif
