//============================================================================
// Name        : CPopulationConfigLoader.h
// Author      : S.Rasmussen
// Date        : 13/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CPOPULATIONCONFIGLOADER_H_
#define CPOPULATIONCONFIGLOADER_H_

// Local Headers
#include "CBaseConfigLoader.h"
#include "../CTimeStepManager.h"
#include "../CProcessManager.h"
#include "../CLayerManager.h"
#include "../CSelectivityManager.h"
#include "../CDirectedProcessManager.h"
#include "../CInitializationManager.h"

//**********************************************************************
//
//
//**********************************************************************
class CPopulationConfigLoader : public CBaseConfigLoader {
public:
  // Functions
	CPopulationConfigLoader(string Directory);
  virtual                   ~CPopulationConfigLoader();
  void                      processConfigFile();

protected:
  // Functions
  void                      loadSpatialStructure();
  void                      loadPopulationStructure();
  void                      loadInitialization();
  void                      loadAnnualCycle();
  void                      loadTimeStep();
  void                      loadInitialisationPhase();
  void                      loadPopulationProcess();
  void                      loadPopulationProcess_Ageing();
  void                      loadPopulationProcess_Recruitment();
  void                      loadPopulationProcess_NaturalMortality();
  void                      loadPopulationProcess_EventMortality();
  void                      loadPopulationProcess_CategoryTransition();
  void                      loadMovementProcess();
  void                      loadMovementProcess_Uniform();
  void                      loadMovementProcess_Directed();
  void                      loadLayer();
  void                      loadLayer_Double();
  void                      loadLayer_String();
  void                      loadLayer_Distance();
  void                      loadLayer_Abundance();
  void                      loadSelectivity();
  void                      loadSelectivity_Constant();
  void                      loadSelectivity_Logistic();
  void                      loadSelectivity_LogisticProducing();
  void                      loadSelectivity_KnifeEdge();
  void                      loadSelectivity_DoubleNormal();
  void                      loadDirectedProcess();
  void                      loadDirectedProcess_Exponential();
  void                      loadDirectedProcess_Threshold();
  void                      loadDirectedProcess_Normal();
  void                      loadDirectedProcess_DoubleNormal();
  void                      loadDirectedProcess_Logistic();
  void                      loadDirectedProcess_InverseLogistic();
  void                      loadDirectedProcess_Constant();
  bool                      loadBaseProcessAttributes(CProcess *Process);
  bool                      loadBaseDirectedProcessAttributes(CDirectedProcess *Process);

  // Variables
  CTimeStepManager          *pTimeStepManager;
  CProcessManager           *pProcessManager;
  CLayerManager             *pLayerManager;
  CSelectivityManager       *pSelectivityManager;
  CDirectedProcessManager   *pDirectedProcessManager;
  CInitializationManager    *pInitializationManager;

};

#endif /*CPOPULATIONCONFIGLOADER_H_*/
