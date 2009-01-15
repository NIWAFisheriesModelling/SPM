################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CConfiguration.cpp \
../src/CRuntimeController.cpp \
../src/Main.cpp 

OBJS += \
./src/CConfiguration.o \
./src/CRuntimeController.o \
./src/Main.o 

CPP_DEPS += \
./src/CConfiguration.d \
./src/CRuntimeController.d \
./src/Main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


