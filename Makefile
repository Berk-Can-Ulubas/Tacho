# Voller Pfad zu deinem Compiler
TOOLCHAIN=../arm-gcc/gcc-arm-none-eabi-10.3-2021.10/bin

# Compiler und Tools
CC=$(TOOLCHAIN)/arm-none-eabi-gcc
OBJCOPY=$(TOOLCHAIN)/arm-none-eabi-objcopy

# Quell-Dateien inkl. system_stm32f4xx.c
SRCS = main.c startup_stm32f429xx.s ../STM32CubeF4/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c init_stub.c

# Compiler Flags (für Kompilierung)
CFLAGS = -mcpu=cortex-m4 -mthumb -O2 -Wall -DSTM32F429xx \
    -I../STM32CubeF4/Drivers/CMSIS/Device/ST/STM32F4xx/Include \
    -I../STM32CubeF4/Drivers/CMSIS/Include

# Linker Flags (für Linken)
LDFLAGS = -mcpu=cortex-m4 -mthumb -T STM32F429ZITX_FLASH.ld -nostartfiles --specs=nosys.specs

# Objekt-Dateien
OBJS = $(SRCS:.c=.o)
OBJS := $(OBJS:.s=.o)

# Targets
all: firmware.bin

# Kompiliere .c und .s Dateien zu .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(CC) $(CFLAGS) -c $< -o $@

# Linke die Objektdateien
firmware.elf: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

# Erzeuge Binärdatei
firmware.bin: firmware.elf
	$(OBJCOPY) -O binary $< $@

# Clean
clean:
	rm -f *.o firmware.elf firmware.bin
