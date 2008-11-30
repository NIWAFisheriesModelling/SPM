################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Processes/CMovementProcess.cpp \
../src/Processes/CProcess.cpp 

OBJS += \
./src/Processes/CMovementProcess.o \
./src/Processes/CProcess.o 

CPP_DEPS += \
./src/Processes/CMovementProcess.d \
./src/Processes/CProcess.d 


# Each subdirectory must supply rules for building sources it contributes
src/Processes/%.o: ../src/Processes/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DOPTIMISE -O3 -finline-functions -g3 -ggdb -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


