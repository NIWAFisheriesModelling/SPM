//============================================================================
// Name        : CEstimateFactory.cpp
// Author      : S.Rasmussen
// Date        : 12/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description : << See CEstimateFactory.h >>
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CEstimateFactory.h"
#include "../CEstimateManager.h"
#include "../../Helpers/CError.h"


//**********************************************************************
// CEstimate* CEstimateFactory::buildEstimate(string type, bool registerWithManager)
// Build our estimates
//**********************************************************************
CEstimate* CEstimateFactory::buildEstimate(string type, bool registerWithManager) {

  CEstimate *pEstimate = 0;

  if (type == "")
    pEstimate = new CEstimate();
  else
    CError::errorUnknown(PARAM_ESTIMATE, type);

  if (registerWithManager)
    CEstimateManager::Instance()->addEstimate(pEstimate);

  return pEstimate;
}
