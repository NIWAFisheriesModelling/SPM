################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Observations/CObservation.cpp \
../src/Observations/CObservationManager.cpp 

OBJS += \
./src/Observations/CObservation.o \
./src/Observations/CObservationManager.o 

CPP_DEPS += \
./src/Observations/CObservation.d \
./src/Observations/CObservationManager.d 


# Each subdirectory must supply rules for building sources it contributes
src/Observations/%.o: ../src/Observations/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


