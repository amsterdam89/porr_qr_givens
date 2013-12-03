################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/FileReader/FileReader.c 

OBJS += \
./src/FileReader/FileReader.o 

C_DEPS += \
./src/FileReader/FileReader.d 


# Each subdirectory must supply rules for building sources it contributes
src/FileReader/%.o: ../src/FileReader/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


