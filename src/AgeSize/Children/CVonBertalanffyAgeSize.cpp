//============================================================================
// Name        : CVonBertalanffyAgeSize.cpp
// Author      : A.Dunn
// Date        : 24/05/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CVonBertalanffyAgeSize.h"
#include "../../Helpers/CError.h"

//**********************************************************************
// CVonBertalanffyAgeSize::CVonBertalanffyAgeSize()
// Default Constructor
//**********************************************************************
CVonBertalanffyAgeSize::CVonBertalanffyAgeSize() {

  // Register estimables
  registerEstimable(PARAM_LINF, &dLinf);
  registerEstimable(PARAM_K, &dK);
  registerEstimable(PARAM_T0, &dT0);
  registerEstimable(PARAM_CV, &dCV);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_LINF);
  pParameterList->registerAllowed(PARAM_K);
  pParameterList->registerAllowed(PARAM_T0);
  pParameterList->registerAllowed(PARAM_CV);
  pParameterList->registerAllowed(PARAM_DISTRIBUTION);

}

//**********************************************************************
// voidCVonBertalanffyAgeSize::validate()
// Validate the age-size relationship
//**********************************************************************
void CVonBertalanffyAgeSize::validate() {
  try {
    // Base
    CAgeSize::validate();

    // Get our variables
    dLinf           = pParameterList->getDouble(PARAM_LINF);
    dK              = pParameterList->getDouble(PARAM_K);
    dT0             = pParameterList->getDouble(PARAM_T0);
    dCV             = pParameterList->getDouble(PARAM_CV,true,0);
    sDistribution   = pParameterList->getString(PARAM_DISTRIBUTION,true, PARAM_NORMAL);

    // Validate
    if (dLinf <= 0)
      CError::errorLessThanEqualTo(PARAM_LINF, PARAM_ZERO);
    if (dK <= 0)
      CError::errorLessThanEqualTo(PARAM_K, PARAM_ZERO);
    if (dCV <= 0)
      CError::errorLessThanEqualTo(PARAM_CV, PARAM_ZERO);

    if ( (sDistribution != PARAM_NORMAL) && (sDistribution != PARAM_LOGNORMAL) )
      CError::errorUnknown(PARAM_DISTRIBUTION, sDistribution);
  } catch (string Ex) {
    Ex = "CVonBertalanffyAgeSize.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// voidCVonBertalanffyAgeSize::build()
// Validate the age-size relationship
//**********************************************************************
void CVonBertalanffyAgeSize::build() {
  try {
    // Base
    CAgeSize::build();

    // Rebuild
    rebuild();

  } catch (string Ex) {
    Ex = "CVonBertalanffyAgeSize.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// voidCVonBertalanffyAgeSize::rebuild()
// Validate the age-size relationship
//**********************************************************************
void CVonBertalanffyAgeSize::rebuild() {
  try {
    // Base
    CAgeSize::rebuild();

  } catch (string Ex) {
    Ex = "CVonBertalanffyAgeSize.rebuild(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CVonBertalanffyAgeSize::getMeanSize(double &age)
// Apply age-size relationship
//**********************************************************************
double CVonBertalanffyAgeSize::getMeanSize(double &age) {
  try {

    if ((-dK * (age - dT0)) > 10)
      throw("Fatal error in age-size relationship: exp(-k*(age-t0)) is enormous. The k or t0 parameters are probably wrong.");

    double dSize = dLinf * (1 - exp(-dK * (age - dT0)));

    if (dSize < 0)
      return 0.0;
    else
      return(dSize);

  } catch (string Ex) {
    Ex = "CVonBertalanffyAgeSize.getMeanSize(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CVonBertalanffyAgeSize::~CVonBertalanffyAgeSize()
// Destructor
//**********************************************************************
CVonBertalanffyAgeSize::~CVonBertalanffyAgeSize() {
}
