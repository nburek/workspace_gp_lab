################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/WidgetCore/wsystem.c 

OBJS += \
./src/WidgetCore/wsystem.o 

C_DEPS += \
./src/WidgetCore/wsystem.d 


# Each subdirectory must supply rules for building sources it contributes
src/WidgetCore/%.o: ../src/WidgetCore/%.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -Os -c -fmessage-length=0 -I../../WidgetCore2_bsp/microblaze_0/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.20.b -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '


