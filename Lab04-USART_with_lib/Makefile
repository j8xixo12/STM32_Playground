PROJECT_NAME = USART
BUILDDIR = build
DEVICE = ../stm32f407g_lib/inc/STM32F4xx
CORE = ../stm32f407g_lib/inc/CMSIS
PERIPH = ../stm32f407g_lib/inc/STM32F4xx_StdPeriph_Driver

SOURCES += \
			$(PERIPH)/src/stm32f4xx_gpio.c \
			$(PERIPH)/src/stm32f4xx_rcc.c \
			$(PERIPH)/src/stm32f4xx_usart.c
			# $(PERIPH)/src/misc.c 
			# $(PERIPH)/src/stm32f4xx_exti.c 
			# $(PERIPH)/src/stm32f4xx_syscfg.c 

SOURCES += startup_stm32f4xx.S
SOURCES += system_stm32f4xx.c

SOURCES += \
			main.c

OBJECTS = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(SOURCES))))

INCLUDES += -I$(DEVICE) \
			-I$(CORE) \
			-I$(PERIPH)/inc \
			-I.

ELF = $(BUILDDIR)/$(PROJECT_NAME).elf
HEX = $(BUILDDIR)/$(PROJECT_NAME).hex
BIN = $(BUILDDIR)/$(PROJECT_NAME).bin

CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc
AR = arm-none-eabi-ar
OBJCOPY = arm-none-eabi-objcopy
GDB = arm-none-eabi-gdb

CFLAGS  = -O0 -g -Wall -I.\
   -mcpu=cortex-m4 -mthumb \
   -mfpu=fpv4-sp-d16 -mfloat-abi=hard \
   $(INCLUDES) -DUSE_STDPERIPH_DRIVER

LDSCRIPT = stm32_flash.ld
LDFLAGS += -T$(LDSCRIPT) -mthumb -mcpu=cortex-m4 -nostdlib

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex $< $@

$(ELF): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS) $(LDLIBS)

$(BUILDDIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILDDIR)/%.o: %.S
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

flash: $(BIN)
	st-flash write $(BIN) 0x8000000

debug: $(ELF)
	$(GDB) -tui $(ELF)

all: $(HEX) $(BIN)

.PHONY: clean
clean:
	rm -rf build