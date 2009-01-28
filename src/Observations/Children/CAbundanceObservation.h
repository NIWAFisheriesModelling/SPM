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
  int                        getProportionCount() { return (int)mvProportionMatrix.size(); }
  string                     getProportionKey(int index);
  double                     getProportionValue(string key);
  int                        getCVCount() { return (int)mvCVMatrix.size(); }
  string                     getCVKey(int index);
  double                     getCVValue(string key);
  string                     getQ() { return sQ; }
  double                     getCVProcessError() { return dCVProcessError; }
  void                       validate();
  void                       build();
  void                       execute();

protected:
  // Variables
  map<string, double>        mvProportionMatrix;
  map<string, double>        mvCVMatrix;
  string                     sQ;
  CCatchability              *pQ;
  double                     dSigma;
  double                     dCVProcessError;
};

#endif /*CABUNDANCEOBSERVATION_H_*/
