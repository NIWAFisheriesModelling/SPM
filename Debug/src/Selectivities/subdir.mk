################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Selectivities/CConstantSelectivity.cpp \
../src/Selectivities/CDoubleNormalSelectivity.cpp \
../src/Selectivities/CKnifeEdgeSelectivity.cpp \
../src/Selectivities/CLogisticProducingSelectivity.cpp \
../src/Selectivities/CLogisticSelectivity.cpp \
../src/Selectivities/CSelectivity.cpp 

OBJS += \
./src/Selectivities/CConstantSelectivity.o \
./src/Selectivities/CDoubleNormalSelectivity.o \
./src/Selectivities/CKnifeEdgeSelectivity.o \
./src/Selectivities/CLogisticProducingSelectivity.o \
./src/Selectivities/CLogisticSelectivity.o \
./src/Selectivities/CSelectivity.o 

CPP_DEPS += \
./src/Selectivities/CConstantSelectivity.d \
./src/Selectivities/CDoubleNormalSelectivity.d \
./src/Selectivities/CKnifeEdgeSelectivity.d \
./src/Selectivities/CLogisticProducingSelectivity.d \
./src/Selectivities/CLogisticSelectivity.d \
./src/Selectivities/CSelectivity.d 


# Each subdirectory must supply rules for building sources it contributes
src/Selectivities/%.o: ../src/Selectivities/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DOPTIMISE -O3 -finline-functions -g3 -ggdb -Wall -c -fmessage-length=0 -mthreads -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


