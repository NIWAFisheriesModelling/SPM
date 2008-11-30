################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/RuntimeThread/CRuntimeThread.cpp 

OBJS += \
./src/RuntimeThread/CRuntimeThread.o 

CPP_DEPS += \
./src/RuntimeThread/CRuntimeThread.d 


# Each subdirectory must supply rules for building sources it contributes
src/RuntimeThread/%.o: ../src/RuntimeThread/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DOPTIMISE -O3 -finline-functions -g3 -ggdb -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


