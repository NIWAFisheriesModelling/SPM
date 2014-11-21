//============================================================================
// Name        : CPDFFactory.cpp
// Author      : S.Rasmussen
// Date        : 7/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CPDFFactory.h"
#include "../CPDFManager.h"
#include "../../Translations/Translations.h"
#include "../../Helpers/CError.h"
#include "../Children/CNormalPDF.h"

//**********************************************************************
// CPDF* CPDFFactory::buildPDF(string type, bool registerWithManager)
// Build our buildPDF
//**********************************************************************
CPDF* CPDFFactory::buildPDF(string type, bool registerWithManager) {

  CPDF *pFunction = 0;

  if (type == PARAM_NORMAL)
    pFunction = new CNormalPDF();
  else
    CError::errorUnknown(PARAM_TYPE, type);

  if (registerWithManager)
    CPDFManager::Instance()->addPDF(pFunction);

  return pFunction;
}
