//============================================================================
// Name        : CStringLayer.h
// Author      : S.Rasmussen
// Date        : 14/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CSTRINGLAYER_H_
#define CSTRINGLAYER_H_

// Local Headers
#include "CLayer.h"

//**********************************************************************
//
//
//**********************************************************************
class CStringLayer : public CLayer {
public:
  // Functions
	CStringLayer(CStringLayer *Layer = 0);
	virtual                    ~CStringLayer();
	void                       setValue(int Row, int Col, string Value);
	string                     getValue(int RowIndex, int ColIndex);
	CLayer*                    clone() { return (new CStringLayer(this)); }
	void                       validate();
	void                       build() { };

protected:
  // Variables
  string                     **pGrid;
};

#endif /*CSTRINGLAYER_H_*/
