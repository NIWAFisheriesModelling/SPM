//============================================================================
// Name        : CBiomassEventMortalityProcess.cpp
// Author      : S.Rasmussen
// Date        : 15/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CBiomassEventMortalityProcess.h"

//**********************************************************************
// CBiomassEventMortalityProcess::CBiomassEventMortalityProcess(CBiomassEventMortalityProcess *Process)
// Default constructor
//**********************************************************************
CBiomassEventMortalityProcess::CBiomassEventMortalityProcess(CBiomassEventMortalityProcess *Process)
: CProcess(Process) {
  throw string("Not yet implemented"); // TODO: Implement this
}

//**********************************************************************
// void CBiomassEventMortalityProcess::validate()
// Validate the process
//**********************************************************************
void CBiomassEventMortalityProcess::validate() {
  try {
    throw string("Not yet implemented"); // TODO: Implement this
  } catch (string Ex) {
    Ex = "CBiomassEventMortalityProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CBiomassEventMortalityProcess::build()
// Build the process
//**********************************************************************
void CBiomassEventMortalityProcess::build() {
  try {
    throw string("Not yet implemented"); // TODO: Implement this
  } catch (string Ex) {
    Ex = "CBiomassEventMortalityProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CBiomassEventMortalityProcess::execute()
// Execute the process
//**********************************************************************
void CBiomassEventMortalityProcess::execute() {
  try {
    throw string("Not yet implemented"); // TODO: Implement this
  } catch (string Ex) {
    Ex = "CBiomassEventMortalityProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CBiomassEventMortalityProcess::~CBiomassEventMortalityProcess()
// Destructor
//**********************************************************************
CBiomassEventMortalityProcess::~CBiomassEventMortalityProcess() {
}
