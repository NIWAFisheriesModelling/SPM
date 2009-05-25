//============================================================================
// Name        : CNoneAgeSize.cpp
// Author      : A.Dunn
// Date        : 24/05/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CNoneAgeSize.h"
#include "../../Helpers/CError.h"
#include "../../SizeWeight/CSizeWeight.h"

//**********************************************************************
// CNoneAgeSize::CNoneAgeSize()
// Default Constructor
//**********************************************************************
CNoneAgeSize::CNoneAgeSize() {

  // Register user allowed parameters

}

//**********************************************************************
// void CNoneAgeSize::validate()
// Validate the age-size relationship
//**********************************************************************
void CNoneAgeSize::validate() {

  try {

    // Base
    CAgeSize::validate();

  } catch (string Ex) {
    Ex = "CNoneAgeSize.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CNoneAgeSize::build()
// Validate the age-size relationship
//**********************************************************************
void CNoneAgeSize::build() {
  try {

    // Base
    CAgeSize::build();

  } catch (string Ex) {
    Ex = "CNoneAgeSize.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CNoneAgeSize::rebuild()
// Validate the age-size relationship
//**********************************************************************
void CNoneAgeSize::rebuild() {
  try {

  } catch (string Ex) {
    Ex = "CNoneAgeSize.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CNoneAgeSize::getMeanWeight(double &size)
// Apply size-weight relationship
//**********************************************************************
double CNoneAgeSize::getMeanWeight(double &age) {
  try {

    return 1;

  } catch (string Ex) {
    Ex = "CNoneAgeSize.getMeanWeight(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CNoneAgeSize::~CNoneAgeSize()
// Destructor
//**********************************************************************
CNoneAgeSize::~CNoneAgeSize() {
}
