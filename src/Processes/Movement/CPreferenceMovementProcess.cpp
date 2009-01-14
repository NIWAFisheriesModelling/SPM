//============================================================================
// Name        : CPreferenceMovementProcess.cpp
// Author      : S.Rasmussen
// Date        : 15/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CPreferenceMovementProcess.h"

//**********************************************************************
// CPreferenceMovementProcess::CPreferenceMovementProcess(CPreferenceMovementProcess *Process)
// Default constructor
//**********************************************************************
CPreferenceMovementProcess::CPreferenceMovementProcess(CPreferenceMovementProcess *Process)
: CMovementProcess(Process) {
  throw string("Not yet implemented"); // TODO: Implement this
}

//**********************************************************************
// void CPreferenceMovementProcess::validate()
// Validate the process
//**********************************************************************
void CPreferenceMovementProcess::validate() {
  try {
    throw string("Not yet implemented"); // TODO: Implement this
  } catch (string Ex) {
    Ex = "CPreferenceMovementProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPreferenceMovementProcess::build()
// Build the process
//**********************************************************************
void CPreferenceMovementProcess::build() {
  try {
    throw string("Not yet implemented"); // TODO: Implement this
  } catch (string Ex) {
    Ex = "CPreferenceMovementProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPreferenceMovementProcess::execute()
// Execute the process
//**********************************************************************
void CPreferenceMovementProcess::execute() {
  try {
    throw string("Not yet implemented"); // TODO: Implement this
  } catch (string Ex) {
    Ex = "CPreferenceMovementProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CPreferenceMovementProcess::~CPreferenceMovementProcess()
// Destructor
//**********************************************************************
CPreferenceMovementProcess::~CPreferenceMovementProcess() {
}
