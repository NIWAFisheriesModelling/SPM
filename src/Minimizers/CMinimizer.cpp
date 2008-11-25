//============================================================================
// Name        : CMinimizer.cpp
// Author      : S.Rasmussen
// Date        : 2/05/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description : 
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $ 
//============================================================================

// Local Headers
#include "CMinimizer.h"

//**********************************************************************
// CMinimizer::CMinimizer()
// Default Constructor
//**********************************************************************
CMinimizer::CMinimizer() {
  iMaxIterations = 300;
  iMaxEvaluations = 1000;
  dGradientTolerance = 0.002;
  dStepsize = 1e-4;
}

//**********************************************************************
// CMinimizer::~CMinimizer()
// Default De-Constructor
//**********************************************************************
CMinimizer::~CMinimizer() {
}
