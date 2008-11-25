//============================================================================
// Name        : CAbundanceLayer.h
// Author      : S.Rasmussen
// Date        : 28/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CABUNDANCELAYER_H_
#define CABUNDANCELAYER_H_

// Local Headers
#include "../CNumericLayer.h"

// Classes
class CWorld;
class CSelectivity;

//**********************************************************************
//
//
//**********************************************************************
class CAbundanceLayer : public CNumericLayer {
public:
  // Functions
	CAbundanceLayer(CAbundanceLayer *Layer = 0);
	virtual                    ~CAbundanceLayer();
	void                       addCategory(string value);
	int                        getCategoryCount() { return (int)vCategoryList.size(); }
	void                       addSelectivity(string value);
	int                        getSelectivityCount() { return (int)vSelectivityList.size(); }
  double                     getValue(int RowIndex, int ColIndex, int TargetRow, int TargetCol);
  CLayer*                    clone() { return (new CAbundanceLayer(this)); }
  void                       validate();
  void                       build();

protected:
  // Variables
  CWorld                     *pWorld;
  vector<string>             vCategoryList;
  vector<int>                vCategoryIndex;
  vector<string>             vSelectivityList;
  vector<CSelectivity*>      vSelectivityIndex;
};

#endif /*CABUNDANCELAYER_H_*/
