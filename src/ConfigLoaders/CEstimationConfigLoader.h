//============================================================================
// Name        : CEstimationConfigLoader.h
// Author      : S.Rasmussen
// Date        : 17/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CESTIMATIONCONFIGLOADER_H_
#define CESTIMATIONCONFIGLOADER_H_

// Local Headers
#include "CBaseConfigLoader.h"
#include "../World/CWorld.h"
#include "../Minimizers/CMinimizerManager.h"
#include "../Estimates/CEstimateManager.h"
#include "../MCMC/CMCMC.h"
#include "../Observations/CObservationManager.h"
#include "../Penalties/CPenaltyManager.h"
#include "../Profiles/CProfileManager.h"
#include "../Priors/CPriorManager.h"
#include "../Qs/CQManager.h"

//**********************************************************************
//
//
//**********************************************************************
class CEstimationConfigLoader : public CBaseConfigLoader {
public:
  // Functions
	CEstimationConfigLoader(string Directory);
	virtual                    ~CEstimationConfigLoader();
	void                       processConfigFile();

protected:
  // Functions
  void                       loadMPD();
  void                       loadMinimizer();
  void                       loadMinimizer_DeSolver();
  void                       loadMinimizer_GammaDiff();
  void                       loadMCMC();
  void                       loadProfile();
  void                       loadProportionsAtAge();
  void                       loadProportionsByCategory();
  void                       loadAbundance();
  void                       loadAgeingError();
  void                       loadEstimate();
  void                       loadPrior();
  void                       loadPrior_Uniform();
  void                       loadPrior_Normal();
  void                       loadPrior_NormalByStdev();
  void                       loadPrior_LogNormal();
  void                       loadPrior_UniformLog();
  void                       loadPrior_NormalLog();
  void                       loadPrior_Beta();
  void                       loadPenalty();
  void                       loadQ();
  bool                       loadBaseMinimizerAttributes(CMinimizer *pMinimizer);

  // Variables
  CWorld                     *pWorld;
  CMinimizerManager          *pMinimizerManager;
  CEstimateManager           *pEstimateManager;
  CMCMC                      *pMCMC;
  CProfileManager            *pProfileManager;
  CObservationManager        *pObservationManager;
  CPriorManager              *pPriorManager;
  CPenaltyManager            *pPenaltyManager;
  CQManager                  *pQManager;
};

#endif /*CESTIMATIONCONFIGLOADER_H_*/
