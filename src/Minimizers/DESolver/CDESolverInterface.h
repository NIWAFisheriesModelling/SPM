//============================================================================
// Name        : CDESolverInterface.h
// Author      : S.Rasmussen
// Date        : 1/05/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description : 
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $ 
//============================================================================
#ifndef CDESOLVERINTERFACE_H_
#define CDESOLVERINTERFACE_H_

// Local Headers
#include "../CMinimizer.h"

//**********************************************************************
//
//
//**********************************************************************
class CDESolverInterface : public CMinimizer {
public:
  // Functions
  CDESolverInterface();
  virtual                    ~CDESolverInterface();
  void                       runEstimation();

};

#endif /*CDESOLVERINTERFACE_H_*/
