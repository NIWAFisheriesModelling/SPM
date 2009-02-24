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
#include "Base/CNumericLayer.h"

//**********************************************************************
//
//
//**********************************************************************
class CDistanceLayer : public CNumericLayer {
public:
  // Functions
	CDistanceLayer();
	virtual                    ~CDistanceLayer();
	CLayer*                    clone() { return (new CDistanceLayer(*this)); }
  double                     getSmallestValue() { throw string("getSmallestValue Not Done"); }
  double                     getLargestValue() { throw string("getLargestValue Not Done"); }
  double                     getValue(int RowIndex, int ColIndex, int TargetRow, int TargetCol);
  void                       build();

};

#endif /*CDISTANCELAYER_H_*/
