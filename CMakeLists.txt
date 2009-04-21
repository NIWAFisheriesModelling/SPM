cmake_minimum_required(VERSION 2.6)
project(SPM)

# To build the list below I used MSYS
# By executing the following command I could store the names of all
# .cpp files in a txt file. Then use a simple find/replace from .cpp to ""
# find src | grep ".cpp" | grep -v "svn" | grep -v ".Test." | grep -v "UnitTest" | grep -v "TestFixtures" > cpps.txt
# To get Unit Test only Files

SET(LIBRARY_NAME SimFish)
SET(MAIN_NAME spm_UnOptimised)
SET(TEST_NAME spm_UnitTests)
SET(OPTI_NAME spm)

# Added autogeneration of Version.h file in src directory
ADD_CUSTOM_TARGET(version ALL
  COMMAND svn_version --quiet --format c++ m--path ${PROJECT_SOURCE_DIR} --recursive --output ${PROJECT_SOURCE_DIR}/src/Version.h
)

IF (WIN32)
  SET(COMPILE_OPTIONS "-DOPTIMISE -O3 -g0 -Wall -fmessage-length=0 -Wno-uninitialized")
  SET(LINK_OPTIONS "-static icon.o")
  ADD_CUSTOM_TARGET(icon ALL
    COMMAND windres --output ${PROJECT_SOURCE_DIR}/icon.o --input ${PROJECT_SOURCE_DIR}/src/spm.rc
  )
  SET(MAIN_LIBRARIES
    libboost_system-mgw34-mt-1_38
    libboost_filesystem-mgw34-mt-1_38
    libboost_thread-mgw34-mt-1_38
    libboost_program_options-mgw34-mt-1_38
  )
  SET(TEST_LIBRARIES libboost_unit_test_framework-mgw34-mt-sd-1_38)
ELSE (WIN32)
  SET(COMPILE_OPTIONS "-DOPTIMISE -O3 -g0 -Wall -fmessage-length=0 -Wno-uninitialized -I /opt/boost138/usr/include")
  SET(LINK_OPTIONS "-L /opt/boost138/usr/lib -static")
  SET(MAIN_LIBRARIES
    libboost_system-gcc41-mt-1_38.so
    libboost_filesystem-gcc41-mt-1_38.so
    libboost_thread-gcc41-mt-1_38.so
    libboost_program_options-gcc41-mt-1_38.so
  )
  SET(TEST_LIBRARIES
    libboost_unit_test_framework-gcc41-mt-sd-1_38.so
  )
ENDIF (WIN32)

SET(SOURCE_FILES
src/BaseClasses/CBaseBuild.cpp
src/BaseClasses/CBaseExecute.cpp
src/BaseClasses/CBaseManager.cpp
src/BaseClasses/CBaseObject.cpp
src/BaseClasses/CBaseValidate.cpp
src/BaseClasses/ParameterList/CParameterList.cpp
src/Catchabilities/CCatchability.cpp
src/Catchabilities/CCatchabilityManager.cpp
src/Catchabilities/Factory/CCatchabilityFactory.cpp
src/CConfiguration.cpp
src/ConfigurationLoaders/CConfigurationLoader.cpp
src/CRuntimeController.cpp
src/DerivedQuantities/CDerivedQuantity.cpp
src/DerivedQuantities/CDerivedQuantityManager.cpp
src/Estimates/CEstimate.cpp
src/Estimates/CEstimateManager.cpp
src/Estimates/Factory/CEstimateFactory.cpp
src/Helpers/CComparer.cpp
src/Helpers/CConvertor.cpp
src/Helpers/CError.cpp
src/Helpers/CMath.cpp
src/InitializationPhases/CInitializationPhase.cpp
src/InitializationPhases/CInitializationPhaseManager.cpp
src/InitializationPhases/Factory/CInitializationPhaseFactory.cpp
src/Layers/CLayer.cpp
src/Layers/CLayerManager.cpp
src/Layers/Factory/CLayerFactory.cpp
src/Layers/MetaLayer/CMetaLayer.cpp
src/Layers/Numeric/Base/CNumericLayer.cpp
src/Layers/Numeric/CAbundanceDensityLayer.cpp
src/Layers/Numeric/CAbundanceLayer.cpp
src/Layers/Numeric/CBiomassDensityLayer.cpp
src/Layers/Numeric/CBiomassLayer.cpp
src/Layers/Numeric/CDistanceLayer.cpp
src/Layers/Numeric/CDoubleLayer.cpp
src/Layers/String/CStringLayer.cpp
src/Likelihoods/CLikelihood.cpp
src/Likelihoods/Factory/CLikelihoodFactory.cpp
src/Likelihoods/Children/CBinomialApproxLikelihood.cpp
src/Likelihoods/Children/CBinomialLikelihood.cpp
src/Likelihoods/Children/CLogNormalLikelihood.cpp
src/Likelihoods/Children/CLogNormalWithQLikelihood.cpp
src/Likelihoods/Children/CMultinomialLikelihood.cpp
src/Likelihoods/Children/CNormalLikelihood.cpp
src/Likelihoods/Children/CPseudoLikelihood.cpp
src/MCMC/CMCMC.cpp
src/Minimizers/CMinimizer.cpp
src/Minimizers/CMinimizerManager.cpp
src/Minimizers/DESolver/CDESolver.cpp
src/Minimizers/DESolver/CDESolverCallback.cpp
src/Minimizers/DESolver/Engine/DESolverEngine.cpp
src/Minimizers/Factory/CMinimizerFactory.cpp
src/Minimizers/GammaDiff/CGammaDiff.cpp
src/Minimizers/GammaDiff/CGammaDiffCallback.cpp
src/Minimizers/GammaDiff/Engine/FMM.cpp
src/Minimizers/GammaDiff/Engine/GammaDiffEngine.cpp
src/ObjectiveFunction/CObjectiveFunction.cpp
src/Observations/Children/CAbundanceObservation.cpp
src/Observations/Children/CProportionsAtAgeObservation.cpp
src/Observations/Children/CProportionsByCategoryObservation.cpp
src/Observations/CObservation.cpp
src/Observations/CObservationManager.cpp
src/Observations/Factory/CObservationFactory.cpp
src/ParameterParser/CParamParser.cpp
src/Penalties/CPenalty.cpp
src/Penalties/CPenaltyManager.cpp
src/Penalties/Factory/CPenaltyFactory.cpp
src/PreferenceFunctions/Children/CConstantPreferenceFunction.cpp
src/PreferenceFunctions/Children/CDoubleNormalPreferenceFunction.cpp
src/PreferenceFunctions/Children/CExponentialPreferenceFunction.cpp
src/PreferenceFunctions/Children/CInverseLogisticPreferenceFunction.cpp
src/PreferenceFunctions/Children/CLogisticPreferenceFunction.cpp
src/PreferenceFunctions/Children/CNormalPreferenceFunction.cpp
src/PreferenceFunctions/Children/CThresholdBiomassPreferenceFunction.cpp
src/PreferenceFunctions/Children/CThresholdPreferenceFunction.cpp
src/PreferenceFunctions/CPreferenceFunction.cpp
src/PreferenceFunctions/CPreferenceFunctionManager.cpp
src/PreferenceFunctions/Factory/CPreferenceFunctionFactory.cpp
src/Priors/Children/CBetaPrior.cpp
src/Priors/Children/CLogNormalPrior.cpp
src/Priors/Children/CNormalByStdevPrior.cpp
src/Priors/Children/CNormalLogPrior.cpp
src/Priors/Children/CNormalPrior.cpp
src/Priors/Children/CUniformLogPrior.cpp
src/Priors/Children/CUniformPrior.cpp
src/Priors/CPrior.cpp
src/Priors/CPriorManager.cpp
src/Priors/Factory/CPriorFactory.cpp
src/Processes/CProcess.cpp
src/Processes/CProcessManager.cpp
src/Processes/Factory/CProcessFactory.cpp
src/Processes/Movement/Base/CMovementProcess.cpp
src/Processes/Movement/CPreferenceMovementProcess.cpp
src/Processes/Movement/CUniformMovementProcess.cpp
src/Processes/Population/CAgeingProcess.cpp
src/Processes/Population/CAnnualMortalityRateProcess.cpp
src/Processes/Population/CBHRecruitmentProcess.cpp
src/Processes/Population/CBiomassEventMortalityProcess.cpp
src/Processes/Population/CCategoryTransitionProcess.cpp
src/Processes/Population/CCategoryTransitionRateProcess.cpp
src/Processes/Population/CConstantMortalityRateProcess.cpp
src/Processes/Population/CConstantRecruitmentProcess.cpp
src/Processes/Population/CEventMortalityProcess.cpp
src/Processes/Population/CNaturalMortalityProcess.cpp
src/Profiles/CProfile.cpp
src/Profiles/CProfileManager.cpp
src/Profiles/Factory/CProfileFactory.cpp
src/Reports/Children/Base/CFileReport.cpp
src/Reports/Children/CDerivedQuantityReport.cpp
src/Reports/Children/CEstimateSummaryReport.cpp
src/Reports/Children/CEstimateValueReport.cpp
src/Reports/Children/CInitializationReport.cpp
src/Reports/Children/CLayerDerivedWorldViewReport.cpp
src/Reports/Children/CObjectiveFunctionReport.cpp
src/Reports/Children/CObservationReport.cpp
src/Reports/Children/CPartitionReport.cpp
src/Reports/Children/CRandomNumberSeedReport.cpp
src/Reports/Children/CSelectivityReport.cpp
src/Reports/Children/CStandardHeaderReport.cpp
src/Reports/Children/CWorldStateReport.cpp
src/Reports/CReport.cpp
src/Reports/CReportManager.cpp
src/Reports/Factory/CReportFactory.cpp
src/RuntimeThread/CRuntimeThread.cpp
src/Selectivities/Children/Base/CCachedSelectivity.cpp
src/Selectivities/Children/CAllValuesBoundedSelectivity.cpp
src/Selectivities/Children/CAllValuesSelectivity.cpp
src/Selectivities/Children/CConstantSelectivity.cpp
src/Selectivities/Children/CDoubleExponentialSelectivity.cpp
src/Selectivities/Children/CDoubleNormalSelectivity.cpp
src/Selectivities/Children/CIncreasingSelectivity.cpp
src/Selectivities/Children/CKnifeEdgeSelectivity.cpp
src/Selectivities/Children/CLogisticProducingSelectivity.cpp
src/Selectivities/Children/CLogisticSelectivity.cpp
src/Selectivities/CSelectivity.cpp
src/Selectivities/CSelectivityManager.cpp
src/Selectivities/Factory/CSelectivityFactory.cpp
src/TimeSteps/CTimeStep.cpp
src/TimeSteps/CTimeStepManager.cpp
src/TimeSteps/Factory/CTimeStepFactory.cpp
src/World/CWorld.cpp
src/World/CWorldSquare.cpp
src/World/WorldSquareCollection/CWorldSquareCollection.cpp
src/World/WorldView/CCompleteWorldView.cpp
src/World/WorldView/CLayerDerivedWorldView.cpp
)

ADD_LIBRARY(${LIBRARY_NAME} ${SOURCE_FILES} )
SET_TARGET_PROPERTIES(${LIBRARY_NAME} PROPERTIES COMPILE_FLAGS ${COMPILE_OPTIONS} LINK_FLAGS ${LINK_OPTIONS})

ADD_EXECUTABLE(${MAIN_NAME}
 src/Main
)

SET_TARGET_PROPERTIES(${MAIN_NAME} PROPERTIES COMPILE_FLAGS ${COMPILE_OPTIONS} LINK_FLAGS ${LINK_OPTIONS})

TARGET_LINK_LIBRARIES(${MAIN_NAME} ${LIBRARY_NAME} ${MAIN_LIBRARIES})

ADD_EXECUTABLE(${TEST_NAME}
src/Layers/Factory/CLayerFactory.Test.cpp
src/Priors/Factory/CPriorFactory.Test.cpp
src/Penalties/Factory/CPenaltyFactory.Test.cpp
src/Processes/Population/CCategoryTransitionRateProcess.Test.cpp
src/Processes/Population/CAgeingProcess.Test.cpp
src/Processes/Population/CConstantRecruitmentProcess.Test.cpp
src/Estimates/Factory/CEstimateFactory.Test.cpp
src/TestFixtures/CLayer_Fixture.cpp
src/TestFixtures/C1x1_Fixture.cpp
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

SET_TARGET_PROPERTIES(${TEST_NAME} PROPERTIES COMPILE_FLAGS ${COMPILE_OPTIONS} LINK_FLAGS ${LINK_OPTIONS})

TARGET_LINK_LIBRARIES(${TEST_NAME} ${LIBRARY_NAME} ${MAIN_LIBRARIES} ${TEST_LIBRARIES})

ADD_EXECUTABLE(${OPTI_NAME}
 ${SOURCE_FILES}
 src/Main
 )

SET_TARGET_PROPERTIES(${OPTI_NAME} PROPERTIES COMPILE_FLAGS ${COMPILE_OPTIONS} LINK_FLAGS ${LINK_OPTIONS})

TARGET_LINK_LIBRARIES(${OPTI_NAME} ${MAIN_LIBRARIES})

ADD_DEPENDENCIES(${MAIN_NAME} version icon)
ADD_DEPENDENCIES(${TEST_NAME} version icon)
ADD_DEPENDENCIES(${LIBRARY_NAME} version)
ADD_DEPENDENCIES(${OPTI_NAME} version icon)

