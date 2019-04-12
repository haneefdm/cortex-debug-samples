
SDK_ROOT=/Applications/ModusToolbox_1.0
#SDK_ROOT=C:/Users/hdm/ModusToolbox_1.0

# NOTE: These aren't normally pre-compiled, but I borrowed these from ModusToolbox (created a project, copied them here) to
# simplify things for cortex-debug evaluation purposes.
PRE_COMPILED= \
	pre-compiled/startup_psoc6_01_cm4.o \
	pre-compiled/system_psoc6_cm4.o \
	-Wl,--start-group \
		pre-compiled/BlinkyLED_config_cm4.a \
		pre-compiled/PSOC6_PDL.a \
	-Wl,--end-group

build: main_final.elf

clean:
	rm -f *.elf main.o

CFLAGS=-mcpu=cortex-m4 -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -O0 -mthumb -ffunction-sections -fdata-sections -ffat-lto-objects -g -Wall -DCY8C6137BZI_F54 -DDEBUG

LDFLAGS=\
	-mthumb \
	-ffunction-sections \
	-fdata-sections \
	-ffat-lto-objects \
	-O0 \
	-g \
	--enable-objc-gc \
	--specs=nano.specs \
	-Wl,--gc-sections  \
	-mcpu=cortex-m4 \
	-mfloat-abi=softfp \
	-mfpu=fpv4-sp-d16 \
	-T$(SDK_ROOT)/libraries/psoc6sw-1.0/components/psoc6pdl/devices/psoc6/linker/gcc/cy8c6xx7_cm4_dual.ld \
	$(PRE_COMPILED)

main_final.elf: main.elf
	$(SDK_ROOT)/tools/modus-shell-1.0/bin/bash --norc --noprofile $(SDK_ROOT)/libraries/psoc6sw-1.0/makefiles/platforms/PSOC6_DUAL_CORE/cymcuelftool_postbuild.bash $(SDK_ROOT)/tools/cymcuelftool-1.0/bin/cymcuelftool pre-compiled/cm0p.elf $< ARM_CM4

main.elf: main.o 
	arm-none-eabi-gcc -o $@ $(LDFLAGS) $^

main.o: main.c
	arm-none-eabi-gcc -c $< -o $@ $(CFLAGS)

