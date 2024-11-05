#PROJECT_NAME := dfu_dual_bank_ble_s110_pca10028

# Note: OPENOCD_PATH, GCC_PATH, GNU_INSTALL_ROOT, GNU_VERSION and GNU_PREFIX
# variables are expected to be pre-set in the environment
# OPENOCD_PATH       ?= D:/nrf51822/OpenOCD/0.10.0-201601101000-dev/bin
OPENOCD_EXECUTABLE := openocd.exe

export OUTPUT_FILENAME
#MAKEFILE_NAME := $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
MAKEFILE_NAME := $(MAKEFILE_LIST)
MAKEFILE_DIR := $(dir $(MAKEFILE_NAME) ) 

NRFSDK_DIR = ../../../sdk
SOURCE_DIR = ../..
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
$(abspath $(NRFSDK_DIR)/app_error.c) \
$(abspath $(NRFSDK_DIR)/app_scheduler.c) \
$(abspath $(NRFSDK_DIR)/app_timer.c) \
$(abspath $(NRFSDK_DIR)/app_timer_appsh.c) \
$(abspath $(NRFSDK_DIR)/bootloader.c) \
$(abspath $(NRFSDK_DIR)/bootloader_settings.c) \
$(abspath $(NRFSDK_DIR)/bootloader_util.c) \
$(abspath $(NRFSDK_DIR)/crc16.c) \
$(abspath $(NRFSDK_DIR)/dfu_dual_bank.c) \
$(abspath $(NRFSDK_DIR)/dfu_init_template.c) \
$(abspath $(NRFSDK_DIR)/dfu_transport_ble.c) \
$(abspath $(NRFSDK_DIR)/hci_mem_pool.c) \
$(abspath $(NRFSDK_DIR)/nrf_assert.c) \
$(abspath $(NRFSDK_DIR)/nrf_delay.c) \
$(abspath $(NRFSDK_DIR)/pstorage_raw.c) \
$(abspath $(SOURCE_DIR)/dfu_ble_svc.c) \
$(abspath $(SOURCE_DIR)/main.c) \
$(abspath $(NRFSDK_DIR)/ble_advdata.c) \
$(abspath $(NRFSDK_DIR)/ble_conn_params.c) \
$(abspath $(NRFSDK_DIR)/ble_dfu.c) \
$(abspath $(NRFSDK_DIR)/ble_srv_common.c) \
$(abspath $(NRFSDK_DIR)/toolchain/system_nrf51.c) \
$(abspath $(NRFSDK_DIR)/softdevice_handler.c) \
$(abspath $(NRFSDK_DIR)/softdevice_handler_appsh.c) \

#assembly files common to all targets
ASM_SOURCE_FILES  = $(abspath $(NRFSDK_DIR)/toolchain/gcc/gcc_startup_nrf51.s)

#includes common to all targets
#-I ../../config -I ../../../sdk -I ../../../main/keyboard
INC_PATHS  = -I$(abspath $(SOURCE_DIR)/config)
INC_PATHS += -I$(abspath $(SOURCE_DIR))
INC_PATHS += -I$(abspath $(NRFSDK_DIR))
INC_PATHS += -I$(abspath $(NRFSDK_DIR)/toolchain)
INC_PATHS += -I$(abspath $(NRFSDK_DIR)/toolchain/gcc)
INC_PATHS += -I$(abspath ../../../main/keyboard)

OBJECT_DIRECTORY = _build
LISTING_DIRECTORY = $(OBJECT_DIRECTORY)
OUTPUT_BINARY_DIRECTORY = $(OBJECT_DIRECTORY)

# Sorting removes duplicates
BUILD_DIRECTORIES := $(sort $(OBJECT_DIRECTORY) $(OUTPUT_BINARY_DIRECTORY) $(LISTING_DIRECTORY) )

#flags common to all targets
CFLAGS  = -DSWI_DISABLE0
CFLAGS += -DBOARD_CUSTOM
CFLAGS += -DSOFTDEVICE_PRESENT
CFLAGS += -DNRF51
CFLAGS += -DS110
CFLAGS += -D__HEAP_SIZE=0
CFLAGS += -D__STACK_SIZE=2048
CFLAGS += -DBLE_STACK_SUPPORT_REQD
CFLAGS += -DBSP_DEFINES_ONLY
CFLAGS += -DBLE60
CFLAGS += -mcpu=cortex-m0
CFLAGS += -mthumb -mabi=aapcs --std=gnu99
CFLAGS += -Wall -Werror -Os
#use link time optimization
CFLAGS += -flto
CFLAGS += -mfloat-abi=soft
# keep every function in separate section. This will allow linker to dump unused functions
CFLAGS += -ffunction-sections -fdata-sections -fno-strict-aliasing
CFLAGS += -fno-builtin --short-enums

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
ASMFLAGS += -DSWI_DISABLE0
ASMFLAGS += -DBOARD_CUSTOM
ASMFLAGS += -DSOFTDEVICE_PRESENT
ASMFLAGS += -DNRF51
ASMFLAGS += -DS110
ASMFLAGS += -D__HEAP_SIZE=0
ASMFLAGS += -D__STACK_SIZE=2048
ASMFLAGS += -DBLE_STACK_SUPPORT_REQD
ASMFLAGS += -DBSP_DEFINES_ONLY
#default target - first one defined
default: clean modelm_bootloader

#building all targets
all: clean
	$(NO_ECHO)$(MAKE) -f $(MAKEFILE_NAME) -C $(MAKEFILE_DIR) -e cleanobj
	$(NO_ECHO)$(MAKE) -f $(MAKEFILE_NAME) -C $(MAKEFILE_DIR) -e modelm_bootloader
	$(NO_ECHO)$(MAKE) -f $(MAKEFILE_NAME) -C $(MAKEFILE_DIR) -e ble60_bootloader

#target for printing all targets
help:
	@echo following targets are available:
	@echo 	modelm_bootloader
	@echo 	ble60_bootloader
	@echo 	flash_erase
	@echo 	flash_softdevice
	@echo 	flash_bootloader
	@echo 	reset_target


C_SOURCE_FILE_NAMES = $(notdir $(C_SOURCE_FILES))
C_PATHS = $(call remduplicates, $(dir $(C_SOURCE_FILES) ) )
C_OBJECTS = $(addprefix $(OBJECT_DIRECTORY)/, $(C_SOURCE_FILE_NAMES:.c=.o) )

ASM_SOURCE_FILE_NAMES = $(notdir $(ASM_SOURCE_FILES))
ASM_PATHS = $(call remduplicates, $(dir $(ASM_SOURCE_FILES) ))
ASM_OBJECTS = $(addprefix $(OBJECT_DIRECTORY)/, $(ASM_SOURCE_FILE_NAMES:.s=.o) )

vpath %.c $(C_PATHS)
vpath %.s $(ASM_PATHS)

OBJECTS = $(C_OBJECTS) $(ASM_OBJECTS)

modelm_bootloader: OUTPUT_FILENAME := modelm_bootloader
modelm_bootloader: ble_bootloader

ble60_bootloader: OUTPUT_FILENAME := ble60_bootloader
ble60_bootloader: ble_bootloader

ble_bootloader: LINKER_SCRIPT=dfu_gcc_nrf51.ld
ble_bootloader: $(BUILD_DIRECTORIES) $(OBJECTS)
	@echo Linking target: $(OUTPUT_FILENAME).out
	$(NO_ECHO)$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out
	$(NO_ECHO)$(MAKE) -f $(MAKEFILE_NAME) -C $(MAKEFILE_DIR) -e finalize

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
	@echo Flashing: $(OUTPUT_BINARY_DIRECTORY)/$<.hex
	nrfjprog --program $(OUTPUT_BINARY_DIRECTORY)/$<.hex -f nrf51  --chiperase
	nrfjprog --reset

flash_hex:
	@echo Flashing: $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).hex
	"$(OPENOCD_PATH)/$(OPENOCD_EXECUTABLE)" -f board/nrf51x22.cfg -c init -c "reset init" -c halt -c "program $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).hex verify reset exit"

flash_erase:
	@echo Mass erase all flash!
	"$(OPENOCD_PATH)/$(OPENOCD_EXECUTABLE)" -f board/nrf51x22.cfg -c init -c "reset init" -c "nrf51 mass_erase" -c exit

## Flash softdevice
flash_softdevice:
	@echo Flashing: s110_softdevice.hex
	"$(OPENOCD_PATH)/$(OPENOCD_EXECUTABLE)" -f board/nrf51x22.cfg -c init -c "reset init" -c halt -c "program ../../../sdk/s110_nrf51_8.0.0_softdevice.hex verify reset exit"

reset_target:
	@echo Resetting...
	"$(OPENOCD_PATH)/$(OPENOCD_EXECUTABLE)" -f board/nrf51x22.cfg -c init -c "reset run" -c exit

flash_bootloader: OUTPUT_FILENAME = modelm_bootloader
flash_bootloader: flash_erase flash_hex flash_softdevice

