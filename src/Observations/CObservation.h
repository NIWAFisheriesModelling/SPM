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
#include "../BaseClasses/CBaseExecutableObject.h"

// Classes
class CStringLayer;
class CSelectivity;

//**********************************************************************
//
//
//**********************************************************************
class CObservation : public CBaseExecutableObject {
public:
  // Functions
	CObservation(CObservation *Observation = 0);
	virtual                    ~CObservation();
  void                       setLabel(string value) { sLabel = value; }
  string                     getLabel() { return sLabel; }
  void                       setYear(int value) { iYear = value; }
  int                        getYear() { return iYear; }
  void                       setTimeStep(int value) { iTimeStep = value; }
  int                        getTimeStep() { return iTimeStep; }
  void                       setLayer(string value) { sLayer = value; }
  string                     getLayer() { return sLayer; }
  void                       addCategory(string value);
  int                        getCategoryCount() { return vCategoryList.size(); }
  string                     getCategory(int index);
  void                       addSelectivity(string value);
  int                        getSelectivityCount() { return vSelectivityList.size(); }
  string                     getSelectivity(int index);
  void                       setDist(string value) { sDist = value; }
  string                     getDist() { return sDist; }
  double                     getScore() { return dScore; }
  virtual void               addProportion(string Group, double Proportion) = 0;
  virtual CObservation*      clone() = 0;
  virtual void               validate();
	virtual void               build();
	virtual void               execute() = 0;

protected:
  // Variables
  double                     dScore;
  string                     sLabel;
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
