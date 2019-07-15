################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include psoc6sw-1.2/components/psoc6pdl/devices/bsp/COMPONENT_MTB/startup/TOOLCHAIN_GCC_ARM/subdir.mk
-include psoc6sw-1.2/components/psoc6pdl/devices/bsp/COMPONENT_MTB/startup/subdir.mk
-include psoc6sw-1.2/components/psoc6cm0p/COMPONENT_CM0P_SLEEP/subdir.mk
-include Source/subdir.mk
-include GeneratedSource/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: BlinkyLED2_mainapp.elf secondary-outputs

dependents:
	-cd /Users/hdm/cypress/vscode/cortex-debug-samples/blink2/psoc6pdl_Cortex-M4/Debug && $(MAKE) all

# Tool invocations
BlinkyLED2_mainapp.elf: $(OBJS) $(USER_OBJS) /Users/hdm/cypress/vscode/cortex-debug-samples/blink2/psoc6pdl_Cortex-M4/Debug/libpsoc6pdl_Cortex-M4.a
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM Cross C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -Og -ffunction-sections -fdata-sections -Wall  -g3 -T "/Users/hdm/cypress/vscode/cortex-debug-samples/blink2/BlinkyLED2_mainapp/cy8c6xx7_cm4_dual.ld" -Xlinker --gc-sections -Wl,-Map,"BlinkyLED2_mainapp.map" --specs=nano.specs -ffat-lto-objects -g --enable-objc-gc -mfpu=fpv4-sp-d16 -o "BlinkyLED2_mainapp.elf" -Wl,--start-group $(OBJS) $(USER_OBJS) $(LIBS) -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) BlinkyLED2_mainapp.elf
	-@echo ' '

post-build:
	-/Applications/ModusToolbox_2.0/tools/modus-shell-1.0/bin/bash --norc --noprofile /Applications/ModusToolbox_2.0/libraries/psoc6sw-1.2/makefiles/platforms/PSoC6_cm4_dual/cymcuelftool_postbuild.bash /Applications/ModusToolbox_2.0/tools/cymcuelftool-1.0/bin/cymcuelftool /Users/hdm/cypress/vscode/cortex-debug-samples/blink2/BlinkyLED2_mainapp/Debug/BlinkyLED2_mainapp.elf
	-@echo ' '

secondary-outputs:

.PHONY: all clean dependents post-build
/Users/hdm/cypress/vscode/cortex-debug-samples/blink2/psoc6pdl_Cortex-M4/Debug/libpsoc6pdl_Cortex-M4.a:

-include ../makefile.targets
