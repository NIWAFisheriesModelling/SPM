//============================================================================
// Name        : CAbundanceDensityLayer.h
// Author      : S.Rasmussen
// Date        : 16/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CABUNDANCEDENSITYLAYER_H_
#define CABUNDANCEDENSITYLAYER_H_

// Local headers
#include "Base/CNumericLayer.h"

//**********************************************************************
//
//
//**********************************************************************
class CAbundanceDensityLayer : public CNumericLayer {
public:
  // Functions
  CAbundanceDensityLayer(CAbundanceDensityLayer *Layer = 0);
  virtual                     ~CAbundanceDensityLayer();
  CLayer*                    clone() { return (new CAbundanceDensityLayer(this)); }
  double                     getValue(int RowIndex, int ColIndex, int TargetRow, int TargetCol);
  void                       validate();
  void                       build();

protected:
  // Variables
  vector<string>              vCategories;
  vector<string>              vSelectivities;
};

#endif /* CABUNDANCEDENSITYLAYER_H_ */
