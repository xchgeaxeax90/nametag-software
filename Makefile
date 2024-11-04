CC := avr-gcc
MCU := avr16dd20
FREQUENCY:=1000000
CFLAGS := -Os -mmcu=$(MCU) -c -DF_CPU=$(FREQUENCY) -MMD -MP

srcs = $(wildcard *.c)
objs = $(srcs:.c=.o)
deps = $(srcs:.c=.d)

all: main.hex

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

main.elf: main.o fuses.o pwm.o timer.o pins.o
	$(CC) -mmcu=$(MCU) -o $@ $^
	avr-size $@

main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex $< $@


.PHONY: clean
clean:
	rm -rf *.hex *.elf *.o *.d

-include $(deps)
