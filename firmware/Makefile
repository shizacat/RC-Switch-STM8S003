######################################
# target
######################################
TARGET = rc_switch_stm

#######################################
# paths
#######################################
# Path to SPL from ST
SPL_ROOT = ../../!stm8/STM8S_SPL

# Build path
BUILD_DIR = build

# source path
SOURCES_DIR = \
$(SPL_ROOT)/Libraries/STM8S_StdPeriph_Driver/src \
mylib

######################################
# source
######################################
# C sources
C_SOURCES =  \
$(SPL_ROOT)/Libraries/STM8S_StdPeriph_Driver/src/stm8s_gpio.c \
$(SPL_ROOT)/Libraries/STM8S_StdPeriph_Driver/src/stm8s_clk.c \
$(SPL_ROOT)/Libraries/STM8S_StdPeriph_Driver/src/stm8s_tim1.c \
$(SPL_ROOT)/Libraries/STM8S_StdPeriph_Driver/src/stm8s_itc.c \
main.c \
stm8s_it.c

# C includes
C_INCLUDES =  \
-I$(SPL_ROOT)/Libraries/STM8S_StdPeriph_Driver/inc \
-I./

#######################################
# binaries
#######################################
CC = sdcc
FLASHER = stm8flash

#######################################
# CFLAGS
#######################################
# mcu
MCU = stm8

# STM8 device (default is STM8 discovery board)
DEVICE = STM8S003

CFLAGS = -m$(MCU) -D$(DEVICE) $(C_INCLUDES) --opt-code-size

# default action: build all
all: $(BUILD_DIR)/$(TARGET).ihx

#######################################
# build the application
#######################################
.PRECIOUS: $(BUILD_DIR)/%.rel

OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.rel)))
vpath %.c $(sort $(dir $(C_SOURCES)))

$(BUILD_DIR)/%.rel: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $? -o $@

$(BUILD_DIR)/%.ihx: $(OBJECTS)
	$(CC) $(CFLAGS) --out-fmt-ihx $(OBJECTS) -o $@

$(BUILD_DIR):
	mkdir $@

upload: $(BUILD_DIR)/$(TARGET).ihx
	$(FLASHER) -c stlinkv2 -p stm8s003f3 -w $<

clean:
	-rm -fR $(BUILD_DIR)
# @rm -v *.sym *.asm *.lst *.rel *.ihx *lk *.rst *.cdb *.map
