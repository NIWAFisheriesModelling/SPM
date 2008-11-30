################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Profiles/CProfile.cpp 

OBJS += \
./src/Profiles/CProfile.o 

CPP_DEPS += \
./src/Profiles/CProfile.d 


# Each subdirectory must supply rules for building sources it contributes
src/Profiles/%.o: ../src/Profiles/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DOPTIMISE -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


