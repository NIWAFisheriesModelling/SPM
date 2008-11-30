################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Observations/CAbundanceObservation.cpp \
../src/Observations/CObservation.cpp \
../src/Observations/CProportionsAtAgeObservation.cpp \
../src/Observations/CProportionsByCategoryObservation.cpp 

OBJS += \
./src/Observations/CAbundanceObservation.o \
./src/Observations/CObservation.o \
./src/Observations/CProportionsAtAgeObservation.o \
./src/Observations/CProportionsByCategoryObservation.o 

CPP_DEPS += \
./src/Observations/CAbundanceObservation.d \
./src/Observations/CObservation.d \
./src/Observations/CProportionsAtAgeObservation.d \
./src/Observations/CProportionsByCategoryObservation.d 


# Each subdirectory must supply rules for building sources it contributes
src/Observations/%.o: ../src/Observations/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DOPTIMISE -O3 -finline-functions -g3 -ggdb -Wall -c -fmessage-length=0 -mthreads -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


