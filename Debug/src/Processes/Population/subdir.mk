################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Processes/Population/CAgeingProcess.cpp \
../src/Processes/Population/CCategoryTransitionProcess.cpp \
../src/Processes/Population/CEventMortalityProcess.cpp \
../src/Processes/Population/CNaturalMortalityProcess.cpp \
../src/Processes/Population/CRecruitmentProcess.cpp 

OBJS += \
./src/Processes/Population/CAgeingProcess.o \
./src/Processes/Population/CCategoryTransitionProcess.o \
./src/Processes/Population/CEventMortalityProcess.o \
./src/Processes/Population/CNaturalMortalityProcess.o \
./src/Processes/Population/CRecruitmentProcess.o 

CPP_DEPS += \
./src/Processes/Population/CAgeingProcess.d \
./src/Processes/Population/CCategoryTransitionProcess.d \
./src/Processes/Population/CEventMortalityProcess.d \
./src/Processes/Population/CNaturalMortalityProcess.d \
./src/Processes/Population/CRecruitmentProcess.d 


# Each subdirectory must supply rules for building sources it contributes
src/Processes/Population/%.o: ../src/Processes/Population/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DOPTIMISE -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


