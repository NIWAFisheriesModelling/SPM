//============================================================================
// Name        : CBiomassDensityLayer.h
// Author      : S.Rasmussen
// Date        : 16/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CBIOMASSDENSITYLAYER_H_
#define CBIOMASSDENSITYLAYER_H_

// Local headers
#include "Base/CNumericLayer.h"

//**********************************************************************
//
//
//**********************************************************************
class CBiomassDensityLayer : public CNumericLayer {
public:
  CBiomassDensityLayer(CBiomassDensityLayer *Layer = 0);
  virtual                     ~CBiomassDensityLayer();
  CLayer*                    clone() { return (new CBiomassDensityLayer(this)); }
  double                     getValue(int RowIndex, int ColIndex, int TargetRow, int TargetCol);
  void                       validate();
  void                       build();

protected:
  // Variables
  vector<string>              vCategories;
  vector<string>              vSelectivities;
  vector<string>              vSizeWeights;
};

#endif /* CBIOMASSDENSITYLAYER_H_ */
