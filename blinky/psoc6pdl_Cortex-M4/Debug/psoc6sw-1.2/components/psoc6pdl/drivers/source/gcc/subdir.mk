################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
/Applications/ModusToolbox_2.0/libraries/psoc6sw-1.2/components/psoc6pdl/drivers/source/gcc/cy_syslib_gcc.S 

OBJS += \
./psoc6sw-1.2/components/psoc6pdl/drivers/source/gcc/cy_syslib_gcc.o 

S_UPPER_DEPS += \
./psoc6sw-1.2/components/psoc6pdl/drivers/source/gcc/cy_syslib_gcc.d 


# Each subdirectory must supply rules for building sources it contributes
psoc6sw-1.2/components/psoc6pdl/drivers/source/gcc/cy_syslib_gcc.o: /Applications/ModusToolbox_2.0/libraries/psoc6sw-1.2/components/psoc6pdl/drivers/source/gcc/cy_syslib_gcc.S
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -Og -ffunction-sections -fdata-sections -Wall  -g3 -x assembler-with-cpp -DCY_DEVICE_COMMON -I"/Applications/ModusToolbox_2.0/libraries/psoc6sw-1.2/components/psoc6pdl/cmsis/include" -I"/Applications/ModusToolbox_2.0/libraries/psoc6sw-1.2/components/psoc6pdl/devices/psoc6/include" -I"/Applications/ModusToolbox_2.0/libraries/psoc6sw-1.2/components/psoc6pdl/drivers/include" -mfpu=fpv4-sp-d16 -ffat-lto-objects -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


