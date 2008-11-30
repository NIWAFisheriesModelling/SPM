################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Minimizers/DESolver/CDESolverCallback.cpp \
../src/Minimizers/DESolver/CDESolverInterface.cpp \
../src/Minimizers/DESolver/DESolver.cpp 

OBJS += \
./src/Minimizers/DESolver/CDESolverCallback.o \
./src/Minimizers/DESolver/CDESolverInterface.o \
./src/Minimizers/DESolver/DESolver.o 

CPP_DEPS += \
./src/Minimizers/DESolver/CDESolverCallback.d \
./src/Minimizers/DESolver/CDESolverInterface.d \
./src/Minimizers/DESolver/DESolver.d 


# Each subdirectory must supply rules for building sources it contributes
src/Minimizers/DESolver/%.o: ../src/Minimizers/DESolver/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DOPTIMISE -O3 -finline-functions -g3 -ggdb -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


