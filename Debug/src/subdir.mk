################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c \
../src/stm32l0xx_it.c \
../src/syscalls.c \
../src/system_stm32l0xx.c 

OBJS += \
./src/main.o \
./src/stm32l0xx_it.o \
./src/syscalls.o \
./src/system_stm32l0xx.o 

C_DEPS += \
./src/main.d \
./src/stm32l0xx_it.d \
./src/syscalls.d \
./src/system_stm32l0xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -DSTM32 -DSTM32L0 -DSTM32L011F3Px -DDEBUG -DSTM32L011xx -DUSE_HAL_DRIVER -I"G:/seeed/ammeter/software/ammeter/HAL_Driver/Inc/Legacy" -I"G:/seeed/ammeter/software/ammeter/inc" -I"G:/seeed/ammeter/software/ammeter/CMSIS/device" -I"G:/seeed/ammeter/software/ammeter/CMSIS/core" -I"G:/seeed/ammeter/software/ammeter/HAL_Driver/Inc" -I"G:/seeed/ammeter/software/ammeter/BSP/Inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


