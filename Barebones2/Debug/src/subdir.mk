################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/instruction_rw.cpp \
../src/packet.cpp \
../src/widget.cpp 

C_SRCS += \
../src/Graphics.c 

CC_SRCS += \
../src/main.cc 

OBJS += \
./src/Graphics.o \
./src/instruction_rw.o \
./src/main.o \
./src/packet.o \
./src/widget.o 

C_DEPS += \
./src/Graphics.d 

CC_DEPS += \
./src/main.d 

CPP_DEPS += \
./src/instruction_rw.d \
./src/packet.d \
./src/widget.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze g++ compiler
	mb-g++ -Wall -O0 -g3 -c -fmessage-length=0 -I../../Barebones2_bsp/microblaze_0/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.20.b -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '

src/%.o: ../src/%.cpp
	@echo Building file: $<
	@echo Invoking: MicroBlaze g++ compiler
	mb-g++ -Wall -O0 -g3 -c -fmessage-length=0 -I../../Barebones2_bsp/microblaze_0/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.20.b -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '

src/%.o: ../src/%.cc
	@echo Building file: $<
	@echo Invoking: MicroBlaze g++ compiler
	mb-g++ -Wall -O0 -g3 -c -fmessage-length=0 -I../../Barebones2_bsp/microblaze_0/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.20.b -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '


