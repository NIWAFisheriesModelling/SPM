//============================================================================
// Name        : CMovementProcess.cpp
// Author      : S.Rasmussen
// Date        : 14/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Local Headers
#include "CMovementProcess.h"

//**********************************************************************
// CMovementProcess::CMovementProcess(CMovementProcess *Process = 0)
// Default Constructor
//**********************************************************************
CMovementProcess::CMovementProcess(CMovementProcess *Process)
: CProcess(Process) {

  // Vars
  sMethod             = "";
  dProportion         = 0.0;
  bHexMode            = false;

  registerEstimable(PARAM_PROPORTION, &dProportion);

  // Copy Construct
  if (Process != 0) {
    sMethod     = Process->getMethod();
    dProportion = Process->getProportion();
    bHexMode    = Process->getHexMode();
  }
}

//**********************************************************************
// void CMovementProcess::setMethod(string value)
// Set method, and Hex mode flag
//**********************************************************************
void CMovementProcess::setMethod(string value) {
  try {
    sMethod = value;

    if (sMethod.length() < 3)
      throw string(ERROR_LENGTH_METHOD);

    if (sMethod.substr(0, 3) == PARAM_HEX)
        bHexMode = true;
      else
        bHexMode = false;

  } catch (string Ex) {
    Ex = "CMovementProcess.setMethod()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMovementProcess::validate()
// Validate
//**********************************************************************
void CMovementProcess::validate() {
  try {
    // BaseValidate
    CProcess::validate();

    // Local Validation
    if (getMethod() == "")
      errorMissing(PARAM_METHOD);
    if (getProportion() == 0.0)
      errorMissing(PARAM_PROPORTION);

    // Check For Valid Method
    if ( (sMethod != PARAM_SQUARE_UNIFORM) && (sMethod != PARAM_HEX_UNIFORM) ) {
      throw string(ERROR_UNKNOWN_METHOD + sMethod);
    }

  } catch(string Ex) {
    Ex = "CMovementProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMovementProcess::build()
// Build
//**********************************************************************
void CMovementProcess::build() {
  try {
    CProcess::build();
  } catch (string Ex) {
    Ex = "CMovementProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMovementProcess::execute()
// Execute
//**********************************************************************
void CMovementProcess::execute() {
#ifndef OPTIMISE
  try {
#endif

    CProcess::execute();
#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CMovementProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CMovementProcess::doMove(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty)
// Do The Move To RIndex/CIndex
//**********************************************************************
void CMovementProcess::doMove(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty) {
#ifndef OPTIMISE
  try {
#endif
    // Get Target Base
    pTargetBase = pWorld->getBaseSquare( RIndex, CIndex);

    // Check if Target-Base Is Usable
    if (!checkUsableSquare(pTargetBase, RIndex, CIndex))
      return;

    // Get Target Diff
    pTargetDiff = pWorld->getDifferenceSquare( RIndex, CIndex);

    // Add/Sub Values
    pTargetDiff->addValue(SRIndex, SCIndex, Qty);
    pBase->subValue(SRIndex, SCIndex, Qty);

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CMovementProcess.doMove(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CMovementProcess::moveUp(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty)
// Move Amount of Fish Up from World(RowIndex, ColIndex)
//**********************************************************************
void CMovementProcess::moveUp(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty) {
#ifndef OPTIMISE
  try {
#endif

    // Can We Move Up?
    if (RIndex == 0)
      return;

    // Do it
    doMove( (RIndex-1), CIndex, SRIndex, SCIndex, Qty);

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CMovementProcess.moveUp(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CMovementProcess::moveDown(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty)
// Move Amount of Fish Down From World(RowIndex, ColIndex) Square(Row/Col)
//**********************************************************************
void CMovementProcess::moveDown(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty) {
#ifndef OPTIMISE
  try {
#endif

    // Can We Move Down?
    if ( RIndex == (iWorldHeight-1) )
      return;

    // Do it
    doMove( (RIndex+1), CIndex, SRIndex, SCIndex, Qty);

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CMovementProcess.moveDown(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CMovementProcess::moveLeft(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty)
// Move Amount of Fish Left From World(RowIndex, ColIndex)
//**********************************************************************
void CMovementProcess::moveLeft(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty) {
#ifndef OPTIMISE
  try {
#endif

    // Can We Move Left?
    if ( CIndex == 0 )
      return;

    // Do it
    doMove(RIndex, (CIndex-1), SRIndex, SCIndex, Qty);

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CMovementProcess.moveLeft(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CMovementProcess::moveRight(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty)
// Move Amount of Fish right from World(RowIndex,ColIndex)
//**********************************************************************
void CMovementProcess::moveRight(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty) {
#ifndef OPTIMISE
  try {
#endif
    // Can We Move Left?
    if ( CIndex == (iWorldWidth-1) )
      return;

    // Do it
    doMove(RIndex, (CIndex+1), SRIndex, SCIndex, Qty);

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CMovementProcess.moveRight(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CMovementProcess::moveLeftUp(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty)
// Move Amount of fish from World(RowIndex, ColIndex)
//**********************************************************************
void CMovementProcess::moveLeftUp(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty) {
#ifndef OPTIMISE
  try {
#endif
    // Can We Move Left?
    if (CIndex == 0)
      return;
    // Can We Move Up?
    if ( RIndex == 0)
      return;

    // Do it
    doMove( (RIndex-1), (CIndex-1), SRIndex, SCIndex, Qty);

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CMovementProcess.moveLeftUp(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CMovementProcess::moveLeftDown(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty)
// Move amount of fish from World(RowIndex, ColIndex)
//**********************************************************************
void CMovementProcess::moveLeftDown(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty) {
#ifndef OPTIMISE
  try {
#endif
    // Can We Move Left?
    if (CIndex == 0)
      return;
    // Can We Move Down
    if ( RIndex == (iWorldHeight-1) )
      return;

    // Do it
    doMove( (RIndex+1), (CIndex-1), SRIndex, SCIndex, Qty);

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CMovementProcess.moveLeftDown(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}
//**********************************************************************
// CMovementProcess::~CMovementProcess()
// Default De-Constructor
//**********************************************************************
CMovementProcess::~CMovementProcess() {

}
