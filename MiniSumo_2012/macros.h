/*
 * File Name : macros.h
 * Purpose :
 * Creation Date : 26-08-2012
 * Last Modified : sön 23 sep 2012 17:23:13
 * Created By : Gabriel Fornaeus, <gf@hax0r.se>
 *
 */

/* Header guard */
#ifndef MACRO_H

#define MACRO_H

/* Macro function to declare an output pin */
#define set_output(x)			_set_output(x)
#define _set_output(bit,port)	DDR##port |= (1 << bit)

/* Macro function to declare an input pin */
#define set_input(x)			_set_input(x)
#define _set_input(bit,port)	DDR##port &= ~(1 << bit)

/* Macro function to set an output pin high */
#define output_high(x)			_output_high(x)
#define _output_high(bit,port)	PORT##port |= (1 << bit)

/* Macro function to set an output pin low */
#define output_low(x)			_output_low(x)
#define _output_low(bit,port)	PORT##port &= ~(1 << bit)

/* Macro function to toggle an output pin */
#define toggle_output(x)			_toggle_output(x)
#define _toggle_output(bit,port)	PORT##port ^= (1 << bit)

/* Macro function to set internal pullup resistor of input pin (same as "on" macro)*/
#define enable_pullup(x)		_output_high(x)

/* Macro function to get state of input pin */
#define read_input(x)			_read_input(x)
#define _read_input(bit,port)	(PIN##port & (1 << bit))

#endif
