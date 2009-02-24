//============================================================================
// Name        : CDoubleLayer.h
// Author      : S.Rasmussen
// Date        : 14/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CDOUBLELAYER_H_
#define CDOUBLELAYER_H_

// Local Headers
#include "Base/CNumericLayer.h"

//**********************************************************************
//
//
//**********************************************************************
class CDoubleLayer : public CNumericLayer  {
public:
  // Functions
  CDoubleLayer();
  virtual                     ~CDoubleLayer();
  CLayer*                     clone() { return (new CDoubleLayer(*this)); }
  double                      getValue(int RowIndex, int ColIndex, int TargetRow, int TargetCol);
  void                        setValue(int Row, int Col, double Value);
  void                        validate();
  void                        build();

protected:
  // Variables
  double                      dRescale;
};

#endif /*CNUMERICLAYER_H_*/
