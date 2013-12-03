################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/QRGivensRotations/QRGivensRotations.c 

OBJS += \
./src/QRGivensRotations/QRGivensRotations.o 

C_DEPS += \
./src/QRGivensRotations/QRGivensRotations.d 


# Each subdirectory must supply rules for building sources it contributes
src/QRGivensRotations/%.o: ../src/QRGivensRotations/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


