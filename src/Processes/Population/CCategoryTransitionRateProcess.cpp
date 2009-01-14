//============================================================================
// Name        : CCategoryTransitionRateProcess.cpp
// Author      : S.Rasmussen
// Date        : 15/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CCategoryTransitionRateProcess.h"

//**********************************************************************
// CCategoryTransitionRateProcess::CCategoryTransitionRateProcess(CCategoryTransitionRateProcess *Process)
// Default constructor
//**********************************************************************
CCategoryTransitionRateProcess::CCategoryTransitionRateProcess(CCategoryTransitionRateProcess *Process)
: CProcess(Process) {
  throw string("Not yet implemented"); // TODO: Implement this
}

//**********************************************************************
// void CCategoryTransitionRateProcess::validate()
// validate the process
//**********************************************************************
void CCategoryTransitionRateProcess::validate() {
  try {
    throw string("Not yet implemented"); // TODO: Implement this
  } catch (string Ex) {
    Ex = "CCategoryTransitionRateProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CCategoryTransitionRateProcess::build()
// Build the process
//**********************************************************************
void CCategoryTransitionRateProcess::build() {
  try {
    throw string("Not yet implemented"); // TODO: Implement this
  } catch (string Ex) {
    Ex = "CCategoryTransitionRateProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CCategoryTransitionRateProcess::execute()
// Execute the process
//**********************************************************************
void CCategoryTransitionRateProcess::execute() {
  try {
    throw string("Not yet implemented"); // TODO: Implement this
  } catch (string Ex) {
    Ex = "CCategoryTransitionRateProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CCategoryTransitionRateProcess::~CCategoryTransitionRateProcess()
// Destructor
//**********************************************************************
CCategoryTransitionRateProcess::~CCategoryTransitionRateProcess() {
}
