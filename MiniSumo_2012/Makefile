# AVR-GCC Makefile
# By Gabriel Fornaeus <gf@hax0r.se>

PROJECT=sumo
SOURCES=main.c
CC=avr-gcc
OBJCOPY=avr-objcopy
MMCU=atmega328p
FREQUENCY=16000000
CFLAGS=-mmcu=$(MMCU) -Wall -Os -c

$(PROJECT).hex: $(PROJECT).out
	$(OBJCOPY) -j .text -j .data -O ihex $(PROJECT).out $(PROJECT).hex

$(PROJECT).out: $(SOURCES)
	$(CC) $(CFLAGS) -I./ -o $(PROJECT).out $(SOURCES)

upload: $(PROJECT).hex
	avrdude -F -V -p ATMEGA328P -c arduino -P /dev/ttyACM0 -b 115200 -U flash:w:$(PROJECT).hex

clean:
	rm -f $(PROJECT).out
	rm -f $(PROJECT).hex
	rm -f $(PROJECT).trace

simulate: 
	simulavr -t $(PROJECT).trace -s -V --device $(MMCU) --file $(PROJECT).out -F $(FREQUENCY)
