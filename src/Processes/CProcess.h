//============================================================================
// Name        : CProcess.h
// Author      : S.Rasmussen
// Date        : 13/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CPROCESS_H_
#define CPROCESS_H_

// Local Headers
#include "../BaseClasses/CBaseExecute.h"

// Classes
class CNumericLayer;
class CSelectivity;

//**********************************************************************
//
//
//**********************************************************************
class CProcess : public CBaseExecute {
public:
  // Functions
	CProcess();
	virtual                    ~CProcess();
  int                        getCategoryCount() { return vCategoryList.size(); }
  string                     getCategory(int index);
  int                        getSelectivityCount() { return vSelectivityList.size(); }
  string                     getSelectivity(int index);
//  int                        getLayerCategoryCount() { return vLayerCategoryList.size(); }
//  string                     getLayerCategory(int index);
//  bool                       checkUsableSquare(CWorldSquare *Square, int iX, int iY);
//  bool                       checkUsableBaseSquare(int RowIndex, int ColIndex);
  virtual void               validate();
  virtual void               build();
  virtual void               execute();

protected:
  // Variables
  vector<string>             vCategoryList;
  vector<int>                vCategoryIndex;
  vector<string>             vSelectivityList;
  vector<CSelectivity*>      vSelectivityIndex;
  vector<string>             vLayerCategoryList;
  bool                       bDependsOnLayer;
  string                     sLayerName;
  double                     dLayerMin;
  double                     dLayerMax;
  int                        iNumberOfValidLayerSpots;
  CNumericLayer              *pLayer;
  CWorldSquare               *pDiff;
  int                        iBaseColCount;
  double                     dCurrent;
  double                     dSelectivityResult;
};

#endif /*CPROCESS_H_*/
