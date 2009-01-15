################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Qs/CQ.cpp \
../src/Qs/CQManager.cpp 

OBJS += \
./src/Qs/CQ.o \
./src/Qs/CQManager.o 

CPP_DEPS += \
./src/Qs/CQ.d \
./src/Qs/CQManager.d 


# Each subdirectory must supply rules for building sources it contributes
src/Qs/%.o: ../src/Qs/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


