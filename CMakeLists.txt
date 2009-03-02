cmake_minimum_required(VERSION 2.6) project(SPM)

# To build the list below I used MSYS
# By executing the following command I could store the names of all
# .cpp files in a txt file. Then use a simple find/replace from .cpp to ""
# find | grep ".cpp" | grep -v "svn" | grep -v ".Test." | grep -v "UnitTest"

SET(LIBRARY_NAME SimFish)
SET(MAIN_NAME SPM_UnOptimised)
SET(TEST_NAME SPM_UnitTests)
SET(OPTI_NAME SPM)

# Added autogeneration of Version.h file in src directory
ADD_CUSTOM_COMMAND(
  OUTPUT SVN
  COMMAND svn_version --quiet --format c++ m--path ${PROJECT_SOURCE_DIR} --recursive --output ${PROJECT_SOURCE_DIR}/src/Version.h
)
ADD_CUSTOM_TARGET(version ALL DEPENDS SVN)

ADD_LIBRARY(${LIBRARY_NAME}
 src/BaseClasses/CBaseBuild
 src/BaseClasses/CBaseExecute
 src/BaseClasses/CBaseManager
 src/BaseClasses/CBaseObject
 src/BaseClasses/CBaseValidate
 src/BaseClasses/ParameterList/CParameterList
 src/Catchabilities/CCatchability
 src/Catchabilities/CCatchabilityManager
 src/Catchabilities/Factory/CCatchabilityFactory
 src/CConfiguration
 src/ConfigurationLoaders/CConfigurationLoader
 src/CRuntimeController
 src/Estimates/CEstimate
 src/Estimates/CEstimateManager
 src/Estimates/Factory/CEstimateFactory
 src/Helpers/CComparer
 src/Helpers/CConvertor
 src/Helpers/CError
 src/Helpers/CMath
 src/InitializationPhases/CInitializationPhase
 src/InitializationPhases/CInitializationPhaseManager
 src/InitializationPhases/Factory/CInitializationPhaseFactory
 src/Layers/CLayer
 src/Layers/CLayerManager
 src/Layers/Factory/CLayerFactory
 src/Layers/MetaLayer/CMetaLayer
 src/Layers/Numeric/Base/CNumericLayer
 src/Layers/Numeric/CAbundanceDensityLayer
 src/Layers/Numeric/CAbundanceLayer
 src/Layers/Numeric/CBiomassDensityLayer
 src/Layers/Numeric/CBiomassLayer
 src/Layers/Numeric/CDistanceLayer
 src/Layers/Numeric/CDoubleLayer
 src/Layers/String/CStringLayer
 src/MCMC/CMCMC
 src/Minimizers/CMinimizer
 src/Minimizers/CMinimizerManager
 src/Minimizers/DESolver/CDESolver
 src/Minimizers/DESolver/CDESolverCallback
 src/Minimizers/DESolver/Engine/DESolverEngine
 src/Minimizers/Factory/CMinimizerFactory
 src/Minimizers/GammaDiff/CGammaDiff
 src/Minimizers/GammaDiff/CGammaDiffCallback
 src/Minimizers/GammaDiff/Engine/FMM
 src/Minimizers/GammaDiff/Engine/GammaDiffEngine
 src/ObjectiveFunction/CObjectiveFunction
 src/Observations/Children/CAbundanceObservation
 src/Observations/Children/CProportionsAtAgeObservation
 src/Observations/Children/CProportionsByCategoryObservation
 src/Observations/CObservation
 src/Observations/CObservationManager
 src/Observations/Factory/CObservationFactory
 src/ParameterParser/CParamParser
 src/Penalties/CPenalty
 src/Penalties/CPenaltyManager
 src/Penalties/Factory/CPenaltyFactory
 src/PreferenceFunctions/Children/CConstantPreferenceFunction
 src/PreferenceFunctions/Children/CDoubleNormalPreferenceFunction
 src/PreferenceFunctions/Children/CExponentialPreferenceFunction
 src/PreferenceFunctions/Children/CInverseLogisticPreferenceFunction
 src/PreferenceFunctions/Children/CLogisticPreferenceFunction
 src/PreferenceFunctions/Children/CNormalPreferenceFunction
 src/PreferenceFunctions/Children/CThresholdBiomassPreferenceFunction
 src/PreferenceFunctions/Children/CThresholdPreferenceFunction
 src/PreferenceFunctions/CPreferenceFunction
 src/PreferenceFunctions/CPreferenceFunctionManager
 src/PreferenceFunctions/Factory/CPreferenceFunctionFactory
 src/Priors/Children/CBetaPrior
 src/Priors/Children/CLogNormalPrior
 src/Priors/Children/CNormalByStdevPrior
 src/Priors/Children/CNormalLogPrior
 src/Priors/Children/CNormalPrior
 src/Priors/Children/CUniformLogPrior
 src/Priors/Children/CUniformPrior
 src/Priors/CPrior
 src/Priors/CPriorManager
 src/Priors/Factory/CPriorFactory
 src/Processes/CProcess
 src/Processes/CProcessManager
 src/Processes/Factory/CProcessFactory
 src/Processes/Movement/Base/CMovementProcess
 src/Processes/Movement/CPreferenceMovementProcess
 src/Processes/Movement/CUniformMovementProcess
 src/Processes/Population/CAgeingProcess
 src/Processes/Population/CAnnualMortalityRateProcess
 src/Processes/Population/CBHRecruitmentProcess
 src/Processes/Population/CBiomassEventMortalityProcess
 src/Processes/Population/CCategoryTransitionProcess
 src/Processes/Population/CCategoryTransitionRateProcess
 src/Processes/Population/CConstantMortalityRateProcess
 src/Processes/Population/CConstantRecruitmentProcess
 src/Processes/Population/CEventMortalityProcess
 src/Processes/Population/CNaturalMortalityProcess
 src/Profiles/CProfile
 src/Profiles/CProfileManager
 src/Profiles/Factory/CProfileFactory
 src/Reporters/Children/Base/CFileReporter
 src/Reporters/Children/CEstimateSummaryReporter
 src/Reporters/Children/CObjectiveFunctionReporter
 src/Reporters/Children/CStandardHeaderReporter
 src/Reporters/Children/CWorldStateReporter
 src/Reporters/CReporter
 src/Reporters/CReporterManager
 src/Reporters/Factory/CReporterFactory
 src/RuntimeThread/CRuntimeThread
 src/Selectivities/Children/Base/CCachedSelectivity
 src/Selectivities/Children/CAllValuesBoundedSelectivity
 src/Selectivities/Children/CAllValuesSelectivity
 src/Selectivities/Children/CConstantSelectivity
 src/Selectivities/Children/CDoubleExponentialSelectivity
 src/Selectivities/Children/CDoubleNormalSelectivity
 src/Selectivities/Children/CIncreasingSelectivity
 src/Selectivities/Children/CKnifeEdgeSelectivity
 src/Selectivities/Children/CLogisticProducingSelectivity
 src/Selectivities/Children/CLogisticSelectivity
 src/Selectivities/CSelectivity
 src/Selectivities/CSelectivityManager
 src/Selectivities/Factory/CSelectivityFactory
 src/TimeSteps/CTimeStep
 src/TimeSteps/CTimeStepManager
 src/TimeSteps/Factory/CTimeStepFactory
 src/World/CWorld
 src/World/CWorldSquare
 src/World/WorldSquareCollection/CWorldSquareCollection
)

SET_TARGET_PROPERTIES(${LIBRARY_NAME} PROPERTIES COMPILE_FLAGS "-O0 -g3 -ggdb -Wall -fmessage-length=0" )

SET(MAIN_LIBRARIES  libboost_system-mgw34-mt-1_38 libboost_filesystem-mgw34-mt-1_38 libboost_thread-mgw34-mt-1_38 libboost_program_options-mgw34-mt-1_38)

SET(TEST_LIBRARIES libboost_unit_test_framework-mgw34-mt-sd-1_38)
ADD_EXECUTABLE(${MAIN_NAME}
 src/Main
)

SET_TARGET_PROPERTIES(${MAIN_NAME} PROPERTIES COMPILE_FLAGS "-O0 -g3 -Wall -fmessage-length=0")

TARGET_LINK_LIBRARIES(${MAIN_NAME} ${LIBRARY_NAME} ${MAIN_LIBRARIES})

ADD_EXECUTABLE(${TEST_NAME}
src/Catchabilities/Factory/CCatchabilityFactory.Test.cpp
src/Estimates/Factory/CEstimateFactory.Test.cpp
src/InitializationPhases/Factory/CInitializationPhaseFactory.Test.cpp
src/Layers/Factory/CLayerFactory.Test.cpp src/Minimizers/Factory/CMinimizerFactory.Test.cpp
src/Observations/Factory/CObservationFactory.Test.cpp src/Penalties/Factory/CPenaltyFactory.Test.cpp
src/PreferenceFunctions/Children/CConstantPreferenceFunction.Test.cpp
src/PreferenceFunctions/Children/CDoubleNormalPreferenceFunction.Test.cpp
src/PreferenceFunctions/Children/CExponentialPreferenceFunction.Test.cpp
src/PreferenceFunctions/Children/CInverseLogisticPreferenceFunction.Test.cpp
src/PreferenceFunctions/Children/CLogisticPreferenceFunction.Test.cpp
src/PreferenceFunctions/Children/CNormalPreferenceFunction.Test.cpp
src/PreferenceFunctions/Factory/CPreferenceFunctionFactory.Test.cpp
src/Priors/Factory/CPriorFactory.Test.cpp
src/Profiles/Factory/CProfileFactory.Test.cpp
src/Selectivities/Children/CConstantSelectivity.Test.cpp
src/Selectivities/Children/CDoubleNormalSelectivity.Test.cpp
src/Selectivities/Children/CKnifeEdgeSelectivity.Test.cpp
src/Selectivities/Children/CLogisticProducingSelectivity.Test.cpp
src/Selectivities/Children/CLogisticSelectivity.Test.cpp
src/Selectivities/Factory/CSelectivityFactory.Test.cpp
src/TimeSteps/Factory/CTimeStepFactory.Test.cpp
src/TestFixtures/CWorld_Fixture src/TestFixtures/CLayer_Fixture
src/Main
)

SET_TARGET_PROPERTIES(${TEST_NAME} PROPERTIES COMPILE_FLAGS "-DTEST -O0 -g3 -Wall -fmessage-length=0 -Wno-uninitialized"
)
TARGET_LINK_LIBRARIES(${TEST_NAME} ${LIBRARY_NAME} ${MAIN_LIBRARIES} ${TEST_LIBRARIES}
)

ADD_EXECUTABLE(${OPTI_NAME}
 src/BaseClasses/CBaseBuild
 src/BaseClasses/CBaseExecute
 src/BaseClasses/CBaseManager
 src/BaseClasses/CBaseObject
 src/BaseClasses/CBaseValidate
 src/BaseClasses/ParameterList/CParameterList
 src/Catchabilities/CCatchability
 src/Catchabilities/CCatchabilityManager
 src/Catchabilities/Factory/CCatchabilityFactory
 src/CConfiguration
 src/ConfigurationLoaders/CConfigurationLoader
 src/CRuntimeController
 src/Estimates/CEstimate
 src/Estimates/CEstimateManager
 src/Estimates/Factory/CEstimateFactory
 src/Helpers/CComparer
 src/Helpers/CConvertor
 src/Helpers/CError
 src/Helpers/CMath
 src/InitializationPhases/CInitializationPhase
 src/InitializationPhases/CInitializationPhaseManager
 src/InitializationPhases/Factory/CInitializationPhaseFactory
 src/Layers/CLayer
 src/Layers/CLayerManager
 src/Layers/Factory/CLayerFactory
 src/Layers/MetaLayer/CMetaLayer
 src/Layers/Numeric/Base/CNumericLayer
 src/Layers/Numeric/CAbundanceDensityLayer
 src/Layers/Numeric/CAbundanceLayer
 src/Layers/Numeric/CBiomassDensityLayer
 src/Layers/Numeric/CBiomassLayer
 src/Layers/Numeric/CDistanceLayer
 src/Layers/Numeric/CDoubleLayer
 src/Layers/String/CStringLayer
 src/MCMC/CMCMC
 src/Minimizers/CMinimizer
 src/Minimizers/CMinimizerManager
 src/Minimizers/DESolver/CDESolver
 src/Minimizers/DESolver/CDESolverCallback
 src/Minimizers/DESolver/Engine/DESolverEngine
 src/Minimizers/Factory/CMinimizerFactory
 src/Minimizers/GammaDiff/CGammaDiff
 src/Minimizers/GammaDiff/CGammaDiffCallback
 src/Minimizers/GammaDiff/Engine/FMM
 src/Minimizers/GammaDiff/Engine/GammaDiffEngine
 src/ObjectiveFunction/CObjectiveFunction
 src/Observations/Children/CAbundanceObservation
 src/Observations/Children/CProportionsAtAgeObservation
 src/Observations/Children/CProportionsByCategoryObservation
 src/Observations/CObservation
 src/Observations/CObservationManager
 src/Observations/Factory/CObservationFactory
 src/ParameterParser/CParamParser
 src/Penalties/CPenalty
 src/Penalties/CPenaltyManager
 src/Penalties/Factory/CPenaltyFactory
 src/PreferenceFunctions/Children/CConstantPreferenceFunction
 src/PreferenceFunctions/Children/CDoubleNormalPreferenceFunction
 src/PreferenceFunctions/Children/CExponentialPreferenceFunction
 src/PreferenceFunctions/Children/CInverseLogisticPreferenceFunction
 src/PreferenceFunctions/Children/CLogisticPreferenceFunction
 src/PreferenceFunctions/Children/CNormalPreferenceFunction
 src/PreferenceFunctions/Children/CThresholdBiomassPreferenceFunction
 src/PreferenceFunctions/Children/CThresholdPreferenceFunction
 src/PreferenceFunctions/CPreferenceFunction
 src/PreferenceFunctions/CPreferenceFunctionManager
 src/PreferenceFunctions/Factory/CPreferenceFunctionFactory
 src/Priors/Children/CBetaPrior
 src/Priors/Children/CLogNormalPrior
 src/Priors/Children/CNormalByStdevPrior
 src/Priors/Children/CNormalLogPrior
 src/Priors/Children/CNormalPrior
 src/Priors/Children/CUniformLogPrior
 src/Priors/Children/CUniformPrior
 src/Priors/CPrior
 src/Priors/CPriorManager
 src/Priors/Factory/CPriorFactory
 src/Processes/CProcess
 src/Processes/CProcessManager
 src/Processes/Factory/CProcessFactory
 src/Processes/Movement/Base/CMovementProcess
 src/Processes/Movement/CPreferenceMovementProcess
 src/Processes/Movement/CUniformMovementProcess
 src/Processes/Population/CAgeingProcess
 src/Processes/Population/CAnnualMortalityRateProcess
 src/Processes/Population/CBHRecruitmentProcess
 src/Processes/Population/CBiomassEventMortalityProcess
 src/Processes/Population/CCategoryTransitionProcess
 src/Processes/Population/CCategoryTransitionRateProcess
 src/Processes/Population/CConstantMortalityRateProcess
 src/Processes/Population/CConstantRecruitmentProcess
 src/Processes/Population/CEventMortalityProcess
 src/Processes/Population/CNaturalMortalityProcess
 src/Profiles/CProfile
 src/Profiles/CProfileManager
 src/Profiles/Factory/CProfileFactory
 src/Reporters/Children/Base/CFileReporter
 src/Reporters/Children/CEstimateSummaryReporter
 src/Reporters/Children/CObjectiveFunctionReporter
 src/Reporters/Children/CStandardHeaderReporter
 src/Reporters/Children/CWorldStateReporter
 src/Reporters/CReporter
 src/Reporters/CReporterManager
 src/Reporters/Factory/CReporterFactory
 src/RuntimeThread/CRuntimeThread
 src/Selectivities/Children/Base/CCachedSelectivity
 src/Selectivities/Children/CAllValuesBoundedSelectivity
 src/Selectivities/Children/CAllValuesSelectivity
 src/Selectivities/Children/CConstantSelectivity
 src/Selectivities/Children/CDoubleExponentialSelectivity
 src/Selectivities/Children/CDoubleNormalSelectivity
 src/Selectivities/Children/CIncreasingSelectivity
 src/Selectivities/Children/CKnifeEdgeSelectivity
 src/Selectivities/Children/CLogisticProducingSelectivity
 src/Selectivities/Children/CLogisticSelectivity
 src/Selectivities/CSelectivity
 src/Selectivities/CSelectivityManager
 src/Selectivities/Factory/CSelectivityFactory
 src/TimeSteps/CTimeStep
 src/TimeSteps/CTimeStepManager
 src/TimeSteps/Factory/CTimeStepFactory
 src/World/CWorld
 src/World/CWorldSquare
 src/World/WorldSquareCollection/CWorldSquareCollection
 src/Main)

SET_TARGET_PROPERTIES(${OPTI_NAME} PROPERTIES COMPILE_FLAGS "-DOPTIMISE -O3 -g0 -Wall -fmessage-length=0 -Wno-uninitialized")
TARGET_LINK_LIBRARIES(${OPTI_NAME} ${MAIN_LIBRARIES})