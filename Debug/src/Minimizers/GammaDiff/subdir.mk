################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Minimizers/GammaDiff/CGammaDiffCallback.cpp \
../src/Minimizers/GammaDiff/CGammaDiffInterface.cpp \
../src/Minimizers/GammaDiff/FMM.cpp \
../src/Minimizers/GammaDiff/GammaDiff.cpp 

OBJS += \
./src/Minimizers/GammaDiff/CGammaDiffCallback.o \
./src/Minimizers/GammaDiff/CGammaDiffInterface.o \
./src/Minimizers/GammaDiff/FMM.o \
./src/Minimizers/GammaDiff/GammaDiff.o 

CPP_DEPS += \
./src/Minimizers/GammaDiff/CGammaDiffCallback.d \
./src/Minimizers/GammaDiff/CGammaDiffInterface.d \
./src/Minimizers/GammaDiff/FMM.d \
./src/Minimizers/GammaDiff/GammaDiff.d 


# Each subdirectory must supply rules for building sources it contributes
src/Minimizers/GammaDiff/%.o: ../src/Minimizers/GammaDiff/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DOPTIMISE -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


