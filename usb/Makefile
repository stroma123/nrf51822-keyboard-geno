PROJ_NAME := CH55X

ifndef OUTPUT_DIR
ifdef OUTPUT_DIRECTORY
	OUTPUT_DIR = $(OUTPUT_DIRECTORY)
else
	OUTPUT_DIR = _build
endif
endif
#OBJ_DIR = $(OUTPUT_DIR)/$(PROJ_NAME)
OBJ_DIR = $(OUTPUT_DIR)

ifndef USB_SOURCE_DIR
USB_SOURCE_DIR := ./
endif

SDCC := sdcc
#SDCC_CFLAGS := -mmcs51 --model-small --std-c11 -o $(OUTPUT_DIR)/ --opt-code-size
SDCC_CFLAGS += -mmcs51 --model-small --stack-auto --std-c11 -o $(OUTPUT_DIR)/ --opt-code-size -I .
# to suppress 'warning 283: function declarator with no prototype' warnings
SDCC_CFLAGS += --disable-warning 283
#SDCC_CFLAGS += -DMODELM
#SDCC_CFLAGS += -DDEBUG_UART0=1
#SDCC_CFLAGS += -DDEBUG_NRF=1
# device to host
#SDCC_CFLAGS += -DDEBUG_USB_IN=1
# host to device
#SDCC_CFLAGS += -DDEBUG_USB_OUT=1

#LDFLAGS := --xram-size 1024 --iram-size 256 --code-size 16384 --out-fmt-ihx
SDCC_LDFLAGS := --xram-size 1024 --iram-size 256 --code-size 14336 --out-fmt-ihx --xram-loc 0

USB_SOURCES := $(USB_SOURCE_DIR)/main.c \
			   $(USB_SOURCE_DIR)/app_timer.c \
			   $(USB_SOURCE_DIR)/endpoints.c \
			   $(USB_SOURCE_DIR)/system.c \
			   $(USB_SOURCE_DIR)/uart.c \
			   $(USB_SOURCE_DIR)/interrupt.c \
			   $(USB_SOURCE_DIR)/descriptor.c \

ifeq (yes,$(strip $(ONBOARD_CMSIS_DAP)))
SDCC_CFLAGS += -DONBOARD_CMSIS_DAP
USB_SOURCES += $(USB_SOURCE_DIR)/DAP.c \
               $(USB_SOURCE_DIR)/DAP_hid.c \
			   $(USB_SOURCE_DIR)/SW_DP.c \

endif

LIBS := $(patsubst $(USB_SOURCE_DIR)/%.c,$(OBJ_DIR)/%.rel,$(USB_SOURCES))

OUTPUT_IHX := $(OBJ_DIR)/$(PROJ_NAME).ihx
ifndef OUTPUT_HEX
OUTPUT_HEX := $(OUTPUT_DIR)/$(PROJ_NAME).hex
endif
ifndef OUTPUT_BIN
OUTPUT_BIN := $(OUTPUT_DIR)/$(PROJ_NAME).bin
endif

.PHONY:ch554, usb

usb: clean ch554
ch554: $(OUTPUT_HEX) $(OUTPUT_BIN)
	@echo DONE ch554

$(OUTPUT_HEX): $(OUTPUT_IHX)
	@echo Preparing: $(OUTPUT_HEX)
	@packihx $(OUTPUT_IHX) > $(OUTPUT_HEX)

$(OUTPUT_BIN): $(OUTPUT_IHX)
	@echo Preparing: $(OUTPUT_BIN)
	@makebin -p $(OUTPUT_IHX) $(OUTPUT_BIN)

$(OBJ_DIR):
	-@mkdir -p $(OBJ_DIR)

$(OUTPUT_IHX): $(LIBS)
	@echo Linking target: $(notdir $(OUTPUT_IHX))
	@$(SDCC) $(LIBS) $(SDCC_CFLAGS) $(SDCC_LDFLAGS) -o $(OUTPUT_IHX)

$(OBJ_DIR)/%.rel: $(USB_SOURCE_DIR)/%.c $(OBJ_DIR)
	@echo Compiling usb file: $(notdir $<)
	@$(SDCC) $(SDCC_CFLAGS) -c $<

.PHONY:clean
clean:
	rm -r $(OUTPUT_DIR)

flash: $(OUTPUT_BIN)
	wchisptool -f $(OUTPUT_BIN)