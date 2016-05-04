# Makefile for:
# SAMD21 based Arduino/Genuino products
# e.g. Arduino M0 Pro, Arduino Zero, Genuino Zero
#
# SAM3X based Arduino products
# e.g. Arduino DUE
#
# Author: Stuart Cording
#         iSYSTEM AG
#         21. Dez 2015

# Define default GCC compiler settings
#
# NOTE: DUE build uses gcc for linking; M0 Pro uses g++ for linking
#       No idea why the difference, just copying Arduino IDE default
#       usage for now.
#
CPP := arm-none-eabi-g++.exe
CC := arm-none-eabi-gcc.exe
AR := arm-none-eabi-ar.exe
ifeq ($(TARGET), ARDUINO_DUE)
LD := arm-none-eabi-gcc.exe
else
LD := arm-none-eabi-g++.exe
endif
OBJ := arm-none-eabi-objcopy.exe

# If provided, use compiler settings from developer
ifdef ARDUINO_GCC_PATH
CPP := $(ARDUINO_GCC_PATH)$(CPP)
CC := $(ARDUINO_GCC_PATH)$(CC)
LD := $(ARDUINO_GCC_PATH)$(LD)
AR := $(ARDUINO_GCC_PATH)$(AR)
OBJ:= $(ARDUINO_GCC_PATH)$(OBJ)
endif

# If provided, use install path for Arduino environment;
# otherwise provide a warning
ifndef ARDUINO_INSTALL_PATH

$(info Arduino installation path is undefined. Please define ARDUINO_INSTALL_PATH when calling make. See help for more info. Build will probably fail - sorry!)

endif

# If provided a choice of RELEASE, build a release version (currently
# same as debug version)
ifeq ($(BUILD),RELEASE)
OUTPUT_DIR := ./Release/
else
OUTPUT_DIR := ./Debug/
endif

# If defined, build for DUE, otherwise default is M0 Pro/Zero
# VARIANT_PATH is the path for the variant.c file
# AVR_PATH is the path for the dtostrf.c file
# CORE_PATH is the path to the Arduino environment files (main.cpp, Delay.cpp, etc.)
# USB_PATH is the path to files needed for USB running on the target MCU
# LD_PATH is path to linker description file for target
ifeq ($(TARGET),ARDUINO_DUE)
VARIANT_PATH := $(ARDUINO_INSTALL_PATH)hardware/arduino/sam/variants/arduino_due_x
AVR_PATH := $(ARDUINO_INSTALL_PATH)hardware/arduino/sam/cores/arduino/avr
CORE_PATH := $(ARDUINO_INSTALL_PATH)hardware/arduino/sam/cores/arduino
USB_PATH := $(ARDUINO_INSTALL_PATH)hardware/arduino/sam/cores/arduino/USB
LD_PATH := $(ARDUINO_INSTALL_PATH)hardware/arduino/sam/variants/arduino_due_x/linker_scripts/gcc/flash.ld

else

# Assume setting for Arduino M0 Pro
VARIANT_PATH := $(ARDUINO_INSTALL_PATH)hardware/arduino/samd/variants/arduino_zero
AVR_PATH := $(ARDUINO_INSTALL_PATH)hardware/arduino/samd/cores/arduino/avr
CORE_PATH := $(ARDUINO_INSTALL_PATH)hardware/arduino/samd/cores/arduino
USB_PATH := $(ARDUINO_INSTALL_PATH)hardware/arduino/samd/cores/arduino/USB
LD_PATH := $(ARDUINO_INSTALL_PATH)hardware/arduino/samd/variants/arduino_zero/linker_scripts/gcc/flash_with_bootloader.ld

endif

#################################################################################################
# Define paths to default Arduino libraries that might be used in a sketch
#################################################################################################

# AUDIO
ifeq ($(USE_AUDIO),TRUE)
ifeq ($(TARGET),ARDUINO_DUE)
# NOTE: This library only works with Arduino DUE
ARDUINO_LIBRARY_FILE_PATH_HEADERS := $(ARDUINO_LIBRARY_FILE_PATH_HEADERS) -I $(ARDUINO_INSTALL_PATH)libraries/Audio/src
ARDUINO_LIBRARY_OBJECTS := $(ARDUINO_LIBRARY_OBJECTS) Audio.o DAC.o
ARDUINO_LIBRARY_FILE_PATH_AUDIO_SOURCE := $(ARDUINO_INSTALL_PATH)libraries/Audio/src
else
$(info Audio library only works with Arduino DUE!)
endif
endif

# BRIDGE
# NOTE: Not supported as it is only used with Yun, Yun Mini, Industrial 101 and Tian
#LIBRARY_FILE_PATH_BRIDGE = $(ARDUINO_INSTALL_PATH)libraries/Bridge/src

# CIAO
# NOTE: Not supported as it is only used with Yun, Yun Mini, Industrial 101 and Tian
#LIBRARY_FILE_PATH_CIAO = $(ARDUINO_INSTALL_PATH)libraries/Ciao/src

# ESPLORA
# NOTE: Not supported as it is only used with Esplora
#LIBRARY_FILE_PATH_ESPLORA = $(ARDUINO_INSTALL_PATH)libraries/Esplora/src

# ETHERNET
ifeq ($(USE_ETHERNET),TRUE)
# NOTE: This library work with all Arduino boards
ARDUINO_LIBRARY_FILE_PATH_HEADERS := $(ARDUINO_LIBRARY_FILE_PATH_HEADERS) -I $(ARDUINO_INSTALL_PATH)libraries/Ethernet/src
ARDUINO_LIBRARY_FILE_PATH_HEADERS := $(ARDUINO_LIBRARY_FILE_PATH_HEADERS) -I $(ARDUINO_INSTALL_PATH)libraries/Ethernet/src/utility

ARDUINO_LIBRARY_OBJECTS := $(ARDUINO_LIBRARY_OBJECTS) Dhcp.o Dns.o Ethernet.o EthernetClient.o EthernetServer.o EthernetUdp.o socket.o w5100.o
ARDUINO_LIBRARY_FILE_PATH_ETHERNET_SOURCE := $(ARDUINO_INSTALL_PATH)libraries/Ethernet/src
ARDUINO_LIBRARY_FILE_PATH_ETHERNET_UTILITY_SOURCE := $(ARDUINO_INSTALL_PATH)libraries/Ethernet/src/utility
endif

# ETHERNET2
ifeq ($(USE_ETHERNET2),TRUE)
# NOTE: This library work with all Arduino boards and the new Ethernet Shield 2
ARDUINO_LIBRARY_FILE_PATH_HEADERS := $(ARDUINO_LIBRARY_FILE_PATH_HEADERS) -I $(ARDUINO_INSTALL_PATH)libraries/Ethernet2/src
ARDUINO_LIBRARY_FILE_PATH_HEADERS := $(ARDUINO_LIBRARY_FILE_PATH_HEADERS) -I $(ARDUINO_INSTALL_PATH)libraries/Ethernet2/src/utility

ARDUINO_LIBRARY_OBJECTS := $(ARDUINO_LIBRARY_OBJECTS) Dhcp.o Dns.o Ethernet2.o EthernetClient.o EthernetServer.o EthernetUdp2.o Twitter.o socket.o w5100.o
ARDUINO_LIBRARY_FILE_PATH_ETHERNET2_SOURCE := $(ARDUINO_INSTALL_PATH)libraries/Ethernet2/src
ARDUINO_LIBRARY_FILE_PATH_ETHERNET2_UTILITY_SOURCE := $(ARDUINO_INSTALL_PATH)libraries/Ethernet2/src/utility
endif

# FIRMATA
#LIBRARY_FILE_PATH_FIRMATA = $(ARDUINO_INSTALL_PATH)libraries/Firmata/src

# GSM
#LIBRARY_FILE_PATH_GSM = $(ARDUINO_INSTALL_PATH)libraries/GSM/src

# GSM2

# LIQUIDCRYSTAL
#LIBRARY_FILE_PATH_LIQUIDCRYSTAL = $(ARDUINO_INSTALL_PATH)libraries/LiquidCrystal/src

# NAXESMOTION
#LIBRARY_FILE_PATH_NAXESMOTION = $(ARDUINO_INSTALL_PATH)libraries/NAxesMotion/src

# ROBOT
# NOTE: Not supported as it is only used with Arduino Robot
#LIBRARY_FILE_PATH_ROBOT_CONTROL = $(ARDUINO_INSTALL_PATH)libraries/Robot_Control/src
#LIBRARY_FILE_PATH_ROBOT_MOTOR = $(ARDUINO_INSTALL_PATH)libraries/Robot_Motor/src
#LIBRARY_FILE_PATH_ROBOTIRREMOTE = $(ARDUINO_INSTALL_PATH)libraries/RobotIRremote/src

# RTC - SAMD21 only
#LIBRARY_FILE_PATH_RTC = $(ARDUINO_INSTALL_PATH)libraries/RTC/src

# SCHEDULER - DUE only
#LIBRARY_FILE_PATH_SCHEDULER = $(ARDUINO_INSTALL_PATH)libraries/Scheduler/src

# SD
#LIBRARY_FILE_PATH_SD = $(ARDUINO_INSTALL_PATH)libraries/SD/src

# SERVO
ifeq ($(USE_SERVO),TRUE)
ARDUINO_LIBRARY_FILE_PATH_HEADERS := $(ARDUINO_LIBRARY_FILE_PATH_HEADERS) -I $(ARDUINO_INSTALL_PATH)libraries/Servo/src
ARDUINO_LIBRARY_OBJECTS := $(ARDUINO_LIBRARY_OBJECTS) servo.o
ifeq ($(TARGET),ARDUINO_DUE)
ARDUINO_LIBRARY_FILE_PATH_SERVO_SOURCE := $(ARDUINO_INSTALL_PATH)libraries/Servo/src/sam
else
ARDUINO_LIBRARY_FILE_PATH_SERVO_SOURCE := $(ARDUINO_INSTALL_PATH)libraries/Servo/src/samd
endif
endif

# SPACEBREWYUN
# NOTE: Not supported as it is only used with Yun
#LIBRARY_FILE_PATH_SPACEBREWYUN = $(ARDUINO_INSTALL_PATH)libraries/SpacebrewYun/src

# STEPPER
#LIBRARY_FILE_PATH_STEPPER = $(ARDUINO_INSTALL_PATH)libraries/Stepper/src

# TEMBOO
# NOTE: Not supported as it is only used with Yun
#LIBRARY_FILE_PATH_TEMBOO = $(ARDUINO_INSTALL_PATH)libraries/Temboo/src

# TFT
#LIBRARY_FILE_PATH_TFT = $(ARDUINO_INSTALL_PATH)libraries/TFT/src

# USBHOST - Due only
#LIBRARY_FILE_PATH_USBHOST = $(ARDUINO_INSTALL_PATH)libraries/USBHost/src

# WIFI
#LIBRARY_FILE_PATH_WIFI = $(ARDUINO_INSTALL_PATH)libraries/WiFi/src


# Also search for .cpp files in the src directory
vpath %.cpp src

# Collect all source file names in the src directory
objects = $(patsubst ./src/%.cpp, %.o,$(wildcard ./src/*.cpp))

# Try to provide some information for user and for debug and support purposes
$(info )

ifeq ($(TARGET),ARDUINO_DUE)
$(info Building for Arduino DUE)
else
$(info No target defined - assuming Arduino M0 Pro)
# Define target as M0 Pro
TARGET = ARDUINO_M0_PRO
endif

$(info using the following settings)
$(info For g++ using - $(CPP))
$(info For gcc using - $(CC))
$(info For ar using - $(AR))
$(info Arduino environment installed here - $(ARDUINO_INSTALL_PATH))
$(info Source files are $(wildcard ./src/*.cpp))
$(info Object files are $(objects))
$(info Output destination is $(OUTPUT_DIR))
$(info )

ifeq ($(TARGET),ARDUINO_DUE)
#################################################################################################
# Flags for Arduino DUE
##########
# g++ flags
##########
CPPFLAGS = -c -g -Os -w -ffunction-sections -fdata-sections -nostdlib -fno-threadsafe-statics --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -MMD -mcpu=cortex-m3 -mthumb

# gcc flags
##########
CCFLAGS = -c -g -Os -w -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -MMD -mcpu=cortex-m3 -mthumb

# linker flags
##########
LDFLAGS = -Os -Wl,--gc-sections -mcpu=cortex-m3 -T$(LD_PATH) \
	-Wl,-Map,sketch.map -mthumb -Wl,--cref -Wl,--check-sections -Wl,--gc-sections \
	-Wl,--entry=Reset_Handler -Wl,--unresolved-symbols=report-all -Wl,--warn-common \
	-Wl,--warn-section-align -Wl,--warn-unresolved-symbols -lm -gcc
	
else

#################################################################################################
# Flags for Arduino M0 Pro
##########
# g++ flags
##########
CPPFLAGS = -c -g -Os -w -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -mcpu=cortex-m0plus -mthumb

# gcc flags
##########
CCFLAGS = -c -g -Os -w -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -mcpu=cortex-m0plus -mthumb 

# linker flags
##########
LDFLAGS = -Os -Wl,--gc-sections -save-temps -mcpu=cortex-m0plus -T$(LD_PATH) \
	-Wl,-Map,sketch.map -Wl,--start-group \
	-lm -lgcc -Wl,--end-group -mthumb -Wl,--cref -Wl,--check-sections -Wl,--gc-sections \
	-Wl,--entry=Reset_Handler -Wl,--unresolved-symbols=report-all -Wl,--warn-common \
	-Wl,--warn-section-align -Wl,--warn-unresolved-symbols -Wl,--section-start=.text=0x4000

endif

# archiver flags
##########
ARFLAGS = rcs

# object creation flags for binary files
##########
OBJFLAGSBIN = -O binary

# object creation flags for Intel hex files
##########
OBJFLAGSHEX = -O ihex -R .eeprom

ifeq ($(TARGET),ARDUINO_DUE)
#################################################################################################
# Defines name of syscalls for Arduino DUE
##########
SYSCALLS = syscalls_sam3

else
#################################################################################################
# Defines name of syscalls for Arduino M0 Pro
##########
SYSCALLS = syscalls

endif

ifeq ($(TARGET),ARDUINO_DUE)
#################################################################################################
# Defines for Arduino DUE
##########
CPPDEFINE = -Dprintf=iprintf -DF_CPU=84000000L -DARDUINO=10707 -DARDUINO_SAM_DUE -DARDUINO_ARCH_SAM \
	-D__SAM3X8E__ -DUSB_VID=0x2a03 -DUSB_PID=0x003e -DUSBCON \
	-DUSB_MANUFACTURER="\"Unknown\""
	
CCDEFINE = -Dprintf=iprintf -DF_CPU=84000000L -DARDUINO=10707 -DARDUINO_SAM_DUE -DARDUINO_ARCH_SAM \
	-D__SAM3X8E__ -DUSB_VID=0x2a03 -DUSB_PID=0x003e -DUSBCON -DUSB_MANUFACTURER="\"Unknown\"" \
	-DUSB_PRODUCT="\"Arduino Due\""

INCLUDE = -I $(ARDUINO_INSTALL_PATH)hardware/arduino/sam/system/libsam \
	-I $(ARDUINO_INSTALL_PATH)hardware/arduino/sam/system/CMSIS/CMSIS/Include \
	-I $(ARDUINO_INSTALL_PATH)hardware/arduino/sam/system/CMSIS/Device/ATMEL \
	-I $(ARDUINO_INSTALL_PATH)hardware/arduino/sam/cores/arduino \
	-I $(ARDUINO_INSTALL_PATH)hardware/arduino/sam/variants/arduino_due_x \
	$(ARDUINO_LIBRARY_FILE_PATH_HEADERS)

else

#################################################################################################
# Defines for Arduino M0 Pro
##########
CPPDEFINE = -Dprintf=iprintf -DF_CPU=48000000L -DARDUINO=10707 -DARDUINO_SAM_ZERO -DARDUINO_ARCH_SAMD \
	-D__SAMD21G18A__ -DUSB_VID=0x2a03 -DUSB_PID=0x804f -DUSBCON -DUSB_MANUFACTURER= \
	-DUSB_PRODUCT="\"Arduino M0 Pro\""

CCDEFINE = -Dprintf=iprintf -DF_CPU=48000000L -DARDUINO=10707 -DARDUINO_SAM_ZERO -DARDUINO_ARCH_SAMD \
	-D__SAMD21G18A__ -DUSB_VID=0x2a03 -DUSB_PID=0x804f -DUSBCON -DUSB_MANUFACTURER= \
	-DUSB_PRODUCT="\"Arduino M0 Pro\""

INCLUDE = -I $(ARDUINO_INSTALL_PATH)hardware/tools/CMSIS/CMSIS/Include \
	-I $(ARDUINO_INSTALL_PATH)hardware/tools/CMSIS/Device/ATMEL \
	-I $(ARDUINO_INSTALL_PATH)hardware/arduino/samd/cores/arduino \
	-I $(ARDUINO_INSTALL_PATH)hardware/arduino/samd/variants/arduino_zero \
	$(ARDUINO_LIBRARY_FILE_PATH_HEADERS)

endif

ifeq ($(TARGET),ARDUINO_DUE)
#################################################################################################
# Core objects for Arduino DUE
##########
CORE_OBJECTS = variant.o dtostrf.o cortex_handlers.o hooks.o iar_calls_sam3.o itoa.o \
	$(SYSCALLS).o \
	WInterrupts.o wiring.o wiring_analog.o wiring_digital.o wiring_shift.o \
	IPAddress.o main.o Print.o Reset.o RingBuffer.o Stream.o UARTClass.o USARTClass.o \
	CDC.o HID.o USBCore.o wiring_pulse.o WMath.o WString.o

else

#################################################################################################
# Core objects for Arduino M0 Pro
##########
CORE_OBJECTS = variant.o dtostrf.o delay.o hooks.o itoa.o startup.o $(SYSCALLS).o samd21_device.o \
	samd21_host.o WInterrupts.o wiring.o wiring_analog.o wiring_digital.o wiring_shift.o \
	IPAddress.o main.o Print.o Reset.o RingBuffer.o SERCOM.o Stream.o Tone.o Uart.o \
	CDC.o HID.o USBCore.o wiring_pulse.o WMath.o WString.o

endif

#################################################################################################
# Arduino Library Objects
#
# Here only required libraries will be added
##########
#ifdef USE_SERVO
#ARDUINO_LIBRARY_OBJECTS := $(ARDUINO_LIBRARY_OBJECTS) servo.o
#INCLUDE := $(INCLUDE) -I $(LIBRARY_FILE_PATH_SERVO)
#endif
ARDUINO_LIBRARY_ARCHIVE = libraries.a


ifeq ($(TARGET),ARDUINO_DUE)
#################################################################################################
# Link group for Arduino DUE
##########
LINK_GROUP = $(SYSCALLS).o $(objects) variant.o core.a $(VARIANT_PATH)/libsam_sam3x8e_gcc_rel.a \
	$(ARDUINO_LIBRARY_ARCHIVE)

else

#################################################################################################
# Link group for Arduino M0 Pro
##########
LINK_GROUP = $(SYSCALLS).o $(objects) variant.o core.a $(ARDUINO_LIBRARY_ARCHIVE)
#LINK_GROUP = $(SYSCALLS).o $(objects) variant.o core.a
	
endif

# $(info Variant path is $(VARIANT_PATH))

# VPATH = $(VARIANT_PATH)

# everything depends on sketch.elf
all : sketch.elf


bin : sketch.bin
	

hex : sketch.hex


sketch.bin : sketch.elf
	${OBJ} $(OBJFLAGSBIN) $(OUTPUT_DIR)$? $(OUTPUT_DIR)$@
	
sketch.hex : sketch.elf
	${OBJ} $(OBJFLAGSHEX) $(OUTPUT_DIR)$? $(OUTPUT_DIR)$@

# sketch.elf depends on all $(objects), core.a, variant.o and syscalls.o
#sketch.elf : $(objects) core.a libraries.a variant.o syscalls.o 
#	${LD} $(LDFLAGS) -Wl,--start-group $(LINK_GROUP) -Wl,--end-group \
#	-Wl,--section-start=.text=0x4000 -o $(OUTPUT_DIR)$@
sketch.elf : $(objects) core.a variant.o $(SYSCALLS).o $(ARDUINO_LIBRARY_ARCHIVE) 
	${LD} $(LDFLAGS) -Wl,--start-group $(LINK_GROUP) -Wl,--end-group -o $(OUTPUT_DIR)$@

# core.a depends on object files that are core to Arduino environment
core.a : $(CORE_OBJECTS)
	${AR} $(ARFLAGS) $@ $(CORE_OBJECTS)

# libraries.a depends on object files that are core to Arduino environment
libraries.a : $(ARDUINO_LIBRARY_OBJECTS)
	${AR} $(ARFLAGS) $@ $(ARDUINO_LIBRARY_OBJECTS)
	
# sketch.o depends on sketch.cpp
#sketch.o : sketch.cpp
#	${CPP} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@

# Compile any other source code in the home directory
%.o: %.cpp
	${CPP} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@

# variant.o depends on variant.cpp
variant.o : $(VARIANT_PATH)/variant.cpp
	${CPP} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@

# dtostrf.o depends on dtostrf.c
dtostrf.o : $(AVR_PATH)/dtostrf.c
	${CC} ${CCFLAGS} ${CCDEFINE} ${INCLUDE} $? -o $@

# delay.o depends on delay.c
delay.o : $(CORE_PATH)/delay.c
	${CC} ${CCFLAGS} ${CCDEFINE} ${INCLUDE} $? -o $@
	
# hooks.o depends on hooks.c
hooks.o : $(CORE_PATH)/hooks.c
	${CC} ${CCFLAGS} ${CCDEFINE} ${INCLUDE} $? -o $@
	
# itoa.o depends on itoa.c
itoa.o : $(CORE_PATH)/itoa.c
	${CC} ${CCFLAGS} ${CCDEFINE} ${INCLUDE} $? -o $@
	
# startup.o depends on startup.c
startup.o : $(CORE_PATH)/startup.c
	${CC} ${CCFLAGS} ${CCDEFINE} ${INCLUDE} $? -o $@
	
# syscalls.o depends on syscalls.c
$(SYSCALLS).o : $(CORE_PATH)/$(SYSCALLS).c
	${CC} ${CCFLAGS} ${CCDEFINE} ${INCLUDE} $? -o $@

# samd21_device.o depends on samd21_device.c
samd21_device.o : $(USB_PATH)/samd21_device.c
	${CC} ${CCFLAGS} ${CCDEFINE} ${INCLUDE} $? -o $@

# samd21_host.o depends on samd21_host.c
samd21_host.o : $(USB_PATH)/samd21_host.c
	${CC} ${CCFLAGS} ${CCDEFINE} ${INCLUDE} $? -o $@
	
# CDC.o depends on CDC.cpp
CDC.o : $(USB_PATH)/CDC.cpp
	${CPP} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@

# HID.o depends on HID.cpp
HID.o : $(USB_PATH)/HID.cpp
	${CPP} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@

# USBCore.o depends on USBCore.cpp
USBCore.o : $(USB_PATH)/USBCore.cpp
	${CPP} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@
	
# WInterrupts.o depends on WInterrupts.cpp
WInterrupts.o : $(CORE_PATH)/WInterrupts.c
	${CC} ${CCFLAGS} ${CCDEFINE} ${INCLUDE} $? -o $@
	
# wiring.o depends on wiring.cpp
wiring.o : $(CORE_PATH)/wiring.c
	${CC} ${CCFLAGS} ${CCDEFINE} ${INCLUDE} $? -o $@
	
# wiring_analog.o depends on wiring_analog.cpp
wiring_analog.o : $(CORE_PATH)/wiring_analog.c
	${CC} ${CCFLAGS} ${CCDEFINE} ${INCLUDE} $? -o $@
	
# wiring_digital.o depends on wiring_digital.cpp
wiring_digital.o : $(CORE_PATH)/wiring_digital.c
	${CC} ${CCFLAGS} ${CCDEFINE} ${INCLUDE} $? -o $@
	
# wiring_shift.o depends on wiring_shift.cpp
wiring_shift.o : $(CORE_PATH)/wiring_shift.c
	${CC} ${CCFLAGS} ${CCDEFINE} ${INCLUDE} $? -o $@

# IPAddress.o depends on IPAddress.cpp
IPAddress.o : $(CORE_PATH)/IPAddress.cpp
	${CPP} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@

# main.o depends on main.cpp
main.o : $(CORE_PATH)/main.cpp
	${CPP} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@

# Print.o depends on Print.cpp
Print.o : $(CORE_PATH)/Print.cpp
	${CPP} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@

# Reset.o depends on Reset.cpp
Reset.o : $(CORE_PATH)/Reset.cpp
	${CPP} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@

# RingBuffer.o depends on RingBuffer.cpp
RingBuffer.o : $(CORE_PATH)/RingBuffer.cpp
	${CPP} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@

# SERCOM.o depends on SERCOM.cpp
SERCOM.o : $(CORE_PATH)/SERCOM.cpp
	${CPP} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@

# Stream.o depends on Stream.cpp
Stream.o : $(CORE_PATH)/Stream.cpp
	${CPP} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@
	
# Tone.o depends on Tone.cpp
Tone.o : $(CORE_PATH)/Tone.cpp
	${CPP} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@

# Uart.o depends on Uart.cpp
Uart.o : $(CORE_PATH)/Uart.cpp
	${CPP} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@

# wiring_pulse.o depends on wiring_pulse.cpp
wiring_pulse.o : $(CORE_PATH)/wiring_pulse.cpp
	${CPP} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@

# WMath.o depends on WMath.cpp
WMath.o : $(CORE_PATH)/WMath.cpp
	${CPP} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@

# WString.o depends on WString.cpp
WString.o : $(CORE_PATH)/WString.cpp
	${CPP} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@

# cortex_handlers.o depends on cortex_handlers.c
cortex_handlers.o : $(CORE_PATH)/cortex_handlers.c
	${CC} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@
	
# iar_calls_sam3.o depends on iar_calls_sam3.c
iar_calls_sam3.o : $(CORE_PATH)/iar_calls_sam3.c
	${CC} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@

# UARTClass.o depends on UARTClass.cpp
UARTClass.o : $(CORE_PATH)/UARTClass.cpp
	${CPP} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@

# USARTClass.o depends on USARTClass.cpp
USARTClass.o : $(CORE_PATH)/USARTClass.cpp
	${CPP} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@
	
#####################################################################################################
# Build library files

# AUDIO
Audio.o : $(ARDUINO_LIBRARY_FILE_PATH_AUDIO_SOURCE)/Audio.cpp
	${CPP} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@
	
DAC.o : $(ARDUINO_LIBRARY_FILE_PATH_AUDIO_SOURCE)/DAC.cpp
	${CPP} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@

# ETHERNET
Dhcp.o : $(ARDUINO_LIBRARY_FILE_PATH_ETHERNET_SOURCE)/Dhcp.cpp
	${CPP} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@

Dns.o : $(ARDUINO_LIBRARY_FILE_PATH_ETHERNET_SOURCE)/Dns.cpp
	${CPP} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@

Ethernet.o : $(ARDUINO_LIBRARY_FILE_PATH_ETHERNET_SOURCE)/Ethernet.cpp
	${CPP} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@

EthernetClient.o : $(ARDUINO_LIBRARY_FILE_PATH_ETHERNET_SOURCE)/EthernetClient.cpp
	${CPP} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@

EthernetServer.o : $(ARDUINO_LIBRARY_FILE_PATH_ETHERNET_SOURCE)/EthernetServer.cpp
	${CPP} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@

EthernetUdp.o : $(ARDUINO_LIBRARY_FILE_PATH_ETHERNET_SOURCE)/EthernetUdp.cpp
	${CPP} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@

socket.o : $(ARDUINO_LIBRARY_FILE_PATH_ETHERNET_UTILITY_SOURCE)/socket.cpp
	${CPP} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@

w5100.o : $(ARDUINO_LIBRARY_FILE_PATH_ETHERNET_UTILITY_SOURCE)/w5100.cpp
	${CPP} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@

# ETHERNET2 - support for source not covered already by ETHERNET above
Ethernet2.o : $(ARDUINO_LIBRARY_FILE_PATH_ETHERNET_SOURCE)/Ethernet2.cpp
	${CPP} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@

EthernetUdp2.o : $(ARDUINO_LIBRARY_FILE_PATH_ETHERNET_SOURCE)/EthernetUdp2.cpp
	${CPP} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@

Twitter.o : $(ARDUINO_LIBRARY_FILE_PATH_ETHERNET_UTILITY_SOURCE)/Twitter.cpp
	${CPP} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@


# SERVO
servo.o : $(ARDUINO_LIBRARY_FILE_PATH_SERVO_SOURCE)/Servo.cpp
	${CPP} ${CPPFLAGS} ${CPPDEFINE} ${INCLUDE} $? -o $@

#####################################################################################################
# Clean up object, archive, map, elf, hex and bin files
.PHONY: clean	
clean :
	rm -f *.o
	rm -f *.a
	rm -f *.d
	rm -f *.map
	rm -f ./Debug/*.elf
	rm -f ./Debug/*.hex
	rm -f ./Debug/*.bin
	rm -f ./Release/*.hex
	rm -f ./Release/*.bin
	rm -f ./Release/*.elf

.PHONY: help
help :
	@echo Makefile for Arduino ARM Cortex-M based boards
	@echo
	@echo Builds projects using source code in directory ./src/
	@echo
	@echo Usage:
	@echo 
	@echo "make ARDUINO_TOOL_PATH=<path> ARDUINO_INSTALL_PATH=<path> TARGET=<ARDUINO_M0_PRO/ARDUINO_DUE> (BUILD=<DEBUG/RELEASE>) (TARGET=<ARDUINO_DUE/ARDUINO_M0_PRO>)"
	@echo
	@echo    Builds project from a sketch.cpp source and generates sketch.elf output
	@echo
	@echo "make ARDUINO_TOOL_PATH=<path> ARDUINO_INSTALL_PATH=<path> bin"
	@echo
	@echo    Builds project from a sketch.cpp source and generates sketch.elf and sketch.bin output
	@echo
	@echo "make ARDUINO_TOOL_PATH=<path> ARDUINO_INSTALL_PATH=<path> hex"
	@echo
	@echo    Builds project from a sketch.cpp source and generates sketch.elf and sketch.hex output
	@echo
	@echo "make clean"
	@echo
	@echo    Clean project to be rebuilt