//============================================================================
// Name        : CAbundanceObservation.h
// Author      : S.Rasmussen
// Date        : 4/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CABUNDANCEOBSERVATION_H_
#define CABUNDANCEOBSERVATION_H_

// Local Headers
#include "../CObservation.h"

// Classes
class CCatchability;

//**********************************************************************
//
//
//**********************************************************************
class CAbundanceObservation : public CObservation {
public:
  // Functions
  CAbundanceObservation();
  virtual                    ~CAbundanceObservation();
  void                       validate();
  void                       build();
  void                       execute();

protected:
  // Variables
  map<string, double>        mProportionMatrix;
  map<string, double>        mErrorValue;
  string                     sCatchability;
  CCatchability              *pCatchability;
  double                     dDelta;
  double                     dProportionTimeStep;
  double                     dProcessError;
};

#endif /*CABUNDANCEOBSERVATION_H_*/
