################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/subdir.mk
-include src/WidgetCore/subdir.mk
-include src/Utilities/subdir.mk
-include src/GraphicsEngine/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
ELFSIZE += \
WidgetCore2.elf.size \

ELFCHECK += \
WidgetCore2.elf.elfcheck \


# All Target
all: WidgetCore2.elf secondary-outputs

# Tool invocations
WidgetCore2.elf: $(OBJS) ../src/lscript.ld $(USER_OBJS)
	@echo Building target: $@
	@echo Invoking: MicroBlaze gcc linker
	mb-gcc -Wl,-T -Wl,../src/lscript.ld -L../../WidgetCore2_bsp/microblaze_0/lib -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.20.b -mno-xl-soft-mul -o"WidgetCore2.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo Finished building target: $@
	@echo ' '

WidgetCore2.elf.size: WidgetCore2.elf
	@echo Invoking: MicroBlaze Print Size
	mb-size WidgetCore2.elf  |tee "WidgetCore2.elf.size"
	@echo Finished building: $@
	@echo ' '

WidgetCore2.elf.elfcheck: WidgetCore2.elf
	@echo Invoking: Xilinx ELF Check
	elfcheck WidgetCore2.elf -hw ../../GP_LAB_EDK_hw_platform/system.xml -pe microblaze_0  |tee "WidgetCore2.elf.elfcheck"
	@echo Finished building: $@
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES)$(ELFSIZE)$(ELFCHECK)$(S_UPPER_DEPS) WidgetCore2.elf
	-@echo ' '

secondary-outputs: $(ELFSIZE) $(ELFCHECK)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
