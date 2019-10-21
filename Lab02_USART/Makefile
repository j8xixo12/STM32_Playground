CROSS_COMPILE ?= arm-none-eabi-
SF=st-flash
TARGET = USART

CFLAGS  = -std=gnu99 -g -O0 -Wall
CFLAGS += -mlittle-endian -mthumb -mthumb-interwork -mcpu=cortex-m4
CFLAGS += -fsingle-precision-constant -Wdouble-promotion

OBJS = $(patsubst %.c, %.o, $(wildcard *.c))
deps := $(OBJS:%.o=%.o.d)

.PHONY: all

all: $(TARGET).bin

%.o: %.c
	$(CROSS_COMPILE)gcc $(CFLAGS) -c $< -o $@ -MMD -MF $@.d

$(TARGET).out: $(OBJS) stm32_flash.ld
	$(CROSS_COMPILE)ld -T stm32_flash.ld -o $(TARGET).out $(OBJS)

$(TARGET).bin: $(TARGET).out
	$(CROSS_COMPILE)objcopy -j .text -O binary $(TARGET).out $(TARGET).bin

flash: $(TARGET).out
	$(SF) write $(TARGET).bin 0x8000000

clean:
	rm -f *.o *.out *.bin
