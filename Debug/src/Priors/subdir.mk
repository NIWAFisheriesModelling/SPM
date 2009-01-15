################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Priors/CPrior.cpp \
../src/Priors/CPriorManager.cpp 

OBJS += \
./src/Priors/CPrior.o \
./src/Priors/CPriorManager.o 

CPP_DEPS += \
./src/Priors/CPrior.d \
./src/Priors/CPriorManager.d 


# Each subdirectory must supply rules for building sources it contributes
src/Priors/%.o: ../src/Priors/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


