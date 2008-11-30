################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Processes/Movement/CDirectedMovementProcess.cpp \
../src/Processes/Movement/CUniformMovementProcess.cpp 

OBJS += \
./src/Processes/Movement/CDirectedMovementProcess.o \
./src/Processes/Movement/CUniformMovementProcess.o 

CPP_DEPS += \
./src/Processes/Movement/CDirectedMovementProcess.d \
./src/Processes/Movement/CUniformMovementProcess.d 


# Each subdirectory must supply rules for building sources it contributes
src/Processes/Movement/%.o: ../src/Processes/Movement/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DOPTIMISE -O3 -finline-functions -g3 -ggdb -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


