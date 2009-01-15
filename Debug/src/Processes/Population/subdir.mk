################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Processes/Population/CAgeingProcess.cpp \
../src/Processes/Population/CAnnualMortalityRateProcess.cpp \
../src/Processes/Population/CBHRecruitmentProcess.cpp \
../src/Processes/Population/CBiomassEventMortalityProcess.cpp \
../src/Processes/Population/CCategoryTransitionProcess.cpp \
../src/Processes/Population/CCategoryTransitionRateProcess.cpp \
../src/Processes/Population/CConstantMortalityRateProcess.cpp \
../src/Processes/Population/CConstantRecruitmentProcess.cpp \
../src/Processes/Population/CEventMortalityProcess.cpp \
../src/Processes/Population/CNaturalMortalityProcess.cpp 

OBJS += \
./src/Processes/Population/CAgeingProcess.o \
./src/Processes/Population/CAnnualMortalityRateProcess.o \
./src/Processes/Population/CBHRecruitmentProcess.o \
./src/Processes/Population/CBiomassEventMortalityProcess.o \
./src/Processes/Population/CCategoryTransitionProcess.o \
./src/Processes/Population/CCategoryTransitionRateProcess.o \
./src/Processes/Population/CConstantMortalityRateProcess.o \
./src/Processes/Population/CConstantRecruitmentProcess.o \
./src/Processes/Population/CEventMortalityProcess.o \
./src/Processes/Population/CNaturalMortalityProcess.o 

CPP_DEPS += \
./src/Processes/Population/CAgeingProcess.d \
./src/Processes/Population/CAnnualMortalityRateProcess.d \
./src/Processes/Population/CBHRecruitmentProcess.d \
./src/Processes/Population/CBiomassEventMortalityProcess.d \
./src/Processes/Population/CCategoryTransitionProcess.d \
./src/Processes/Population/CCategoryTransitionRateProcess.d \
./src/Processes/Population/CConstantMortalityRateProcess.d \
./src/Processes/Population/CConstantRecruitmentProcess.d \
./src/Processes/Population/CEventMortalityProcess.d \
./src/Processes/Population/CNaturalMortalityProcess.d 


# Each subdirectory must supply rules for building sources it contributes
src/Processes/Population/%.o: ../src/Processes/Population/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


