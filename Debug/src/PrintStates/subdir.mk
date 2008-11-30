################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/PrintStates/CEstimatePrintState.cpp \
../src/PrintStates/CEstimateValuePrintState.cpp \
../src/PrintStates/CObjectivePrintState.cpp \
../src/PrintStates/CPrintState.cpp \
../src/PrintStates/CWorldGridPrintState.cpp 

OBJS += \
./src/PrintStates/CEstimatePrintState.o \
./src/PrintStates/CEstimateValuePrintState.o \
./src/PrintStates/CObjectivePrintState.o \
./src/PrintStates/CPrintState.o \
./src/PrintStates/CWorldGridPrintState.o 

CPP_DEPS += \
./src/PrintStates/CEstimatePrintState.d \
./src/PrintStates/CEstimateValuePrintState.d \
./src/PrintStates/CObjectivePrintState.d \
./src/PrintStates/CPrintState.d \
./src/PrintStates/CWorldGridPrintState.d 


# Each subdirectory must supply rules for building sources it contributes
src/PrintStates/%.o: ../src/PrintStates/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DOPTIMISE -O3 -finline-functions -g3 -ggdb -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


