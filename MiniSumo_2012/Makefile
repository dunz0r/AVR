CC=avr-gcc
CFLAGS=-Wall -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU)
MCU=atmega328
F_CPU=16000000UL
PRG=main

OBJCOPY=avr-objcopy
BIN_FORMAT=ihex

PORT=/dev/ttyACM0
BAUD=115200
PROTOCOL=stk500v1
PART=$(MCU)
AVRDUDE=avrdude -C /etc/avrdude.conf -F -V 

RM=rm -f

.PHONY: all
	all: $(PRG).hex

$(PRG).hex: $(PRG).elf

$(PRG).elf: $(PRG).s

$(PRG).s: $(PRG).c

.PHONY: clean
	clean:
	    $(RM) $(PRG).elf $(PRG).hex $(PRG).s

upload: $(PRG).hex
	    $(AVRDUDE) -c $(PROTOCOL) -p m328p -P $(PORT) -b $(BAUD) -U flash:w:$<

%.elf: %.s ; $(CC) $(CFLAGS) -s -o $@ $<

%.s: %.c ; $(CC) $(CFLAGS) -S -o $@ $<

%.hex: %.elf ; $(OBJCOPY) -O $(BIN_FORMAT) -R .eeprom $< $@
