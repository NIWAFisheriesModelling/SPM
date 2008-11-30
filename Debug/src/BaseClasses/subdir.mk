################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BaseClasses/CBaseBuildableObject.cpp \
../src/BaseClasses/CBaseExecutableObject.cpp \
../src/BaseClasses/CBaseObject.cpp 

OBJS += \
./src/BaseClasses/CBaseBuildableObject.o \
./src/BaseClasses/CBaseExecutableObject.o \
./src/BaseClasses/CBaseObject.o 

CPP_DEPS += \
./src/BaseClasses/CBaseBuildableObject.d \
./src/BaseClasses/CBaseExecutableObject.d \
./src/BaseClasses/CBaseObject.d 


# Each subdirectory must supply rules for building sources it contributes
src/BaseClasses/%.o: ../src/BaseClasses/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DOPTIMISE -O3 -finline-functions -g3 -ggdb -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


