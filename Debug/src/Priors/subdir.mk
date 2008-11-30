################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Priors/CBetaPrior.cpp \
../src/Priors/CLogNormalPrior.cpp \
../src/Priors/CNormalByStdevPrior.cpp \
../src/Priors/CNormalLogPrior.cpp \
../src/Priors/CNormalPrior.cpp \
../src/Priors/CPrior.cpp \
../src/Priors/CUniformLogPrior.cpp \
../src/Priors/CUniformPrior.cpp 

OBJS += \
./src/Priors/CBetaPrior.o \
./src/Priors/CLogNormalPrior.o \
./src/Priors/CNormalByStdevPrior.o \
./src/Priors/CNormalLogPrior.o \
./src/Priors/CNormalPrior.o \
./src/Priors/CPrior.o \
./src/Priors/CUniformLogPrior.o \
./src/Priors/CUniformPrior.o 

CPP_DEPS += \
./src/Priors/CBetaPrior.d \
./src/Priors/CLogNormalPrior.d \
./src/Priors/CNormalByStdevPrior.d \
./src/Priors/CNormalLogPrior.d \
./src/Priors/CNormalPrior.d \
./src/Priors/CPrior.d \
./src/Priors/CUniformLogPrior.d \
./src/Priors/CUniformPrior.d 


# Each subdirectory must supply rules for building sources it contributes
src/Priors/%.o: ../src/Priors/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DOPTIMISE -O3 -finline-functions -g3 -ggdb -Wall -c -fmessage-length=0 -mthreads -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


