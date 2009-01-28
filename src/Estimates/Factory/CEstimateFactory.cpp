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
#include "../../Translations/Translations.h"
#include "../CEstimate.h"

//**********************************************************************
// CEstimate* CEstimateFactory::buildEstimate(string type, bool registerWithManager)
// Build our estimates
//**********************************************************************
CEstimate* CEstimateFactory::buildEstimate(string type, bool registerWithManager) {
  // NOTE: Please add Unit Tests when adding new types

  if (type == "")
    return new CEstimate();
  else
    throw string("unknown type: " + type); // TODO: FIX THIS

  return 0;
}
