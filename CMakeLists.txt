cmake_minimum_required(VERSION 2.6)
project(SPM)

# To build the list below I used MSYS
# By executing the following command I could store the names of all
# .cpp files in a txt file. Then use a simple find/replace from .cpp to ""
# find | grep ".cpp" | grep -v "svn" | grep -v ".Test." | grep -v "UnitTest"

SET(LIBRARY_NAME SimFish)
SET(MAIN_NAME spm_UnOptimised)
SET(TEST_NAME spm_UnitTests)
SET(OPTI_NAME spm)

# Added autogeneration of Version.h file in src directory
ADD_CUSTOM_TARGET(version ALL
  COMMAND svn_version --quiet --format c++ m--path ${PROJECT_SOURCE_DIR} --recursive --output ${PROJECT_SOURCE_DIR}/src/Version.h
)

IF (WIN32)
  SET(LINK_ICON "-static icon.o")
  ADD_CUSTOM_TARGET(icon ALL
    COMMAND windres --output ${PROJECT_SOURCE_DIR}/icon.o --input ${PROJECT_SOURCE_DIR}/src/spm.rc
  )
ENDIF (WIN32)

SET(SOURCE_FILES
src/MCMC/CMCMC.cpp
src/ParameterParser/CParamParser.cpp
src/CConfiguration.cpp
src/World/WorldSquareCollection/CWorldSquareCollection.cpp
src/World/CWorldSquare.cpp
src/World/CWorld.cpp
src/DerivedQuantities/CDerivedQuantity.cpp
src/DerivedQuantities/CDerivedQuantityManager.cpp
src/Layers/Numeric/Base/CNumericLayer.cpp
src/Layers/Numeric/CAbundanceDensityLayer.cpp
src/Layers/Numeric/CBiomassDensityLayer.cpp
src/Layers/Numeric/CAbundanceLayer.cpp
src/Layers/Numeric/CDistanceLayer.cpp
src/Layers/Numeric/CBiomassLayer.cpp
src/Layers/Numeric/CDoubleLayer.cpp
src/Layers/CLayer.cpp
src/Layers/String/CStringLayer.cpp
src/Layers/CLayerManager.cpp
src/Layers/MetaLayer/CMetaLayer.cpp
src/Layers/Factory/CLayerFactory.cpp
src/Priors/Children/CNormalPrior.cpp
src/Priors/Children/CNormalLogPrior.cpp
src/Priors/Children/CNormalByStdevPrior.cpp
src/Priors/Children/CUniformLogPrior.cpp
src/Priors/Children/CLogNormalPrior.cpp
src/Priors/Children/CUniformPrior.cpp
src/Priors/Children/CBetaPrior.cpp
src/Priors/CPrior.cpp
src/Priors/Factory/CPriorFactory.cpp
src/Priors/CPriorManager.cpp
src/CRuntimeController.cpp
src/ObjectiveFunction/CObjectiveFunction.cpp
src/Penalties/CPenalty.cpp
src/Penalties/Factory/CPenaltyFactory.cpp
src/Penalties/CPenaltyManager.cpp
src/Processes/Population/CEventMortalityProcess.cpp
src/Processes/Population/CAnnualMortalityRateProcess.cpp
src/Processes/Population/CBiomassEventMortalityProcess.cpp
src/Processes/Population/CConstantMortalityRateProcess.cpp
src/Processes/Population/CCategoryTransitionProcess.cpp
src/Processes/Population/CAgeingProcess.cpp
src/Processes/Population/CBHRecruitmentProcess.cpp
src/Processes/Population/CCategoryTransitionRateProcess.cpp
src/Processes/Population/CNaturalMortalityProcess.cpp
src/Processes/Population/CConstantRecruitmentProcess.cpp
src/Processes/Movement/Base/CMovementProcess.cpp
src/Processes/Movement/CPreferenceMovementProcess.cpp
src/Processes/Movement/CUniformMovementProcess.cpp
src/Processes/CProcess.cpp
src/Processes/CProcessManager.cpp
src/Processes/Factory/CProcessFactory.cpp
src/Estimates/CEstimateManager.cpp
src/Estimates/Factory/CEstimateFactory.cpp
src/Estimates/CEstimate.cpp
src/Reports/CReport.cpp
src/Reports/Children/Base/CFileReport.cpp
src/Reports/Children/CStandardHeaderReport.cpp
src/Reports/Children/CWorldStateReport.cpp
src/Reports/Children/CEstimateValueReport.cpp
src/Reports/Children/CInitializationReport.cpp
src/Reports/Children/CObjectiveFunctionReport.cpp
src/Reports/Children/CPartitionReport.cpp
src/Reports/Children/CObservationReport.cpp
src/Reports/Children/CEstimateSummaryReport.cpp
src/Reports/Children/CSelectivityReport.cpp
src/Reports/Children/CDerivedQuantityReport.cpp
src/Reports/Children/CRandomNumberSeedReport.cpp
src/Reports/CReportManager.cpp
src/Reports/Factory/CReportFactory.cpp
src/Profiles/CProfileManager.cpp
src/Profiles/CProfile.cpp
src/Profiles/Factory/CProfileFactory.cpp
src/Selectivities/Children/Base/CCachedSelectivity.cpp
src/Selectivities/Children/CDoubleNormalSelectivity.cpp
src/Selectivities/Children/CIncreasingSelectivity.cpp
src/Selectivities/Children/CConstantSelectivity.cpp
src/Selectivities/Children/CAllValuesSelectivity.cpp
src/Selectivities/Children/CAllValuesBoundedSelectivity.cpp
src/Selectivities/Children/CDoubleExponentialSelectivity.cpp
src/Selectivities/Children/CLogisticProducingSelectivity.cpp
src/Selectivities/Children/CKnifeEdgeSelectivity.cpp
src/Selectivities/Children/CLogisticSelectivity.cpp
src/Selectivities/CSelectivity.cpp
src/Selectivities/Factory/CSelectivityFactory.cpp
src/Selectivities/CSelectivityManager.cpp
src/Observations/Children/CAbundanceObservation.cpp
src/Observations/Children/CProportionsByCategoryObservation.cpp
src/Observations/Children/CProportionsAtAgeObservation.cpp
src/Observations/CObservationManager.cpp
src/Observations/Factory/CObservationFactory.cpp
src/Observations/CObservation.cpp
src/TimeSteps/CTimeStepManager.cpp
src/TimeSteps/Factory/CTimeStepFactory.cpp
src/TimeSteps/CTimeStep.cpp
src/Minimizers/CMinimizer.cpp
src/Minimizers/DESolver/Engine/DESolverEngine.cpp
src/Minimizers/DESolver/CDESolverCallback.cpp
src/Minimizers/DESolver/CDESolver.cpp
src/Minimizers/Factory/CMinimizerFactory.cpp
src/Minimizers/GammaDiff/Engine/GammaDiffEngine.cpp
src/Minimizers/GammaDiff/Engine/FMM.cpp
src/Minimizers/GammaDiff/CGammaDiff.cpp
src/Minimizers/GammaDiff/CGammaDiffCallback.cpp
src/Minimizers/CMinimizerManager.cpp
src/RuntimeThread/CRuntimeThread.cpp
src/Catchabilities/CCatchabilityManager.cpp
src/Catchabilities/Factory/CCatchabilityFactory.cpp
src/Catchabilities/CCatchability.cpp
src/PreferenceFunctions/CPreferenceFunctionManager.cpp
src/PreferenceFunctions/Children/CThresholdBiomassPreferenceFunction.cpp
src/PreferenceFunctions/Children/CDoubleNormalPreferenceFunction.cpp
src/PreferenceFunctions/Children/CThresholdPreferenceFunction.cpp
src/PreferenceFunctions/Children/CInverseLogisticPreferenceFunction.cpp
src/PreferenceFunctions/Children/CLogisticPreferenceFunction.cpp
src/PreferenceFunctions/Children/CExponentialPreferenceFunction.cpp
src/PreferenceFunctions/Children/CConstantPreferenceFunction.cpp
src/PreferenceFunctions/Children/CNormalPreferenceFunction.cpp
src/PreferenceFunctions/CPreferenceFunction.cpp
src/PreferenceFunctions/Factory/CPreferenceFunctionFactory.cpp
src/ConfigurationLoaders/CConfigurationLoader.cpp
src/InitializationPhases/CInitializationPhase.cpp
src/InitializationPhases/Factory/CInitializationPhaseFactory.cpp
src/InitializationPhases/CInitializationPhaseManager.cpp
src/BaseClasses/CBaseManager.cpp
src/BaseClasses/CBaseBuild.cpp
src/BaseClasses/CBaseObject.cpp
src/BaseClasses/CBaseExecute.cpp
src/BaseClasses/ParameterList/CParameterList.cpp
src/BaseClasses/CBaseValidate.cpp
src/Helpers/CComparer.cpp
src/Helpers/CError.cpp
src/Helpers/CMath.cpp
src/Helpers/CConvertor.cpp
src/World/WorldView/CLayerDerivedWorldView.cpp
)

ADD_LIBRARY(${LIBRARY_NAME} ${SOURCE_FILES} )
SET_TARGET_PROPERTIES(${LIBRARY_NAME} PROPERTIES COMPILE_FLAGS "-O0 -g3 -ggdb -Wall -fmessage-length=0" )

SET(MAIN_LIBRARIES
 libboost_system-mgw34-mt-1_38
 libboost_filesystem-mgw34-mt-1_38
 libboost_thread-mgw34-mt-1_38
 libboost_program_options-mgw34-mt-1_38
)

SET(TEST_LIBRARIES libboost_unit_test_framework-mgw34-mt-sd-1_38)
ADD_EXECUTABLE(${MAIN_NAME}
 src/Main
)

IF (WIN32)
  SET_TARGET_PROPERTIES(${MAIN_NAME} PROPERTIES COMPILE_FLAGS "-O0 -g3 -Wall -fmessage-length=0" LINK_FLAGS ${LINK_ICON})
ELSE (WIN32)
  SET_TARGET_PROPERTIES(${MAIN_NAME} PROPERTIES COMPILE_FLAGS "-O0 -g3 -Wall -fmessage-length=0")
ENDIF (WIN32)

TARGET_LINK_LIBRARIES(${MAIN_NAME} ${LIBRARY_NAME} ${MAIN_LIBRARIES})

ADD_EXECUTABLE(${TEST_NAME}
src/Layers/Factory/CLayerFactory.Test.cpp
src/Priors/Factory/CPriorFactory.Test.cpp
src/Penalties/Factory/CPenaltyFactory.Test.cpp
src/Estimates/Factory/CEstimateFactory.Test.cpp
src/TestFixtures/CLayer_Fixture.cpp
src/TestFixtures/CWorld_Fixture.cpp
src/Profiles/Factory/CProfileFactory.Test.cpp
src/Selectivities/Children/CConstantSelectivity.Test.cpp
src/Selectivities/Children/CLogisticProducingSelectivity.Test.cpp
src/Selectivities/Children/CLogisticSelectivity.Test.cpp
src/Selectivities/Children/CDoubleNormalSelectivity.Test.cpp
src/Selectivities/Children/CKnifeEdgeSelectivity.Test.cpp
src/Selectivities/Factory/CSelectivityFactory.Test.cpp
src/Observations/Factory/CObservationFactory.Test.cpp
src/TimeSteps/Factory/CTimeStepFactory.Test.cpp
src/Minimizers/Factory/CMinimizerFactory.Test.cpp
src/Catchabilities/Factory/CCatchabilityFactory.Test.cpp
src/PreferenceFunctions/Children/CInverseLogisticPreferenceFunction.Test.cpp
src/PreferenceFunctions/Children/CDoubleNormalPreferenceFunction.Test.cpp
src/PreferenceFunctions/Children/CLogisticPreferenceFunction.Test.cpp
src/PreferenceFunctions/Children/CNormalPreferenceFunction.Test.cpp
src/PreferenceFunctions/Children/CExponentialPreferenceFunction.Test.cpp
src/PreferenceFunctions/Children/CConstantPreferenceFunction.Test.cpp
src/PreferenceFunctions/Factory/CPreferenceFunctionFactory.Test.cpp
src/InitializationPhases/Factory/CInitializationPhaseFactory.Test.cpp
src/Main
)

IF (WIN32)
  SET_TARGET_PROPERTIES(${TEST_NAME} PROPERTIES COMPILE_FLAGS "-DTEST -O0 -g3 -Wall -fmessage-length=0 -Wno-uninitialized" LINK_FLAGS ${LINK_ICON})
ELSE (WIN32)
  SET_TARGET_PROPERTIES(${TEST_NAME} PROPERTIES COMPILE_FLAGS "-DTEST -O0 -g3 -Wall -fmessage-length=0 -Wno-uninitialized" )
ENDIF (WIN32)

TARGET_LINK_LIBRARIES(${TEST_NAME} ${LIBRARY_NAME} ${MAIN_LIBRARIES} ${TEST_LIBRARIES})

ADD_EXECUTABLE(${OPTI_NAME}
 ${SOURCE_FILES}
 src/Main
 )

IF (WIN32)
  SET_TARGET_PROPERTIES(${OPTI_NAME} PROPERTIES COMPILE_FLAGS "-DOPTIMISE -O3 -g0 -Wall -fmessage-length=0 -Wno-uninitialized" LINK_FLAGS ${LINK_ICON})
ELSE (WIN32)
  SET_TARGET_PROPERTIES(${OPTI_NAME} PROPERTIES COMPILE_FLAGS "-DOPTIMISE -O3 -g0 -Wall -fmessage-length=0 -Wno-uninitialized")
ENDIF (WIN32)

TARGET_LINK_LIBRARIES(${OPTI_NAME} ${MAIN_LIBRARIES})

ADD_DEPENDENCIES(${MAIN_NAME} version icon)
ADD_DEPENDENCIES(${TEST_NAME} version icon)
ADD_DEPENDENCIES(${LIBRARY_NAME} version)
ADD_DEPENDENCIES(${OPTI_NAME} version icon)

