################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/MCMC/CMCMC.cpp 

OBJS += \
./src/MCMC/CMCMC.o 

CPP_DEPS += \
./src/MCMC/CMCMC.d 


# Each subdirectory must supply rules for building sources it contributes
src/MCMC/%.o: ../src/MCMC/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DOPTIMISE -O3 -finline-functions -g3 -ggdb -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


