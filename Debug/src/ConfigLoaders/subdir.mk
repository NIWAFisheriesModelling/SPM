################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ConfigLoaders/CBaseConfigLoader.cpp \
../src/ConfigLoaders/CEstimateValueConfigLoader.cpp \
../src/ConfigLoaders/CEstimationConfigLoader.cpp \
../src/ConfigLoaders/COutputConfigLoader.cpp \
../src/ConfigLoaders/CPopulationConfigLoader.cpp 

OBJS += \
./src/ConfigLoaders/CBaseConfigLoader.o \
./src/ConfigLoaders/CEstimateValueConfigLoader.o \
./src/ConfigLoaders/CEstimationConfigLoader.o \
./src/ConfigLoaders/COutputConfigLoader.o \
./src/ConfigLoaders/CPopulationConfigLoader.o 

CPP_DEPS += \
./src/ConfigLoaders/CBaseConfigLoader.d \
./src/ConfigLoaders/CEstimateValueConfigLoader.d \
./src/ConfigLoaders/CEstimationConfigLoader.d \
./src/ConfigLoaders/COutputConfigLoader.d \
./src/ConfigLoaders/CPopulationConfigLoader.d 


# Each subdirectory must supply rules for building sources it contributes
src/ConfigLoaders/%.o: ../src/ConfigLoaders/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DOPTIMISE -O3 -finline-functions -g3 -ggdb -Wall -c -fmessage-length=0 -mthreads -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


