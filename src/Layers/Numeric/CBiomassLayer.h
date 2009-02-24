//============================================================================
// Name        : CBiomassLayer.h
// Author      : S.Rasmussen
// Date        : 16/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CBIOMASSLAYER_H_
#define CBIOMASSLAYER_H_

// Local headers
#include "Base/CNumericLayer.h"

//**********************************************************************
//
//
//**********************************************************************
class CBiomassLayer : public CNumericLayer {
public:
  CBiomassLayer();
  virtual                     ~CBiomassLayer();
  CLayer*                    clone() { return (new CBiomassLayer(*this)); }
  double                     getValue(int RowIndex, int ColIndex, int TargetRow, int TargetCol);
  void                       validate();
  void                       build();

protected:
  // Variables
  vector<string>              vCategories;
  vector<string>              vSelectivities;
  vector<string>              vSizeWeights;
};

#endif /* CBIOMASSLAYER_H_ */
