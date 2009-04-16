//============================================================================
// Name        : CProportionsAtAgeObservation.h
// Author      : S.Rasmussen
// Date        : 17/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CPROPORTIONSATAGE_H_
#define CPROPORTIONSATAGE_H_

// Local Headers
#include "../CObservation.h"

//**********************************************************************
//
//
//**********************************************************************
class CProportionsAtAgeObservation : public CObservation {
public:
  // Functions
  CProportionsAtAgeObservation();
  virtual                    ~CProportionsAtAgeObservation();
//  int                        getProportionCount() { return (int)mvProportionMatrix.size(); }
//  string                     getProportionKey(int index);
//  int                        getProportionKeyValueCount(string key);
//  double                     getProportionValue(string key, int index);
//  int                        getMinAge() { return iMinAge; }
//  int                        getMaxAge() { return iMaxAge; }
//  bool                       getAgePlus() { return bAgePlus; }
//  bool                       getRescale() { return bRescale; }
  void                       validate();
  void                       build();
  void                       execute();

protected:
  // Variables
  map<string, vector<double> > mvProportionMatrix;
  map<string, double>        mErrorValue;
  double                     dDelta;
  double                     *pAgeResults;
  int                        iMinAge;
  int                        iMaxAge;
  int                        iArraySize;
  bool                       bAgePlus;
  bool                       bRescale;
  double                     dTolerance;
  double                     dProcessError;
};

#endif /*CPROPORTIONSATAGE_H_*/
