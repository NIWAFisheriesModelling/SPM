################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AgeingError/CAgeingError.cpp 

OBJS += \
./src/AgeingError/CAgeingError.o 

CPP_DEPS += \
./src/AgeingError/CAgeingError.d 


# Each subdirectory must supply rules for building sources it contributes
src/AgeingError/%.o: ../src/AgeingError/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DOPTIMISE -O3 -finline-functions -g3 -ggdb -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


