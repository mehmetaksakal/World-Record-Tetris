################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/src/UART/ring_buffer.c \
../Drivers/src/UART/uart.c 

OBJS += \
./Drivers/src/UART/ring_buffer.o \
./Drivers/src/UART/uart.o 

C_DEPS += \
./Drivers/src/UART/ring_buffer.d \
./Drivers/src/UART/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/src/UART/%.o: ../Drivers/src/UART/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DNDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC11xx -I"C:\Users\Mehmet\Documents\LPCXpresso_7.4.0_229\TetCo\CMSISv2p00_LPC11xx\inc" -I"C:\Users\Mehmet\Documents\LPCXpresso_7.4.0_229\TetCo\Master\Application\inc" -I"C:\Users\Mehmet\Documents\LPCXpresso_7.4.0_229\TetCo\Master\Drivers\inc\CANopen" -I"C:\Users\Mehmet\Documents\LPCXpresso_7.4.0_229\TetCo\Master\Drivers\inc\UART" -Os -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


