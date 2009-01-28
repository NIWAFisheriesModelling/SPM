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
  int                        getCategoryCount() { return vCategoryList.size(); }
  string                     getCategory(int index);
  int                        getSelectivityCount() { return vSelectivityList.size(); }
  string                     getSelectivity(int index);
  string                     getDist() { return sDist; }
  double                     getScore() { return dScore; }
  virtual void               validate() { CBaseExecute::validate(); }
	virtual void               build();
	virtual void               execute() = 0;

protected:
  // Variables
  double                     dScore;
  int                        iYear;
  int                        iTimeStep;
  string                     sLayer;
  CStringLayer               *pLayer;
  vector<string>             vCategoryList;
  vector<string>             vSelectivityList;
  vector<int>                vCategoryIndex;
  vector<CSelectivity*>      vSelectivityIndex;
  string                     sDist;
};

#endif /*COBSERVATION_H_*/
