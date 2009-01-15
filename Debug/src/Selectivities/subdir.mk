################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Selectivities/CSelectivity.cpp \
../src/Selectivities/CSelectivityManager.cpp 

OBJS += \
./src/Selectivities/CSelectivity.o \
./src/Selectivities/CSelectivityManager.o 

CPP_DEPS += \
./src/Selectivities/CSelectivity.d \
./src/Selectivities/CSelectivityManager.d 


# Each subdirectory must supply rules for building sources it contributes
src/Selectivities/%.o: ../src/Selectivities/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


