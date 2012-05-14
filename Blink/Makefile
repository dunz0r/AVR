# AVR-GCC Makefile
# By Gabriel Fornaeus <gf@hax0r.se>

PROJECT=Blink
SOURCES=main.c
CC=avr-gcc
OBJCOPY=avr-objcopy
MMCU=attiny2313
FREQUENCY=1000000

CFLAGS=-mmcu=$(MMCU) -Wall

$(PROJECT).hex: $(PROJECT).out
	$(OBJCOPY) -j .text -j .data -O ihex $(PROJECT).out $(PROJECT).hex

$(PROJECT).out: $(SOURCES)
	$(CC) $(CFLAGS) -I./ -o $(PROJECT).out $(SOURCES)

upload: $(PROJECT).hex
	avrdude -p t2313 -c dragon_isp -P usb -e -U flash:w:$(PROJECT).hex

clean:
	rm -f $(PROJECT).out
	rm -f $(PROJECT).hex
	rm -f $(PROJECT).trace

simulate: 
	simulavr -t $(PROJECT).trace -s -V --device $(MMCU) --file $(PROJECT).out -F $(FREQUENCY)
