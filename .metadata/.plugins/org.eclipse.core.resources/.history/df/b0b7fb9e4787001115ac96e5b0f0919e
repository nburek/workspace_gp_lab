################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
ELFSIZE += \
Barebones2.elf.size \

ELFCHECK += \
Barebones2.elf.elfcheck \


# All Target
all: Barebones2.elf secondary-outputs

# Tool invocations
Barebones2.elf: $(OBJS)  $(USER_OBJS)
	@echo Building target: $@
	@echo Invoking: MicroBlaze g++ linker
	mb-g++ -L../../Barebones2_bsp/microblaze_0/lib -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.20.b -mno-xl-soft-mul -o"Barebones2.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo Finished building target: $@
	@echo ' '

Barebones2.elf.size: Barebones2.elf
	@echo Invoking: MicroBlaze Print Size
	mb-size Barebones2.elf  |tee "Barebones2.elf.size"
	@echo Finished building: $@
	@echo ' '

Barebones2.elf.elfcheck: Barebones2.elf
	@echo Invoking: Xilinx ELF Check
	elfcheck Barebones2.elf -hw ../../GP_LAB_EDK_hw_platform/system.xml -pe microblaze_0  |tee "Barebones2.elf.elfcheck"
	@echo Finished building: $@
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(ELFSIZE)$(CXX_DEPS)$(C_UPPER_DEPS)$(ELFCHECK)$(S_UPPER_DEPS) Barebones2.elf
	-@echo ' '

secondary-outputs: $(ELFSIZE) $(ELFCHECK)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
