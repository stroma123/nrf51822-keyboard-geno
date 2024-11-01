#PROJECT_NAME := ble_app_hids_keyboard_s110_pca10028

#OUTPUT_FILENAME := ble4100
#MAKEFILE_NAME := $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))

# Note: OPENOCD_PATH, GCC_PATH, GNU_INSTALL_ROOT, GNU_VERSION and GNU_PREFIX
# variables are expected to be pre-set in the environment
#OPENOCD_PATH       ?= D:/nrf51822/OpenOCD/0.10.0-201601101000-dev/bin
OPENOCD_EXECUTABLE := openocd.exe

MAKEFILE_NAME := $(MAKEFILE_LIST)
MAKEFILE_DIR := $(dir $(MAKEFILE_NAME) ) 
NRFSDK_DIR = ../../../sdk
SOURCE_DIR = ../..
TMK_DIR = ../../../tmk/tmk_core
TEMPLATE_PATH = $(NRFSDK_DIR)/toolchain/gcc
ifeq ($(OS),Windows_NT)
include $(TEMPLATE_PATH)/Makefile.windows
else
include $(TEMPLATE_PATH)/Makefile.posix
endif

MK := mkdir
RM := rm -rf

#echo suspend
ifeq ("$(VERBOSE)","1")
NO_ECHO := 
else
NO_ECHO := @
endif

# Toolchain commands
CC              := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-gcc'
AS              := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-as'
AR              := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-ar' -r
LD              := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-ld'
NM              := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-nm'
OBJDUMP         := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-objdump'
OBJCOPY         := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-objcopy'
SIZE            := '$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-size'

#function for removing duplicates in a list
remduplicates = $(strip $(if $1,$(firstword $1) $(call remduplicates,$(filter-out $(firstword $1),$1))))

#source common to all targets
C_SOURCE_FILES += \
$(abspath $(SOURCE_DIR)/ble/main.c) \
$(abspath $(SOURCE_DIR)/ble/battery_service.c) \
$(abspath $(SOURCE_DIR)/ble/ble_hid_service.c) \
$(abspath $(SOURCE_DIR)/ble/ble_services.c) \
$(abspath $(SOURCE_DIR)/keyboard/keyboard_led.c) \
$(abspath $(SOURCE_DIR)/keyboard/keyboard_matrix.c) \
$(abspath $(SOURCE_DIR)/keyboard/keymap_plain.c) \
$(abspath $(SOURCE_DIR)/keyboard/keyboard_timer.c) \
$(abspath $(SOURCE_DIR)/keyboard/host_driver.c) \
$(abspath $(SOURCE_DIR)/keyboard/storage.c) \
$(abspath $(SOURCE_DIR)/keyboard/keyboard_fn.c) \
$(abspath $(SOURCE_DIR)/keyboard/keymap_storage.c) \
$(abspath $(SOURCE_DIR)/keyboard/uart_driver.c) \
$(abspath $(SOURCE_DIR)/command.c) \
\
$(abspath $(NRFSDK_DIR)/ble_advdata.c) \
$(abspath $(NRFSDK_DIR)/ble_advertising.c) \
$(abspath $(NRFSDK_DIR)/ble_bas.c) \
$(abspath $(NRFSDK_DIR)/ble_conn_params.c) \
$(abspath $(NRFSDK_DIR)/ble_dis.c) \
$(abspath $(NRFSDK_DIR)/ble_hids.c) \
$(abspath $(NRFSDK_DIR)/ble_srv_common.c) \
$(abspath $(NRFSDK_DIR)/device_manager_peripheral.c) \
$(abspath $(NRFSDK_DIR)/bootloader_util.c) \
$(abspath $(NRFSDK_DIR)/dfu_app_handler.c) \
$(abspath $(NRFSDK_DIR)/ble_dfu.c) \
\
$(abspath $(NRFSDK_DIR)/app_uart_fifo.c) \
$(abspath $(NRFSDK_DIR)/nrf_delay.c) \
$(abspath $(NRFSDK_DIR)/nrf_drv_common.c) \
$(abspath $(NRFSDK_DIR)/nrf_drv_uart.c) \
$(abspath $(NRFSDK_DIR)/nrf_drv_wdt.c) \
$(abspath $(NRFSDK_DIR)/pstorage.c) \
$(abspath $(NRFSDK_DIR)/nrf_adc.c) \
\
$(abspath $(NRFSDK_DIR)/app_error.c) \
$(abspath $(NRFSDK_DIR)/app_fifo.c) \
$(abspath $(NRFSDK_DIR)/app_scheduler.c) \
$(abspath $(NRFSDK_DIR)/app_timer.c) \
$(abspath $(NRFSDK_DIR)/app_timer_appsh.c) \
$(abspath $(NRFSDK_DIR)/app_trace.c) \
$(abspath $(NRFSDK_DIR)/nrf_assert.c) \
$(abspath $(NRFSDK_DIR)/retarget.c) \
\
$(abspath $(NRFSDK_DIR)/softdevice_handler.c) \
$(abspath $(NRFSDK_DIR)/softdevice_handler_appsh.c) \
$(abspath $(NRFSDK_DIR)/toolchain/system_nrf51.c) \
\
$(abspath $(TMK_DIR)/common/action.c) \
$(abspath $(TMK_DIR)/common/action_layer.c) \
$(abspath $(TMK_DIR)/common/action_macro.c) \
$(abspath $(TMK_DIR)/common/action_tapping.c) \
$(abspath $(TMK_DIR)/common/action_util.c) \
$(abspath $(TMK_DIR)/common/debug.c) \
$(abspath $(TMK_DIR)/common/hook.c) \
$(abspath $(TMK_DIR)/common/host.c) \
$(abspath $(TMK_DIR)/common/keyboard.c) \
$(abspath $(TMK_DIR)/common/matrix.c) \
$(abspath $(TMK_DIR)/common/print.c) \
$(abspath $(TMK_DIR)/common/util.c) \
$(abspath $(TMK_DIR)/common/keymap.c) \
$(abspath $(TMK_DIR)/common/bootmagic.c) \


#assembly files common to all targets
ASM_SOURCE_FILES  = $(abspath $(NRFSDK_DIR)/toolchain/gcc/gcc_startup_nrf51.s)

#includes common to all targets
INC_PATHS += -I$(abspath $(SOURCE_DIR)/config)
INC_PATHS += -I$(abspath $(SOURCE_DIR)/ble)
INC_PATHS += -I$(abspath $(SOURCE_DIR)/keyboard)
INC_PATHS += -I$(abspath $(SOURCE_DIR))
INC_PATHS += -I$(abspath $(NRFSDK_DIR))
INC_PATHS += -I$(abspath $(NRFSDK_DIR)/toolchain)
INC_PATHS += -I$(abspath $(NRFSDK_DIR)/toolchain/gcc)
INC_PATHS += -I$(abspath $(TMK_DIR)/common)

OBJECT_DIRECTORY = _build
LISTING_DIRECTORY = $(OBJECT_DIRECTORY)
OUTPUT_BINARY_DIRECTORY = $(OBJECT_DIRECTORY)

# Sorting removes duplicates
BUILD_DIRECTORIES := $(sort $(OBJECT_DIRECTORY) $(OUTPUT_BINARY_DIRECTORY) $(LISTING_DIRECTORY) )

#flags common to all targets
CFLAGS  = -DBOARD_CUSTOM
CFLAGS += -DSOFTDEVICE_PRESENT
CFLAGS += -DSWI_DISABLE0
CFLAGS += -DS110
CFLAGS += -DNRF51
CFLAGS += -DBLE_STACK_SUPPORT_REQD
CFLAGS += -DBLE_DFU_APP_SUPPORT
CFLAGS += -mcpu=cortex-m0
CFLAGS += -mthumb -mabi=aapcs --std=gnu99
#CFLAGS += -Wall -Werror -O3
CFLAGS += -Os
CFLAGS += -mfloat-abi=soft
CFLAGS += -D__HEAP_SIZE=0
CFLAGS += -include config.h
# keep every function in separate section. This will allow linker to dump unused functions
CFLAGS += -ffunction-sections -fdata-sections -fno-strict-aliasing
CFLAGS += -fno-builtin --short-enums
#CFLAGS += -g

# keep every function in separate section. This will allow linker to dump unused functions
LDFLAGS += -Xlinker -Map=$(LISTING_DIRECTORY)/$(OUTPUT_FILENAME).map
LDFLAGS += -mthumb -mabi=aapcs -L $(TEMPLATE_PATH) -T$(LINKER_SCRIPT)
LDFLAGS += -mcpu=cortex-m0
# let linker to dump unused sections
LDFLAGS += -Wl,--gc-sections
# use newlib in nano version
LDFLAGS += --specs=nano.specs -lc -lnosys

# Assembler flags
ASMFLAGS += -x assembler-with-cpp
ASMFLAGS += -DBOARD_CUSTOM
ASMFLAGS += -DSOFTDEVICE_PRESENT
ASMFLAGS += -DSWI_DISABLE0
ASMFLAGS += -DS110
ASMFLAGS += -DNRF51
ASMFLAGS += -DBLE_STACK_SUPPORT_REQD
ASMFLAGS += -DBLE_DFU_APP_SUPPORT
ASMFLAGS += -D__HEAP_SIZE=0
#default target - first one defined
default: clean ble400

#building all targets
all: clean
	$(NO_ECHO)$(MAKE) -f $(MAKEFILE_NAME) -C $(MAKEFILE_DIR) -e cleanobj
	$(NO_ECHO)$(MAKE) -f $(MAKEFILE_NAME) -C $(MAKEFILE_DIR) -e ble60

#target for printing all targets
help:
	@echo "following targets are available:"
	@echo "    ble60"
	@echo "    flash_erase"
	@echo "    flash_softdevice"
	@echo "    flash_ble60"
	@echo "    flash_bootloader"
	@echo "    fflash_bootloader_keil"
	@echo "    flash_ble60_keil"
	@echo "    reset_target"

C_SOURCE_FILE_NAMES = $(notdir $(C_SOURCE_FILES))
C_PATHS = $(call remduplicates, $(dir $(C_SOURCE_FILES) ) )
C_OBJECTS = $(addprefix $(OBJECT_DIRECTORY)/, $(C_SOURCE_FILE_NAMES:.c=.o) )

ASM_SOURCE_FILE_NAMES = $(notdir $(ASM_SOURCE_FILES))
ASM_PATHS = $(call remduplicates, $(dir $(ASM_SOURCE_FILES) ))
ASM_OBJECTS = $(addprefix $(OBJECT_DIRECTORY)/, $(ASM_SOURCE_FILE_NAMES:.s=.o) )

vpath %.c $(C_PATHS)
vpath %.s $(ASM_PATHS)

OBJECTS = $(C_OBJECTS) $(ASM_OBJECTS)

ble60: CFLAGS += -DBLE60
ble60: OUTPUT_FILENAME = ble60_app
ble60: ble_xx finalize

ble_xx: LINKER_SCRIPT = ble_app_hids_keyboard_gcc_nrf51.ld
ble_xx: $(BUILD_DIRECTORIES) $(OBJECTS)
	@echo Linking target: $(OUTPUT_FILENAME).out
	$(NO_ECHO)$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out

## Create build directories
$(BUILD_DIRECTORIES):
	echo $(MAKEFILE_NAME)
	$(MK) $@

# Create objects from C SRC files
$(OBJECT_DIRECTORY)/%.o: %.c
	@echo Compiling file: $(notdir $<)
	$(NO_ECHO)$(CC) $(CFLAGS) $(INC_PATHS) -c -o $@ $<

# Assemble files
$(OBJECT_DIRECTORY)/%.o: %.s
	@echo Compiling file: $(notdir $<)
	$(NO_ECHO)$(CC) $(ASMFLAGS) $(INC_PATHS) -c -o $@ $<


# Link
$(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out: $(BUILD_DIRECTORIES) $(OBJECTS)
	@echo Linking target: $(OUTPUT_FILENAME).out
	$(NO_ECHO)$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out


## Create binary .bin file from the .out file
$(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).bin: $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out
	@echo Preparing: $(OUTPUT_FILENAME).bin
	$(NO_ECHO)$(OBJCOPY) -O binary $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).bin

## Create binary .hex file from the .out file
$(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).hex: $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out
	@echo Preparing: $(OUTPUT_FILENAME).hex
	$(NO_ECHO)$(OBJCOPY) -O ihex $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).hex

finalize: genbin genhex echosize

genbin:
	@echo Preparing: $(OUTPUT_FILENAME).bin
	$(NO_ECHO)$(OBJCOPY) -O binary $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).bin

## Create binary .hex file from the .out file
genhex: 
	@echo Preparing: $(OUTPUT_FILENAME).hex
	$(NO_ECHO)$(OBJCOPY) -O ihex $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).hex

echosize:
	-@echo ''
	$(NO_ECHO)$(SIZE) $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out
	-@echo ''

clean:
	$(RM) $(BUILD_DIRECTORIES)

cleanobj:
	$(RM) $(BUILD_DIRECTORIES)/*.o

flash: $(MAKECMDGOALS)
	@echo Flashing: $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).hex

flash_hex:
	@echo Flashing: $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).hex
	"$(OPENOCD_PATH)/$(OPENOCD_EXECUTABLE)" -f board/nrf51x22.cfg -c init -c "reset init" -c halt -c "program $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).hex verify reset exit"

flash_erase:
	@echo Mass erase all flash!
	"$(OPENOCD_PATH)/$(OPENOCD_EXECUTABLE)" -f board/nrf51x22.cfg -c init -c "reset init" -c "nrf51 mass_erase" -c exit

## Flash softdevice
flash_softdevice:
	@echo Flashing: s110_nrf51_8.0.0_softdevice.hex
	"$(OPENOCD_PATH)/$(OPENOCD_EXECUTABLE)" -f board/nrf51x22.cfg -c init -c "reset init" -c halt -c "program ../../../sdk/s110_nrf51_8.0.0_softdevice.hex verify reset exit"

reset_target:
	@echo Resetting...
	"$(OPENOCD_PATH)/$(OPENOCD_EXECUTABLE)" -f board/nrf51x22.cfg -c init -c "reset run" -c exit

flash_ble60: OUTPUT_FILENAME = ble60_app
flash_ble60: flash_hex

flash_bootloader:
	"$(OPENOCD_PATH)/$(OPENOCD_EXECUTABLE)" -f board/nrf51x22.cfg -c init -c "reset init" -c halt -c "program ../../../bootloader/project/armgcc/_build/ble60_bootloader.hex verify reset exit"

flash_bootloader_keil:
	"$(OPENOCD_PATH)/$(OPENOCD_EXECUTABLE)" -f board/nrf51x22.cfg -c init -c "reset init" -c halt -c "program ../../../bootloader/project/arm5_no_packs/_build/BLE60_Bootloader.hex verify reset exit"

flash_ble60_keil:
	"$(OPENOCD_PATH)/$(OPENOCD_EXECUTABLE)" -f board/nrf51x22.cfg -c init -c "reset init" -c halt -c "program ../arm5_no_packs/_build/BLE60_APP.hex verify reset exit"

