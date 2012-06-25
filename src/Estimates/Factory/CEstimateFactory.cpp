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
// CEstimateInfo* CEstimateFactory::buildEstimateInfo(bool registerWithManager)
// Build our estimates
//**********************************************************************
CEstimateInfo* CEstimateFactory::buildEstimateInfo(bool registerWithManager) {

  CEstimateInfo *pInfo = new CEstimateInfo();

  if (registerWithManager)
    CEstimateManager::Instance()->addEstimateInfo(pInfo);

  return pInfo;
}

CEstimate* CEstimateFactory::buildEstimate(bool registerWithManager) {
  CEstimate *estimate = new CEstimate();

  if (registerWithManager)
    CEstimateManager::Instance()->addEstimate(estimate);

  return estimate;
}
