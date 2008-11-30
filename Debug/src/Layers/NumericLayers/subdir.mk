################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Layers/NumericLayers/CAbundanceLayer.cpp \
../src/Layers/NumericLayers/CDistanceLayer.cpp \
../src/Layers/NumericLayers/CDoubleLayer.cpp 

OBJS += \
./src/Layers/NumericLayers/CAbundanceLayer.o \
./src/Layers/NumericLayers/CDistanceLayer.o \
./src/Layers/NumericLayers/CDoubleLayer.o 

CPP_DEPS += \
./src/Layers/NumericLayers/CAbundanceLayer.d \
./src/Layers/NumericLayers/CDistanceLayer.d \
./src/Layers/NumericLayers/CDoubleLayer.d 


# Each subdirectory must supply rules for building sources it contributes
src/Layers/NumericLayers/%.o: ../src/Layers/NumericLayers/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DOPTIMISE -O3 -finline-functions -g3 -ggdb -Wall -c -fmessage-length=0 -mthreads -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


