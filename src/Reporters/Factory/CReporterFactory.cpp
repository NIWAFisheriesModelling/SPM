//============================================================================
// Name        : CReporterFactory.cpp
// Author      : S.Rasmussen
// Date        : 9/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CReporterFactory.h"
#include "../CReporterManager.h"
#include "../Children/CWorldStateReporter.h"
#include "../Children/CObjectiveFunctionReporter.h"
#include "../Children/CEstimateSummaryReporter.h"
#include "../Children/CEstimateValueReporter.h"

//**********************************************************************
//
//
//**********************************************************************
CReporter* CReporterFactory::buildReporter(string type, bool registerWithManager) {

  CReporter *pReporter = 0;

  if (type == PARAM_WORLD_STATE)
    pReporter = new CWorldStateReporter();
  else if (type == PARAM_OBJECTIVE_FUNCTION)
    pReporter = new CObjectiveFunctionReporter();
  else if (type == PARAM_ESTIMATE_SUMMARY)
    pReporter = new CEstimateSummaryReporter();
  else if (type == PARAM_ESTIMATE_VALUE)
    pReporter = new CEstimateValueReporter();
  else
    throw string("Unknown type: " + type);

  // Add to manager if needed
  if (registerWithManager)
    CReporterManager::Instance()->addReporter(pReporter);

  return pReporter;
}
