//============================================================================
// Name        : CMCMCFactory.cpp
// Author      : S.Rasmussen
// Date        : 10/11/2014
// Copyright   : Copyright NIWA Science ©2014 - www.niwa.co.nz
// Description :
//============================================================================

#include "CMCMCFactory.h"
#include "../CMCMCManager.h"
#include "../../Helpers/CError.h"
#include "../../Translations/Translations.h"
#include "../Children/CMetropolisHastingsMCMC.h"

//**********************************************************************
// CProcessFactory::CProcessFactory()
// Default Constructor
//**********************************************************************
CMCMC* CMCMCFactory::buildMCMC(string type, bool registerWithManager) {

  CMCMC *pMCMC = 0;

  if (type == PARAM_METROPOLIS_HASTINGS || type == "")
    pMCMC = new CMetropolisHastingsMCMC();
  else
    CError::errorUnknown(PARAM_MCMC, type);

  if (registerWithManager)
    CMCMCManager::Instance()->addMCMC(pMCMC);

  return pMCMC;
}

