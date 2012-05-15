//============================================================================
// Name        : CMigrationMovementProcess.cpp
// Author      : S.Rasmussen
// Date        : 4/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CMigrationMovementProcess.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CComparer.h"

//**********************************************************************
// CMigrationMovementProcess::CMigrationMovementProcess()
// Default Constructor
//**********************************************************************
CMigrationMovementProcess::CMigrationMovementProcess() {
}

//**********************************************************************
// void CMigrationMovementProcess::validate()
// validate
//**********************************************************************
void CMigrationMovementProcess::validate() {
  try {
    // Base Validation
    CMovementProcess::validate();

    // Local Validation
    if (getCategoryCount() == 0)
      CError::errorMissing(PARAM_CATEGORIES);
    if (getSelectivityCount() == 0)
      CError::errorMissing(PARAM_SELECTIVITIES);
    if (getCategoryCount() != getSelectivityCount())
      CError::errorListSameSize(PARAM_CATEGORY, PARAM_SELECTIVITY);

  } catch (string &Ex) {
    Ex = "CMigrationMovementProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMigrationMovementProcess::build()
// build
//**********************************************************************
void CMigrationMovementProcess::build() {
  try {
    // Base Building
    CMovementProcess::build();

  } catch (string &Ex) {
    Ex = "CMigrationMovementProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMigrationMovementProcess::execute()
// execute
//**********************************************************************
void CMigrationMovementProcess::execute() {
#ifndef OPTIMIZE
  try {
#endif

#ifndef OPTIMIZE
  } catch (string &Ex) {
    Ex = "CMigrationMovementProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CMigrationMovementProcess::~CMigrationMovementProcess()
// Default De-Constructor
//**********************************************************************
CMigrationMovementProcess::~CMigrationMovementProcess() {
}
