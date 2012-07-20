cmake_minimum_required(VERSION 2.6)
project(SPM)

# to run (Windows, Mingw32-gcc)
#   cmake -G "MinGW Makefiles"
#   mingw32-make all
# or Linux
#   cmake -G "Unix Makefiles"
#   make all

SET(LIBRARY_NAME _spm)
SET(MAIN_NAME spm_unoptimised)
SET(TEST_NAME spm_unittests)
SET(OPTI_NAME spm)

# Assumptions
# Compiled with MinGW under Windows, where,
#   MinGW is in c:\Program Files
#   Boost libraries are located in C:/Progra~2/MingW/boost_libs
#   Boost header files are located in C:/Progra~2/MinGW/include/boost/

IF (WIN32)
  SET(BOOST_LIBS "-L C:/Progra~1/boost/boost_1_48_0/stage/lib -L D:/Programming/boost/boost_1_48_0/boost_1_48_0/stage/lib")
  SET(LINK_OPTIONS "${BOOST_LIBS} -static icon.o")
  SET(COMPILE_OPTIONS_LIBR "-DBOOST_THREAD_USE_LIB=1 -O0 -g3 -ggdb -Wall -fmessage-length=0")
  SET(COMPILE_OPTIONS_MAIN "-DBOOST_THREAD_USE_LIB=1 -O0 -g3 -Wall -fmessage-length=0")
  SET(COMPILE_OPTIONS_OPTI "-DBOOST_THREAD_USE_LIB=1 -DOPTIMIZE -O3 -g0 -Wall -fmessage-length=0")
  SET(COMPILE_OPTIONS_TEST "-DBOOST_THREAD_USE_LIB=1 -DTEST -O0 -g3 -Wall -fmessage-length=0")
  ADD_CUSTOM_TARGET(icon ALL
    COMMAND windres --output ${PROJECT_SOURCE_DIR}/icon.o --input ${PROJECT_SOURCE_DIR}/src/spm.rc
  )
  SET(MAIN_LIBRARIES
    boost_system-mgw46-mt-s-1_48
    boost_filesystem-mgw46-mt-s-1_48
    boost_thread-mgw46-mt-s-1_48
    boost_program_options-mgw46-mt-s-1_48
  )
  SET(TEST_LIBRARIES boost_unit_test_framework-mgw46-mt-sd-1_48)
ELSE (WIN32)
  SET(BOOST_LIBS "/opt/boost138/usr/lib64/")
  SET(BOOST_HEADERS "/opt/boost138/usr/include/")
  SET(LINK_OPTIONS "-static -L ${BOOST_LIBS}")
  SET(COMPILE_OPTIONS_LIBR "-DBOOST_THREAD_USE_LIB=1 -O0 -g3 -ggdb -Wall -fmessage-length=0 -I ${BOOST_HEADERS}")
  SET(COMPILE_OPTIONS_MAIN "-DBOOST_THREAD_USE_LIB=1 -O0 -g3 -Wall -fmessage-length=0 -I ${BOOST_HEADERS}")
  SET(COMPILE_OPTIONS_OPTI "-DBOOST_THREAD_USE_LIB=1 -DOPTIMIZE -O3 -g0 -Wall -fmessage-length=0 -I ${BOOST_HEADERS}")
  SET(COMPILE_OPTIONS_TEST "-DBOOST_THREAD_USE_LIB=1 -DTEST -O0 -g3 -Wall -fmessage-length=0 -I ${BOOST_HEADERS}")
  SET(MAIN_LIBRARIES
    boost_system-gcc41-mt-1_38
    boost_filesystem-gcc41-mt-1_38
    boost_thread-gcc41-mt-1_38
    boost_program_options-gcc41-mt-1_38
    pthread
    )
  SET(TEST_LIBRARIES
    boost_unit_test_framework-gcc41-mt-1_38
  )
ENDIF (WIN32)


# Autogeneration of Version.h file in src directory (backing up current ('NULL') version
ADD_CUSTOM_TARGET(version ALL
  COMMAND cp ${PROJECT_SOURCE_DIR}/src/Version.h ${PROJECT_SOURCE_DIR}/src/Version.h.old
  COMMAND svn_version --quiet --format c++ m--path ${PROJECT_SOURCE_DIR} --recursive --output ${PROJECT_SOURCE_DIR}/src/Version.h
)

# To build the list below I used MSYS
# By executing the following command I could store the names of all
# .cpp files in a txt file. Then use a simple find/replace from .cpp to ""
# find src | grep ".cpp" | grep -v "svn" | grep -v ".Test." | grep -v "UnitTest" | grep -v "TestFixtures" > cpps.txt
# To get Unit Test only Files

SET(SOURCE_FILES
src/AgeingError/CAgeingError.cpp
src/AgeingError/CAgeingErrorManager.cpp
src/AgeingError/Children/CNormalAgeingError.cpp
src/AgeingError/Children/COffByOneAgeingError.cpp
src/AgeingError/Factory/CAgeingErrorFactory.cpp
src/AgeSize/CAgeSize.cpp
src/AgeSize/CAgeSizeManager.cpp
src/AgeSize/Children/CNoneAgeSize.cpp
src/AgeSize/Children/CSchnuteAgeSize.cpp
src/AgeSize/Children/CVonBertalanffyAgeSize.cpp
src/AgeSize/Factory/CAgeSizeFactory.cpp
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
src/DerivedQuantities/Children/CAbundanceDerivedQuantity.cpp
src/DerivedQuantities/Children/CBiomassDerivedQuantity.cpp
src/DerivedQuantities/Children/CTestDerivedQuantity.cpp
src/DerivedQuantities/Factory/CDerivedQuantityFactory.cpp
src/Distributions/CNormalDistribution.cpp
src/Estimates/CEstimate.cpp
src/Estimates/CEstimateInfo.cpp
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
src/Likelihoods/Children/CBinomialApproxLikelihood.cpp
src/Likelihoods/Children/CBinomialLikelihood.cpp
src/Likelihoods/Children/CLogNormalLikelihood.cpp
src/Likelihoods/Children/CLogNormalWithQLikelihood.cpp
src/Likelihoods/Children/CMultinomialLikelihood.cpp
src/Likelihoods/Children/CNormalLikelihood.cpp
src/Likelihoods/Children/CPseudoLikelihood.cpp
src/Likelihoods/CLikelihood.cpp
src/Likelihoods/Factory/CLikelihoodFactory.cpp
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
src/ObjectFinder/CObjectFinder.cpp
src/ObjectiveFunction/CObjectiveFunction.cpp
src/Observations/Children/CAbundanceObservation.cpp
src/Observations/Children/CBiomassObservation.cpp
src/Observations/Children/CProportionsAtAgeObservation.cpp
src/Observations/Children/CProportionsByCategoryObservation.cpp
src/Observations/CObservation.cpp
src/Observations/CObservationManager.cpp
src/Observations/Factory/CObservationFactory.cpp
src/Penalties/CPenalty.cpp
src/Penalties/CPenaltyManager.cpp
src/Penalties/Factory/CPenaltyFactory.cpp
src/PreferenceFunctions/Children/CConstantPreferenceFunction.cpp
src/PreferenceFunctions/Children/CCategoricalMonotonicPreferenceFunction.cpp
src/PreferenceFunctions/Children/CCategoricalPreferenceFunction.cpp
src/PreferenceFunctions/Children/CDoubleNormalPreferenceFunction.cpp
src/PreferenceFunctions/Children/CExponentialPreferenceFunction.cpp
src/PreferenceFunctions/Children/CInverseLogisticPreferenceFunction.cpp
src/PreferenceFunctions/Children/CLogisticPreferenceFunction.cpp
src/PreferenceFunctions/Children/CNormalPreferenceFunction.cpp
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
src/Processes/Movement/CAdjacentCellMovementProcess.cpp
src/Processes/Movement/CMigrationMovementProcess.cpp
src/Processes/Population/CAgeingProcess.cpp
src/Processes/Population/CAnnualMortalityRateProcess.cpp
src/Processes/Population/CBHRecruitmentProcess.cpp
src/Processes/Population/CBiomassEventMortalityProcess.cpp
src/Processes/Population/CCategoryTransitionProcess.cpp
src/Processes/Population/CCategoryTransitionRateProcess.cpp
src/Processes/Population/CConstantMortalityRateProcess.cpp
src/Processes/Population/CConstantRecruitmentProcess.cpp
src/Processes/Population/CEventMortalityProcess.cpp
src/Processes/Population/CHollingMortalityRateProcess.cpp
src/Processes/Population/CLocalBHRecruitmentProcess.cpp
src/Profiles/CProfile.cpp
src/Profiles/CProfileManager.cpp
src/Profiles/Factory/CProfileFactory.cpp
src/RandomNumberGenerator/CRandomNumberGenerator.cpp
src/Reports/Children/Base/CFileReport.cpp
src/Reports/Children/CAgeingErrorReport.cpp
src/Reports/Children/CAgeSizeReport.cpp
src/Reports/Children/CAgeWeightReport.cpp
src/Reports/Children/CCovarianceReport.cpp
src/Reports/Children/CDerivedQuantityReport.cpp
src/Reports/Children/CEstimateSummaryReport.cpp
src/Reports/Children/CEstimateValueReport.cpp
src/Reports/Children/CInitializationReport.cpp
src/Reports/Children/CLayerDerivedWorldViewReport.cpp
src/Reports/Children/CLayerReport.cpp
src/Reports/Children/CMCMCReport.cpp
src/Reports/Children/CObjectiveFunctionReport.cpp
src/Reports/Children/CObservationReport.cpp
src/Reports/Children/CProcessReport.cpp
src/Reports/Children/CPartitionReport.cpp
src/Reports/Children/CRandomNumberSeedReport.cpp
src/Reports/Children/CSelectivityReport.cpp
src/Reports/Children/CSimulatedObservationReport.cpp
src/Reports/Children/CSizeWeightReport.cpp
src/Reports/Children/CSpatialMapReport.cpp
src/Reports/Children/CStandardHeaderReport.cpp
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
src/Selectivities/Children/CInverseLogisticSelectivity.cpp
src/Selectivities/CSelectivity.cpp
src/Selectivities/CSelectivityManager.cpp
src/Selectivities/Factory/CSelectivityFactory.cpp
src/SizeWeight/CSizeWeight.cpp
src/SizeWeight/CSizeWeightManager.cpp
src/SizeWeight/Children/CBasicSizeWeight.cpp
src/SizeWeight/Children/CNoneSizeWeight.cpp
src/SizeWeight/Factory/CSizeWeightFactory.cpp
src/TimeSteps/CTimeStep.cpp
src/TimeSteps/CTimeStepManager.cpp
src/TimeSteps/Factory/CTimeStepFactory.cpp
src/World/CWorld.cpp
src/World/CWorldSquare.cpp
src/World/WorldView/CCompleteWorldView.cpp
src/World/WorldView/CLayerDerivedWorldView.cpp
)

ADD_EXECUTABLE(${TEST_NAME}
src/Catchabilities/CCatchability.Test.cpp
src/Catchabilities/Factory/CCatchabilityFactory.Test.cpp
src/ConfigurationLoaders/CConfigurationLoader.Test.cpp
src/DerivedQuantities/Children/CAbundanceDerivedQuantity.Test.cpp
src/DerivedQuantities/Children/CTestDerivedQuantity.Test.cpp
src/DerivedQuantities/Factory/CDerivedQuantityFactory.Test.cpp
src/Estimates/Factory/CEstimateFactory.Test.cpp
src/InitializationPhases/Factory/CInitializationPhaseFactory.Test.cpp
src/Layers/Factory/CLayerFactory.Test.cpp
src/Likelihoods/Children/CBinomialApproxLikelihood.Test.cpp
src/Likelihoods/Children/CBinomialLikelihood.Test.cpp
src/Likelihoods/Children/CLogNormalLikelihood.Test.cpp
src/Main
src/Minimizers/Factory/CMinimizerFactory.Test.cpp
src/Observations/Children/CAbundanceObservation.Test.cpp
src/Observations/Children/CProportionsAtAgeObservation.Test.cpp
src/Observations/Children/CProportionsByCategoryObservation.Test.cpp
src/Observations/Factory/CObservationFactory.Test.cpp
src/Penalties/Factory/CPenaltyFactory.Test.cpp
src/PreferenceFunctions/Children/CConstantPreferenceFunction.Test.cpp
src/PreferenceFunctions/Children/CDoubleNormalPreferenceFunction.Test.cpp
src/PreferenceFunctions/Children/CExponentialPreferenceFunction.Test.cpp
src/PreferenceFunctions/Children/CInverseLogisticPreferenceFunction.Test.cpp
src/PreferenceFunctions/Children/CLogisticPreferenceFunction.Test.cpp
src/PreferenceFunctions/Children/CNormalPreferenceFunction.Test.cpp
src/PreferenceFunctions/Factory/CPreferenceFunctionFactory.Test.cpp
src/Priors/Children/CBetaPrior.Test.cpp
src/Priors/Children/CLogNormalPrior.Test.cpp
src/Priors/Children/CNormalByStdevPrior.Test.cpp
src/Priors/Children/CNormalLogPrior.Test.cpp
src/Priors/Children/CNormalPrior.Test.cpp
src/Priors/Children/CUniformLogPrior.Test.cpp
src/Priors/Children/CUniformPrior.Test.cpp
src/Priors/Factory/CPriorFactory.Test.cpp
src/Processes/Movement/CAdjacentCellMovementProcess.Test.cpp
src/Processes/Population/CAgeingProcess.Test.cpp
src/Processes/Population/CAnnualMortalityRateProcess.Test.cpp
src/Processes/Population/CCategoryTransitionRateProcess.Test.cpp
src/Processes/Population/CConstantRecruitmentProcess.Test.cpp
src/Profiles/Factory/CProfileFactory.Test.cpp
src/RandomNumberGenerator/CRandomNumberGenerator.Test.cpp
src/Selectivities/Children/CAllValuesBoundedSelectivity.Test.cpp
src/Selectivities/Children/CAllValuesSelectivity.Test.cpp
src/Selectivities/Children/CConstantSelectivity.Test.cpp
src/Selectivities/Children/CDoubleNormalSelectivity.Test.cpp
src/Selectivities/Children/CKnifeEdgeSelectivity.Test.cpp
src/Selectivities/Children/CLogisticProducingSelectivity.Test.cpp
src/Selectivities/Children/CLogisticSelectivity.Test.cpp
src/Selectivities/Children/CInverseLogisticSelectivity.Test.cpp
src/Selectivities/Factory/CSelectivityFactory.Test.cpp
src/TestFixtures/C1x1_Fixture.cpp
src/TestFixtures/C3x3_Fixture.cpp
src/TestFixtures/CLayer_Fixture.cpp
src/TestFixtures/CWorld_Fixture.cpp
src/TimeSteps/Factory/CTimeStepFactory.Test.cpp
)

ADD_EXECUTABLE(${MAIN_NAME}
 src/Main
)

ADD_EXECUTABLE(${OPTI_NAME}
 ${SOURCE_FILES}
 src/Main
 )

# Build lspm library
ADD_LIBRARY(${LIBRARY_NAME} ${SOURCE_FILES} )
SET_TARGET_PROPERTIES(${LIBRARY_NAME} PROPERTIES COMPILE_FLAGS ${COMPILE_OPTIONS_LIBR} LINK_FLAGS ${LINK_OPTIONS})

# Build SPM unoptimised
SET_TARGET_PROPERTIES(${MAIN_NAME} PROPERTIES COMPILE_FLAGS ${COMPILE_OPTIONS_MAIN} LINK_FLAGS ${LINK_OPTIONS})
TARGET_LINK_LIBRARIES(${MAIN_NAME} ${LIBRARY_NAME} ${MAIN_LIBRARIES})

# Build SPM unit tests
SET_TARGET_PROPERTIES(${TEST_NAME} PROPERTIES COMPILE_FLAGS ${COMPILE_OPTIONS_TEST} LINK_FLAGS ${LINK_OPTIONS})
TARGET_LINK_LIBRARIES(${TEST_NAME} ${LIBRARY_NAME} ${MAIN_LIBRARIES} ${TEST_LIBRARIES})

# Build SPM optimised
SET_TARGET_PROPERTIES(${OPTI_NAME} PROPERTIES COMPILE_FLAGS ${COMPILE_OPTIONS_OPTI} LINK_FLAGS ${LINK_OPTIONS})
TARGET_LINK_LIBRARIES(${OPTI_NAME} ${MAIN_LIBRARIES})

ADD_DEPENDENCIES(${MAIN_NAME} version icon)
ADD_DEPENDENCIES(${TEST_NAME} version icon)
ADD_DEPENDENCIES(${LIBRARY_NAME} version)
ADD_DEPENDENCIES(${OPTI_NAME} version icon)
