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
#include "CObservation.h"

// Classes
class CQ;

//**********************************************************************
//
//
//**********************************************************************
class CAbundanceObservation : public CObservation {
public:
  // Functions
	CAbundanceObservation(CAbundanceObservation *Observation = 0);
	virtual                    ~CAbundanceObservation();
  void                       addProportion(string Group, double Proportion);
  int                        getProportionCount() { return (int)mvProportionMatrix.size(); }
  string                     getProportionKey(int index);
  double                     getProportionValue(string key);
  void                       addCV(string Group, double Value);
  int                        getCVCount() { return (int)mvCVMatrix.size(); }
  string                     getCVKey(int index);
  double                     getCVValue(string key);
  void                       setQ(string value) { sQ = value; }
  string                     getQ() { return sQ; }
  void                       setCVProcessError(double value) { dCVProcessError = value; }
  double                     getCVProcessError() { return dCVProcessError; }
  CObservation*              clone() { return (new CAbundanceObservation(this)); }
  void                       validate();
  void                       build();
  void                       execute();

protected:
  // Variables
  map<string, double>        mvProportionMatrix;
  map<string, double>        mvCVMatrix;
  string                     sQ;
  CQ                         *pQ;
  double                     dSigma;
  double                     dCVProcessError;
};

#endif /*CABUNDANCEOBSERVATION_H_*/
