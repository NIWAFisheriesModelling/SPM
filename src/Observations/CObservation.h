//============================================================================
// Name        : CObservation.h
// Author      : S.Rasmussen
// Date        : 19/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef COBSERVATION_H_
#define COBSERVATION_H_

// Local Headers
#include "../BaseClasses/CBaseExecute.h"

// Classes
class CStringLayer;
class CSelectivity;

//**********************************************************************
//
//
//**********************************************************************
class CObservation : public CBaseExecute {
public:
  // Functions
	CObservation();
	virtual                    ~CObservation();
  int                        getYear() { return iYear; }
  int                        getTimeStep() { return iTimeStep; }
  string                     getLayer() { return sLayer; }
  string                     getCategory(int index);
  string                     getSelectivity(int index);
  double                     getScore() { return dScore; }
  virtual void               validate();
	virtual void               build();
	virtual void               execute() = 0;

protected:
  // Variables
  double                     dScore;
  int                        iYear;
  string                     sTimeStep;
  int                        iTimeStep;
  string                     sLayer;
  CStringLayer               *pLayer;
  vector<string>             vCategoryNames;
  vector<int>                vCategories;
  vector<string>             vSelectivityNames;
  vector<CSelectivity*>      vSelectivities;
  string                     sLikelihood;
};

#endif /*COBSERVATION_H_*/
