//============================================================================
// Name        : CDerivedQuantityByCellLayer.h
// Author      : A.Dunn
// Date        : 02/09/2013
// Copyright   : Copyright NIWA Science ©2013 - www.niwa.co.nz
//============================================================================
#ifndef CDERIVEDQUANTITYBYCELLLAYER_H_
#define CDERIVEDQUANTITYBYCELLLAYER_H_

// Local Headers
#include "Base/CNumericLayer.h"
#include "../../DerivedQuantitiesByCell/CDerivedQuantityByCell.h"
#include "../../DerivedQuantitiesByCell/CDerivedQuantityByCellManager.h"

// Classes
class CWorld;
class CSelectivity;
class CDerivedQuantityByCell;

//**********************************************************************
//
//
//**********************************************************************
class CDerivedQuantityByCellLayer : public CNumericLayer {
public:
  // Functions
  CDerivedQuantityByCellLayer();
  virtual                    ~CDerivedQuantityByCellLayer();
  CLayer*                    clone() { return (new CDerivedQuantityByCellLayer(*this)); }
  void                       addCategory(string value);
  int                        getCategoryCount() { return (int)vCategoryNames.size(); }
  void                       addSelectivity(string value);
  int                        getSelectivityCount() { return (int)vSelectivityNames.size(); }
  double                     getValue(int RowIndex, int ColIndex, int TargetRow, int TargetCol);
  void                       validate();
  void                       build();

protected:
  // Variables
  CWorld                     *pWorld;
  vector<string>             vCategoryNames;
  vector<int>                vCategories;
  vector<string>             vSelectivityNames;
  vector<CSelectivity*>      vSelectivities;
  string                     sDerivedQuantityByCell;
  int                        iOffset;
  CDerivedQuantityByCell     *pDerivedQuantityByCell;
};

#endif /*CDERIVEDQUANTITYBYCELLLAYER_H_*/
