################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/src/LED/subdir.mk
-include Drivers/src/GPIO/subdir.mk
-include Drivers/src/CANopen/subdir.mk
-include Drivers/src/ADC/subdir.mk
-include Application/src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Slave.axf

# Tool invocations
Slave.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\Mehmet\Documents\LPCXpresso_7.4.0_229\TetCo\CMSISv2p00_LPC11xx\Release" -Xlinker -Map="Slave.map" -Xlinker --gc-sections -mcpu=cortex-m0 -mthumb -T "Slave_Release.ld" -o "Slave.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) Slave.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "Slave.axf"; # arm-none-eabi-objcopy -O binary "Slave.axf" "Slave.bin" ; checksum -p LPC11C24_301 -d "Slave.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
