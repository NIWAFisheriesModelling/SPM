################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/WorldSquares/WorldSquareCollection/CWorldSquareCollection.cpp 

OBJS += \
./src/WorldSquares/WorldSquareCollection/CWorldSquareCollection.o 

CPP_DEPS += \
./src/WorldSquares/WorldSquareCollection/CWorldSquareCollection.d 


# Each subdirectory must supply rules for building sources it contributes
src/WorldSquares/WorldSquareCollection/%.o: ../src/WorldSquares/WorldSquareCollection/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DOPTIMISE -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

