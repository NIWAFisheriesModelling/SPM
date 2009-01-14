//============================================================================
// Name        : CConstantMortalityRateProcess.cpp
// Author      : S.Rasmussen
// Date        : 15/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CConstantMortalityRateProcess.h"

//**********************************************************************
// CConstantMortalityRateProcess::CConstantMortalityRateProcess(CConstantMortalityRateProcess *Process)
// Default Constructor
//**********************************************************************
CConstantMortalityRateProcess::CConstantMortalityRateProcess(CConstantMortalityRateProcess *Process)
: CProcess(Process) {
  throw string("Not yet implemented"); // TODO: Implement this
}

//**********************************************************************
// void CConstantMortalityRateProcess::validate()
// Validate our process
//**********************************************************************
void CConstantMortalityRateProcess::validate() {
  try {
    throw string("Not yet implemented"); // TODO: Implement this
  } catch (string Ex) {
    Ex = "CConstantMortalityRateProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CConstantMortalityRateProcess::build()
// Build our process
//**********************************************************************
void CConstantMortalityRateProcess::build() {
  try {
    throw string("Not yet implemented"); // TODO: Implement this
  } catch (string Ex) {
    Ex = "CConstantMortalityRateProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CConstantMortalityRateProcess::execute()
// Execute our process
//**********************************************************************
void CConstantMortalityRateProcess::execute() {
  try {
    throw string("Not yet implemented"); // TODO: Implement function
  } catch (string Ex) {
    Ex = "CConstantMortalityRateProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CConstantMortalityRateProcess::~CConstantMortalityRateProcess()
// Destructor
//**********************************************************************
CConstantMortalityRateProcess::~CConstantMortalityRateProcess() {
}
