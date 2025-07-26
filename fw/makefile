# Target MCU
MCU = cortex-m0
CHIP = LPC812

# Toolchain
CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
CFLAGS = -mcpu=$(MCU) -mthumb -O0 -g -Wall -std=c11 -I./cmsis
LDFLAGS = -T linker.ld -nostdlib

# Files
OBJS = startup_lpc81x.o main.o display.o
TARGET = clock

all: $(TARGET).hex

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

clean:
	rm -f *.o *.elf *.hex

flash: $(TARGET).hex
	lpc21isp -verify -wipe $< /dev/cu.usbserial-DU0DO48A 115200 12000

