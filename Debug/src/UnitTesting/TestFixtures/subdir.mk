################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/UnitTesting/TestFixtures/CAgeingTestFixture.cpp \
../src/UnitTesting/TestFixtures/CBaseTestFixture.cpp \
../src/UnitTesting/TestFixtures/CCategoryTransitionTestFixture.cpp \
../src/UnitTesting/TestFixtures/CDirectedMovementTestFixture.cpp \
../src/UnitTesting/TestFixtures/CEventMortalityTestFixture.cpp \
../src/UnitTesting/TestFixtures/CNaturalMortalityTestFixture.cpp \
../src/UnitTesting/TestFixtures/CRecruitmentTestFixture.cpp \
../src/UnitTesting/TestFixtures/CUniformMovementTestFixture.cpp 

OBJS += \
./src/UnitTesting/TestFixtures/CAgeingTestFixture.o \
./src/UnitTesting/TestFixtures/CBaseTestFixture.o \
./src/UnitTesting/TestFixtures/CCategoryTransitionTestFixture.o \
./src/UnitTesting/TestFixtures/CDirectedMovementTestFixture.o \
./src/UnitTesting/TestFixtures/CEventMortalityTestFixture.o \
./src/UnitTesting/TestFixtures/CNaturalMortalityTestFixture.o \
./src/UnitTesting/TestFixtures/CRecruitmentTestFixture.o \
./src/UnitTesting/TestFixtures/CUniformMovementTestFixture.o 

CPP_DEPS += \
./src/UnitTesting/TestFixtures/CAgeingTestFixture.d \
./src/UnitTesting/TestFixtures/CBaseTestFixture.d \
./src/UnitTesting/TestFixtures/CCategoryTransitionTestFixture.d \
./src/UnitTesting/TestFixtures/CDirectedMovementTestFixture.d \
./src/UnitTesting/TestFixtures/CEventMortalityTestFixture.d \
./src/UnitTesting/TestFixtures/CNaturalMortalityTestFixture.d \
./src/UnitTesting/TestFixtures/CRecruitmentTestFixture.d \
./src/UnitTesting/TestFixtures/CUniformMovementTestFixture.d 


# Each subdirectory must supply rules for building sources it contributes
src/UnitTesting/TestFixtures/%.o: ../src/UnitTesting/TestFixtures/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DOPTIMISE -O3 -finline-functions -g3 -ggdb -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


