CROSS_COMPILE ?= arm-none-eabi-
SF=st-flash

CFLAGS  = -std=gnu99 -g -O0 -Wall
CFLAGS += -mlittle-endian -mthumb -mthumb-interwork -mcpu=cortex-m4
CFLAGS += -fsingle-precision-constant -Wdouble-promotion

.PHONY: all

all: blink.bin

blink.o: blink.c
	$(CROSS_COMPILE)gcc $(CFLAGS) -c blink.c -o blink.o

blink.out: blink.o stm32_flash.ld
	$(CROSS_COMPILE)ld -T stm32_flash.ld -o blink.out blink.o

blink.bin: blink.out
	$(CROSS_COMPILE)objcopy -j .text -O binary blink.out blink.bin

flash: blink.out
	$(SF) write blink.bin 0x8000000

clean:
	rm -f *.o *.out *.bin

