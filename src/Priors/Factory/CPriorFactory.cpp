//============================================================================
// Name        : CPriorFactory.cpp
// Author      : S.Rasmussen
// Date        : 12/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CPriorFactory.h"
#include "../CPriorManager.h"
#include "../../Translations/Translations.h"
#include "../Children/CBetaPrior.h"
#include "../Children/CLogNormalPrior.h"
#include "../Children/CNormalByStdevPrior.h"
#include "../Children/CNormalLogPrior.h"
#include "../Children/CNormalPrior.h"
#include "../Children/CUniformLogPrior.h"
#include "../Children/CUniformPrior.h"
#include "../../Helpers/CError.h"

//**********************************************************************
// CPrior* CPriorFactory::buildPrior(string type, bool registerWithManager)
// Build prior based on type
//**********************************************************************
CPrior* CPriorFactory::buildPrior(string type, bool registerWithManager) {

  CPrior *pPrior = 0;

  if (type == PARAM_BETA)
    pPrior = new CBetaPrior();
  else if (type == PARAM_LOGNORMAL)
    pPrior = new CLogNormalPrior();
  else if (type == PARAM_NORMAL_BY_STDEV)
    pPrior = new CNormalByStdevPrior();
  else if (type == PARAM_NORMAL_LOG)
    pPrior = new CNormalLogPrior();
  else if (type == PARAM_NORMAL)
    pPrior = new CNormalPrior();
  else if (type == PARAM_UNIFORM_LOG)
    pPrior = new CUniformLogPrior();
  else if (type == PARAM_UNIFORM)
    pPrior = new CUniformPrior();
  else
    CError::errorUnknown(PARAM_PRIOR, type);

  if (registerWithManager)
    CPriorManager::Instance()->addPrior(pPrior);

  return pPrior;
}
