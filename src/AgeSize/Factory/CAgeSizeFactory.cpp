//============================================================================
// Name        : CAgeSizeFactory.cpp
// Author      : A.Dunn
// Date        : 24/05/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CAgeSizeFactory.h"
#include "../CAgeSize.h"
#include "../CAgeSizeManager.h"
#include "../Children/CNoneAgeSize.h"
#include "../Children/CSchnuteAgeSize.h"
#include "../Children/CVonBertalanffyAgeSize.h"
#include "../../Helpers/CError.h"


//**********************************************************************
// CAgeSize* CAgeSizeFactory::buildAgeSize(string type, bool registerWithManager)
//
//**********************************************************************
CAgeSize* CAgeSizeFactory::buildAgeSize(string type, bool registerWithManager) {

  CAgeSize *pAgeSize = 0;

  if (type == PARAM_NONE)
    pAgeSize = new CNoneAgeSize();
  else if (type == PARAM_VONBERTALANFFY)
    pAgeSize = new CVonBertalanffyAgeSize();
  else if (type == PARAM_SCHNUTE)
    pAgeSize = new CSchnuteAgeSize();
  else
    CError::errorUnknown(PARAM_AGE_SIZE, type);

  if (registerWithManager)
    CAgeSizeManager::Instance()->addAgeSize(pAgeSize);

  return pAgeSize;
}
