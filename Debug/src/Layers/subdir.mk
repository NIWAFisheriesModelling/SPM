################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Layers/CLayer.cpp \
../src/Layers/CNumericLayer.cpp \
../src/Layers/CStringLayer.cpp 

OBJS += \
./src/Layers/CLayer.o \
./src/Layers/CNumericLayer.o \
./src/Layers/CStringLayer.o 

CPP_DEPS += \
./src/Layers/CLayer.d \
./src/Layers/CNumericLayer.d \
./src/Layers/CStringLayer.d 


# Each subdirectory must supply rules for building sources it contributes
src/Layers/%.o: ../src/Layers/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DOPTIMISE -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


