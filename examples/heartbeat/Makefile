MCU = stm8
DEVICE = stm8s001j3
FLASHER = stlinkv2
CFLAGS = -I STM8S_StdPeriph_Driver/inc -I . -DSTM8S003 -c
CC = sdcc
OBJCOPY  = sdobjcopy
LIB = stm8s_gpio.rel stm8s_clk.rel stm8s_tim4.rel
OBJ = main.rel
TARGET = blink_heartbeat_spl

.PHONY: all clean

%.rel:	%.c
	$(CC) -m$(MCU) $(CFLAGS) $(LDFLAGS) $<

%.rel:	STM8S_StdPeriph_Driver/src/%.c
	$(CC) -m$(MCU) $(CFLAGS) $(LDFLAGS) $<

all:	$(OBJ) $(LIB)
	$(CC) -m$(MCU) -o $(TARGET).ihx $(OBJ) $(LIB)

size:
	@$(OBJCOPY) -I ihex --output-target=binary $(TARGET).ihx $(TARGET).bin
	@echo "Image size:"
	@stat -L -c %s $(TARGET).bin

flash:
	stm8flash -c $(FLASHER) -p $(DEVICE) -w $(TARGET).ihx
clean:
	@rm -v *.sym *.asm *.lst *.rel *.ihx *.bin *lk *.rst *.cdb *.map
