//============================================================================
// Name        : CDistanceLayer.h
// Author      : S.Rasmussen
// Date        : 28/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CDISTANCELAYER_H_
#define CDISTANCELAYER_H_

// Local Headers
#include "../CNumericLayer.h"

//**********************************************************************
//
//
//**********************************************************************
class CDistanceLayer : public CNumericLayer {
public:
  // Functions
	CDistanceLayer(CDistanceLayer *Layer = 0);
	virtual                    ~CDistanceLayer();
  double                     getValue(int RowIndex, int ColIndex, int TargetRow, int TargetCol);
  CLayer*                    clone() { return (new CDistanceLayer(this)); }
  void                       build();

};

#endif /*CDISTANCELAYER_H_*/
