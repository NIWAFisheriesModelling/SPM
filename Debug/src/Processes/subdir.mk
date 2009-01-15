################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Processes/CProcess.cpp \
../src/Processes/CProcessManager.cpp 

OBJS += \
./src/Processes/CProcess.o \
./src/Processes/CProcessManager.o 

CPP_DEPS += \
./src/Processes/CProcess.d \
./src/Processes/CProcessManager.d 


# Each subdirectory must supply rules for building sources it contributes
src/Processes/%.o: ../src/Processes/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


