//============================================================================
// Name        : CBiomassLayer.h
// Author      : S.Rasmussen
// Date        : 28/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2009-02-25 11:35:59 +1300 (Wed, 25 Feb 2009) $
//============================================================================
#ifndef CBIOMASSLAYER_H_
#define CBIOMASSLAYER_H_

// Local Headers
#include "Base/CNumericLayer.h"

// Classes
class CWorld;
class CSelectivity;

//**********************************************************************
//
//
//**********************************************************************
class CBiomassLayer : public CNumericLayer {
public:
  // Functions
  CBiomassLayer();
  virtual                    ~CBiomassLayer();
  CLayer*                    clone() { return (new CBiomassLayer(*this)); }
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
};

#endif /*CBIOMASSLAYER_H_*/
