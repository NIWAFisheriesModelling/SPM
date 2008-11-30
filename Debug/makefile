################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/WorldSquares/WorldSquareCollection/subdir.mk
-include src/WorldSquares/subdir.mk
-include src/UnitTesting/subdir.mk
-include src/UnitTesting/TestFixtures/subdir.mk
-include src/TimeSteps/subdir.mk
-include src/Selectivities/subdir.mk
-include src/RuntimeThread/subdir.mk
-include src/Qs/subdir.mk
-include src/Profiles/subdir.mk
-include src/Processes/Population/subdir.mk
-include src/Processes/Movement/subdir.mk
-include src/Processes/subdir.mk
-include src/Priors/subdir.mk
-include src/PrintStates/subdir.mk
-include src/Penalties/subdir.mk
-include src/ParameterParser/subdir.mk
-include src/Observations/subdir.mk
-include src/ObjectiveFunction/subdir.mk
-include src/Minimizers/GammaDiff/subdir.mk
-include src/Minimizers/DESolver/subdir.mk
-include src/Minimizers/subdir.mk
-include src/subdir.mk
-include src/MCMC/subdir.mk
-include src/Layers/NumericLayers/subdir.mk
-include src/Layers/subdir.mk
-include src/Estimates/subdir.mk
-include src/DirectedProcesses/subdir.mk
-include src/ConfigLoaders/subdir.mk
-include src/BaseClasses/subdir.mk
-include src/AgeingError/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: pre-build main-build

# Main-build Target
main-build: SFM.exe

# Tool invocations
SFM.exe: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MinGW C++ Linker'
	g++ -L"" -o"SFM.exe" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) SFM.exe
	-@echo ' '

pre-build:
	-svnrev -o"..\src\Version.h" -i ../src/*.cpp ../src/*.h
	-@echo ' '

post-build:
	-C:\Windows\System32\cmd.exe /C copy "C:\Work\Workspaces\SimFish\SimFish\Debug\SFM.exe" "C:\work"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: main-build pre-build post-build

-include ../makefile.targets
