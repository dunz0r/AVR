/* Macro function to declare an output pin */
#define set_output(x)			_out(x)
#define _out(bit,port)	DDR##port |= (1 << bit)

/* Macro function to declare an input pin */
#define set_input(x)			_in(x)
#define _in(bit,port)	DDR##port &= ~(1 << bit)

/* Macro function to set an output pin high */
#define output_high(x)			_on(x)
#define _on(bit,port)	PORT##port |= (1 << bit)

/* Macro function to set an output pin low */
#define output_low(x)			_off(x)
#define _off(bit,port)	PORT##port &= ~(1 << bit)

/* Macro function to toggle an output pin */
#define toggle_output(x)			_flip(x)
#define _flip(bit,port)	PORT##port ^= (1 << bit)

/* Macro function to set internal pullup resistor of input pin (same as "on" macro)*/
#define enable_pullup(x)		_on(x)

/* Macro function to get state of input pin */
#define read_input(x)			_get(x)
#define _get(bit,port)	(PIN##port & (1 << bit))
