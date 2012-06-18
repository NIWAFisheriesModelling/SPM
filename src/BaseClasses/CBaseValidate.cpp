//============================================================================
// Name        : CBaseValidate.cpp
// Author      : S.Rasmussen
// Date        : 28/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global headers
#include <boost/lexical_cast.hpp>

// Local headers
#include "CBaseValidate.h"
#include "../Helpers/CError.h"

//**********************************************************************
// CBaseValidate::CBaseValidate()
// Default Constructor
//**********************************************************************
CBaseValidate::CBaseValidate() {

  // Default sLabel
  sLabel  = "";

  // Register Variable
  pParameterList->registerAllowed(PARAM_LABEL);
  pParameterList->registerAllowed(PARAM_TYPE);
}

//**********************************************************************
// void CBaseValidate::validate()
// Validate
//**********************************************************************
void CBaseValidate::validate() {
  try {
    // Populate our variable
    sLabel  = pParameterList->getString(PARAM_LABEL);

    // Check label is alphanumeric (incl. '_')
    for (size_t i=0; i < sLabel.length(); ++i) {
      std::cerr << sLabel.at(i) << "\n";
      if ( !(isalnum(sLabel.at(i)) || sLabel.at(i)== boost::lexical_cast<char>("_")) )
        CError::errorInvalidCharacter(boost::lexical_cast<string>(sLabel.at(i)),sLabel);
    }

    // Validate known parameters against bad ones
    pParameterList->checkInvalidParameters();

  } catch(string &Ex) {
    Ex = "CBaseValidate.validate(" + getLabel() + ")->" + Ex; // No label defined yet.
    throw Ex;
  }
}

//**********************************************************************
// CBaseValidate::~CBaseValidate()
// Destructor
//**********************************************************************
CBaseValidate::~CBaseValidate() {
}
