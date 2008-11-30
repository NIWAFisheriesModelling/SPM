################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/WorldSquares/CWorldSquare.cpp 

OBJS += \
./src/WorldSquares/CWorldSquare.o 

CPP_DEPS += \
./src/WorldSquares/CWorldSquare.d 


# Each subdirectory must supply rules for building sources it contributes
src/WorldSquares/%.o: ../src/WorldSquares/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DOPTIMISE -O3 -finline-functions -g3 -ggdb -Wall -c -fmessage-length=0 -mthreads -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


