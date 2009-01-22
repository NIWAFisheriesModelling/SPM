//============================================================================
// Name        : CMinimizerFactory.cpp
// Author      : S.Rasmussen
// Date        : 12/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CMinimizerFactory.h"
#include "../CMinimizerManager.h"
#include "../../Translations/Translations.h"
#include "../DESolver/CDESolverInterface.h"
#include "../GammaDiff/CGammaDiffInterface.h"

//**********************************************************************
// CMinimizer* CMinimizerFactory::buildMinimizer(string type)
// Build our Minimizer based on type
//**********************************************************************
CMinimizer* CMinimizerFactory::buildMinimizer(string type, bool registerWithManager) {

  CMinimizer* pMinimizer = 0;

  if (type == PARAM_GAMMADIFF)
    pMinimizer = new CGammaDiffInterface();
  else if (type == PARAM_DESOLVER)
    pMinimizer = new CDESolverInterface();
  else
    throw string("Unknown type: "+ type); // TODO: FIX THIS

  if (registerWithManager)
    CMinimizerManager::Instance()->addMinimizer(pMinimizer);

  return pMinimizer;
}
