//============================================================================
// Name        : CBaseTestFixture.cpp
// Author      : S.Rasmussen
// Date        : 30/05/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef UNITTEST

// Local Headers
#include "CBaseTestFixture.h"
#include "../../Layers/NumericLayers/CDoubleLayer.h"
#include "../../Layers/NumericLayers/CAbundanceLayer.h"
#include "../../Layers/NumericLayers/CDistanceLayer.h"
#include "../../Layers/CStringLayer.h"
#include "../../Selectivities/CConstantSelectivity.h"
#include "../../Selectivities/CDoubleNormalSelectivity.h"
#include "../../Selectivities/CKnifeEdgeSelectivity.h"
#include "../../Selectivities/CLogisticProducingSelectivity.h"
#include "../../Selectivities/CLogisticSelectivity.h"
#include "../../Penalties/CPenalty.h"
#include "../../DirectedProcesses/CConstantDirectedProcess.h"
#include "../../DirectedProcesses/CDoubleNormalDirectedProcess.h"
#include "../../DirectedProcesses/CExponentialDirectedProcess.h"
#include "../../DirectedProcesses/CInverseLogisticDirectedProcess.h"
#include "../../DirectedProcesses/CLogisticDirectedProcess.h"
#include "../../DirectedProcesses/CNormalDirectedProcess.h"
#include "../../DirectedProcesses/CThresholdDirectedProcess.h"

//**********************************************************************
// CBaseTestFixture::CBaseTestFixture()
// Default Constructor
//**********************************************************************
CBaseTestFixture::CBaseTestFixture() {
  // Cleanup, Incase This wasn't Done
  CRuntimeController::Destroy();

  // Default Our Variables
  BOOST_REQUIRE_NO_THROW(pConfig = CConfiguration::Instance());
  BOOST_REQUIRE_NO_THROW(pRuntime = CRuntimeController::Instance());
  BOOST_REQUIRE_NO_THROW(pWorld = CWorld::Instance());
  BOOST_REQUIRE_NO_THROW(pLayerManager = CLayerManager::Instance());
  BOOST_REQUIRE_NO_THROW(pSelectivityManager = CSelectivityManager::Instance());
  BOOST_REQUIRE_NO_THROW(pPenaltyManager = CPenaltyManager::Instance());
  BOOST_REQUIRE_NO_THROW(pDirectedProcessManager = CPreferenceFunctionManager::Instance());

  // Default Some Variables
  immatureIndex       = -1;
  matureIndex         = -1;
  spawningIndex       = -1;

  // Cal Some Functions
  setupConfiguration();
  setupWorld();
  setupRuntime();
  setupLayers();
  setupSelectivities();
  setupPenalties();
  setupDirectedProcesses();

  // Validate and Build
  validateAll();
  buildAll();
}

//**********************************************************************
// void CBaseTestFixture::setupConfiguration()
// Setup our CConfiguration Object
//**********************************************************************
void CBaseTestFixture::setupConfiguration() {
  // Setup Defaults
  BOOST_REQUIRE_NO_THROW(pConfig->setHumanStartYear(1990));
  BOOST_REQUIRE_NO_THROW(pConfig->setMaxAge(20));
  BOOST_REQUIRE_NO_THROW(pConfig->setMinAge(0));
  BOOST_REQUIRE_NO_THROW(pConfig->setNumberOfTimeSteps(1));
  BOOST_REQUIRE_NO_THROW(pConfig->setNumberOfYearsToProject(1));
  BOOST_REQUIRE_NO_THROW(pConfig->setNumberOfYearsToRun(1));
  BOOST_REQUIRE_NO_THROW(pConfig->setPopulateWithDummyData(true));
  BOOST_REQUIRE_NO_THROW(pConfig->setVerboseMode(false));
  BOOST_REQUIRE_NO_THROW(pConfig->addCategory("immature"));
  BOOST_REQUIRE_NO_THROW(pConfig->addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(pConfig->addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(immatureIndex = pConfig->getCategoryIndexForName("immature"));
  BOOST_REQUIRE_NO_THROW(matureIndex = pConfig->getCategoryIndexForName("mature"));
  BOOST_REQUIRE_NO_THROW(spawningIndex = pConfig->getCategoryIndexForName("spawning"));
  BOOST_REQUIRE_THROW(pConfig->addCategory("mature"), string);
}

//**********************************************************************
// void CBaseTestFixture::setupWorld()
// Setup our CWorld Object
//**********************************************************************
void CBaseTestFixture::setupWorld() {
  // Set Params
  BOOST_REQUIRE_NO_THROW(pWorld->setHeight(3));
  BOOST_REQUIRE_NO_THROW(pWorld->setWidth(3));
  BOOST_REQUIRE_NO_THROW(pWorld->setBaseLayer("double_layer"));
}

//**********************************************************************
// void CBaseTestFixture::setupRuntime()
// Setup our CRuntimeController
//**********************************************************************
void CBaseTestFixture::setupRuntime() {
  pRuntime->setRunMode("basic_run");
}

//**********************************************************************
// void CBaseTestFixture::setupLayers()
// Setup Some Basic Layers
//**********************************************************************
void CBaseTestFixture::setupLayers() {

  //***************************************************
  // Double Layer Varient
  CDoubleLayer *pLayer   = 0;
  BOOST_REQUIRE_NO_THROW(pLayer = new CDoubleLayer());
  BOOST_REQUIRE_NO_THROW(pLayer->setLabel("double_layer"));

  for (int i = 0; i < pWorld->getHeight(); ++i)
    for (int j = 0; j < pWorld->getWidth(); ++j)
      BOOST_REQUIRE_NO_THROW(pLayer->setValue((i+1), (j+1), 1.0));

  BOOST_REQUIRE_NO_THROW(pLayerManager->addLayer(pLayer));

  //***************************************************
  // Double Layer Varient
  BOOST_REQUIRE_NO_THROW(pLayer = new CDoubleLayer());
  BOOST_REQUIRE_NO_THROW(pLayer->setLabel("double_layer_varient"));

  for (int i = 0; i < pWorld->getHeight(); ++i)
    for (int j = 0; j < pWorld->getWidth(); ++j)
      BOOST_REQUIRE_NO_THROW(pLayer->setValue((i+1), (j+1), 100.0 - (i+j)));

  BOOST_REQUIRE_NO_THROW(pLayerManager->addLayer(pLayer));

  //***************************************************
  // Abundance Layer
  CAbundanceLayer *pABLayer = 0;
  BOOST_REQUIRE_NO_THROW(pABLayer = new CAbundanceLayer());
  BOOST_REQUIRE_NO_THROW(pABLayer->setLabel("abundance_layer"));
  BOOST_REQUIRE_NO_THROW(pABLayer->addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(pABLayer->addSelectivity("constant_selectivity"));

  BOOST_REQUIRE_NO_THROW(pLayerManager->addLayer(pABLayer));

  //***************************************************
  // Distance Layer
  CDistanceLayer *pDisLayer = 0;
  BOOST_REQUIRE_NO_THROW(pDisLayer = new CDistanceLayer());
  BOOST_REQUIRE_NO_THROW(pDisLayer->setLabel("distance_layer"));

  BOOST_REQUIRE_NO_THROW(pLayerManager->addLayer(pDisLayer));

  //***************************************************
  // String Layer
  CStringLayer *pStrLayer = 0;
  BOOST_REQUIRE_NO_THROW(pStrLayer = new CStringLayer());
  BOOST_REQUIRE_NO_THROW(pStrLayer->setLabel("string_layer"));

  for (int i = 0; i < pWorld->getHeight(); ++i) {
    BOOST_REQUIRE_NO_THROW(pStrLayer->setValue( (i+1), 1, "grp01"));
    BOOST_REQUIRE_NO_THROW(pStrLayer->setValue( (i+1), 2, "grp02"));
    BOOST_REQUIRE_NO_THROW(pStrLayer->setValue( (i+1), 3, "grp03"));
  }

  BOOST_REQUIRE_NO_THROW(pLayerManager->addLayer(pStrLayer));
}

//**********************************************************************
// void CBaseTestFixture::setupSelectivities()
// Setup Some Basic Selectivities
//**********************************************************************
void CBaseTestFixture::setupSelectivities() {

  //*******************************************************
  // Constant Selectivity
  CConstantSelectivity *pConSelectivity = 0;
  BOOST_REQUIRE_NO_THROW(pConSelectivity = new CConstantSelectivity());
  BOOST_REQUIRE_NO_THROW(pConSelectivity->setLabel("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(pConSelectivity->setC(1.0));

  BOOST_REQUIRE_NO_THROW(pSelectivityManager->addSelectivity(pConSelectivity));

  //*******************************************************
  // Double-Normal Selectivity
  CDoubleNormalSelectivity *pDNSelectivity = 0;
  BOOST_REQUIRE_NO_THROW(pDNSelectivity = new CDoubleNormalSelectivity());
  BOOST_REQUIRE_NO_THROW(pDNSelectivity->setLabel("double_normal_selectivity"));
  BOOST_REQUIRE_NO_THROW(pDNSelectivity->setMu(3));
  BOOST_REQUIRE_NO_THROW(pDNSelectivity->setSigmaL(1));
  BOOST_REQUIRE_NO_THROW(pDNSelectivity->setSigmaR(5));

  BOOST_REQUIRE_NO_THROW(pSelectivityManager->addSelectivity(pDNSelectivity));

  //*******************************************************
  // Knife-Edge Selectivity
  CKnifeEdgeSelectivity *pKESelectivity = 0;
  BOOST_REQUIRE_NO_THROW(pKESelectivity = new CKnifeEdgeSelectivity());
  BOOST_REQUIRE_NO_THROW(pKESelectivity->setLabel("knife_edge_selectivity"));
  BOOST_REQUIRE_NO_THROW(pKESelectivity->setC(5.0));

  BOOST_REQUIRE_NO_THROW(pSelectivityManager->addSelectivity(pKESelectivity));

  //*******************************************************
  // Logistic-Producing Selectivity
  CLogisticProducingSelectivity *pLPSelectivity = 0;
  BOOST_REQUIRE_NO_THROW(pLPSelectivity = new CLogisticProducingSelectivity());
  BOOST_REQUIRE_NO_THROW(pLPSelectivity->setLabel("logistic_producing_selectivity"));
  BOOST_REQUIRE_NO_THROW(pLPSelectivity->setL(1));
  BOOST_REQUIRE_NO_THROW(pLPSelectivity->setH(20));
  BOOST_REQUIRE_NO_THROW(pLPSelectivity->setA50(8));
  BOOST_REQUIRE_NO_THROW(pLPSelectivity->setAto95(3));

  BOOST_REQUIRE_NO_THROW(pSelectivityManager->addSelectivity(pLPSelectivity));

  //*******************************************************
  // Logistic Selectivity
  CLogisticSelectivity *pLoSelectivity = 0;
  BOOST_REQUIRE_NO_THROW(pLoSelectivity = new CLogisticSelectivity());
  BOOST_REQUIRE_NO_THROW(pLoSelectivity->setLabel("logistic_selectivity"));
  BOOST_REQUIRE_NO_THROW(pLoSelectivity->setA50(8));
  BOOST_REQUIRE_NO_THROW(pLoSelectivity->setAto95(3));

  BOOST_REQUIRE_NO_THROW(pSelectivityManager->addSelectivity(pLoSelectivity));
}

//**********************************************************************
// void CBaseTestFixture::setupPenalties()
//
//**********************************************************************
void CBaseTestFixture::setupPenalties() {

  // ************************************
  // Penalty
  CPenalty *pPenalty = 0;
  pPenalty = new CPenalty();
  pPenalty->setLabel("penalty");
  pPenalty->setLogScale(false);
  pPenalty->setMultiplier(100);

  pPenaltyManager->addPenalty(pPenalty);

  //***************************************
  // Penalty With Log Scale
  pPenalty = new CPenalty();
  pPenalty->setLabel("penalty_logscale");
  pPenalty->setLogScale(true);
  pPenalty->setMultiplier(100);

  pPenaltyManager->addPenalty(pPenalty);
}

//**********************************************************************
// void CBaseTestFixture::setupDirectedProcesses()
// Setup the Directed processes
//**********************************************************************
void CBaseTestFixture::setupDirectedProcesses() {

  //***************************************
  // Constant
  CConstantPreferenceFunction *pConstant = new CConstantPreferenceFunction();
  pConstant->setLabel("constant_directed");
  pConstant->setAlpha(3.0);
  pConstant->setLayerName("double_layer");
  pDirectedProcessManager->addProcess(pConstant);

  //*****************************************
  // Constant -Distance Layer
  CConstantPreferenceFunction *pConstantDist = new CConstantPreferenceFunction();
  pConstantDist->setLabel("constant_directed_distance");
  pConstantDist->setAlpha(1.0);
  pConstantDist->setLayerName("distance_layer");
  pDirectedProcessManager->addProcess(pConstantDist);

  //***************************************
  // Double-Normal
  CDoubleNormalPreferenceFunction *pDoubleNormal = new CDoubleNormalPreferenceFunction();
  pDoubleNormal->setLabel("double_normal_directed");
  pDoubleNormal->setLayerName("double_layer");
  pDoubleNormal->setAlpha(3.0);
  pDoubleNormal->setMu(3.0);
  pDoubleNormal->setSigmaL(1.0);
  pDoubleNormal->setSigmaR(5.0);
  pDirectedProcessManager->addProcess(pDoubleNormal);

  //*************************************
  // Exponential
  CExponentialPreferenceFunction *pExponential = new CExponentialPreferenceFunction();
  pExponential->setLabel("exponential_directed");
  pExponential->setLayerName("double_layer");
  pExponential->setAlpha(3.0);
  pExponential->setLambda(5.0);
  pDirectedProcessManager->addProcess(pExponential);

  //************************************
  // Inverse Logistic
  CInverseLogisticPreferenceFunction *pInverse = new CInverseLogisticPreferenceFunction();
  pInverse->setLabel("inverse_logistic_directed");
  pInverse->setLayerName("double_layer");
  pInverse->setA50(3.0);
  pInverse->setAto95(8.0);
  pInverse->setAlpha(3.0);
  pDirectedProcessManager->addProcess(pInverse);

  //*************************************
  // Logistic
  CLogisticPreferenceFunction *pLogistic = new CLogisticPreferenceFunction();
  pLogistic->setLabel("logistic_directed");
  pLogistic->setLayerName("double_layer");
  pLogistic->setA50(3.0);
  pLogistic->setAto95(8.0);
  pLogistic->setAlpha(3.0);
  pDirectedProcessManager->addProcess(pLogistic);

  //**************************************
  // Normal
  CNormalPreferenceFunction *pNormal = new CNormalPreferenceFunction();
  pNormal->setLabel("normal_directed");
  pNormal->setLayerName("double_layer");
  pNormal->setAlpha(3.0);
  pNormal->setMu(8.0);
  pNormal->setSigma(5.0);
  pDirectedProcessManager->addProcess(pNormal);

  //***************************************
  // Threshold
  CThresholdPreferenceFunction *pThreshold = new CThresholdPreferenceFunction();
  pThreshold->setLabel("threshold_directed");
  pThreshold->setLayerName("double_layer");
  pThreshold->setAlpha(3.0);
  pThreshold->setLambda(4.0);
  pThreshold->setN(5.0);
  pDirectedProcessManager->addProcess(pThreshold);

  //***************************************
  // Threshold Distance
  CThresholdPreferenceFunction *pDThreshold = new CThresholdPreferenceFunction();
  pDThreshold->setLabel("threshold_directed_distance");
  pDThreshold->setLayerName("distance_layer");
  pDThreshold->setAlpha(3.0);
  pDThreshold->setLambda(4.0);
  pDThreshold->setN(1.1);
  pDirectedProcessManager->addProcess(pDThreshold);
}

//**********************************************************************
// void CBaseTestFixture::validateAll()
// Validate our Objects
//**********************************************************************
void CBaseTestFixture::validateAll() {
  pConfig->validate();
  pWorld->validate();
  pLayerManager->validate();
  pLayerManager->validate();
  pSelectivityManager->validate();
  pPenaltyManager->validate();
  pDirectedProcessManager->validate();
}

//**********************************************************************
// void CBaseTestFixture::buildAll()
// Build our Objects
//**********************************************************************
void CBaseTestFixture::buildAll() {
  pWorld->build();
  pLayerManager->build();
  pSelectivityManager->build();
  pPenaltyManager->build();
  pDirectedProcessManager->build();
}

//**********************************************************************
// CBaseTestFixture::~CBaseTestFixture()
// Default Destructor
//**********************************************************************
CBaseTestFixture::~CBaseTestFixture() {
  // Cleanup Everything. The RuntimeController will destroy
  // Everything for us.
  CRuntimeController::Destroy();
}

#endif
