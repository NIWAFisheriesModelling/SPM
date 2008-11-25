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
#include "../BaseClasses/CBaseExecutableObject.h"

// Classes
class CPenalty;
class CNumericLayer;
class CSelectivity;

//**********************************************************************
//
//
//**********************************************************************
class CProcess : public CBaseExecutableObject {
public:
  // Functions
	CProcess(CProcess *Process = 0);
	virtual                    ~CProcess();
  void                       addCategory(string value);
  int                        getCategoryCount() { return vCategoryList.size(); }
  string                     getCategory(int index);
  void                       addSelectivity(string value);
  int                        getSelectivityCount() { return vSelectivityList.size(); }
  string                     getSelectivity(int index);
  void                       addLayerCategory(string value);
  int                        getLayerCategoryCount() { return vLayerCategoryList.size(); }
  string                     getLayerCategory(int index);
  void                       setDependsOnLayer(bool value) { bDependsOnLayer = value; }
  bool                       getDependsOnLayer() { return bDependsOnLayer; }
  void                       setLayerName(string value) { sLayerName = value; }
  string                     getLayerName() { return sLayerName; }
  void                       setLayerMin(double value) { dLayerMin = value; }
  double                     getLayerMin() { return dLayerMin; }
  void                       setLayerMax(double value) { dLayerMax = value; }
  double                     getLayerMax() { return dLayerMax; }
  void                       setPenalty(string value) { sPenalty = value; }
  string                     getPenalty() { return sPenalty; }
  bool                       checkUsableSquare(CWorldSquare *Square, int iX, int iY);
  bool                       checkUsableBaseSquare(int RowIndex, int ColIndex);
  virtual CProcess*          clone() = 0;
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
  string                     sPenalty;
  CPenalty                   *pPenalty;
};

#endif /*CPROCESS_H_*/
