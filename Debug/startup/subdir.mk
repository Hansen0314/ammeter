################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32.s 

OBJS += \
./startup/startup_stm32.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -I"G:/seeed/ammeter/software/ammeter/HAL_Driver/Inc/Legacy" -I"G:/seeed/ammeter/software/ammeter/inc" -I"G:/seeed/ammeter/software/ammeter/CMSIS/device" -I"G:/seeed/ammeter/software/ammeter/CMSIS/core" -I"G:/seeed/ammeter/software/ammeter/HAL_Driver/Inc" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


