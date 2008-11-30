################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/UnitTesting/TestDirectedProcesses.cpp \
../src/UnitTesting/TestLayers.cpp \
../src/UnitTesting/TestMovementProcessDirected.cpp \
../src/UnitTesting/TestMovementProcessUniform.cpp \
../src/UnitTesting/TestPopulationProcessAgeing.cpp \
../src/UnitTesting/TestPopulationProcessCategoryTransition.cpp \
../src/UnitTesting/TestPopulationProcessEventMortality.cpp \
../src/UnitTesting/TestPopulationProcessNaturalMortality.cpp \
../src/UnitTesting/TestPopulationProcessRecruitment.cpp \
../src/UnitTesting/TestSelectivities.cpp 

OBJS += \
./src/UnitTesting/TestDirectedProcesses.o \
./src/UnitTesting/TestLayers.o \
./src/UnitTesting/TestMovementProcessDirected.o \
./src/UnitTesting/TestMovementProcessUniform.o \
./src/UnitTesting/TestPopulationProcessAgeing.o \
./src/UnitTesting/TestPopulationProcessCategoryTransition.o \
./src/UnitTesting/TestPopulationProcessEventMortality.o \
./src/UnitTesting/TestPopulationProcessNaturalMortality.o \
./src/UnitTesting/TestPopulationProcessRecruitment.o \
./src/UnitTesting/TestSelectivities.o 

CPP_DEPS += \
./src/UnitTesting/TestDirectedProcesses.d \
./src/UnitTesting/TestLayers.d \
./src/UnitTesting/TestMovementProcessDirected.d \
./src/UnitTesting/TestMovementProcessUniform.d \
./src/UnitTesting/TestPopulationProcessAgeing.d \
./src/UnitTesting/TestPopulationProcessCategoryTransition.d \
./src/UnitTesting/TestPopulationProcessEventMortality.d \
./src/UnitTesting/TestPopulationProcessNaturalMortality.d \
./src/UnitTesting/TestPopulationProcessRecruitment.d \
./src/UnitTesting/TestSelectivities.d 


# Each subdirectory must supply rules for building sources it contributes
src/UnitTesting/%.o: ../src/UnitTesting/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DOPTIMISE -O3 -finline-functions -g3 -ggdb -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


