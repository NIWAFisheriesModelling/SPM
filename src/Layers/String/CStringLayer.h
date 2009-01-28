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
#include "../CLayer.h"

//**********************************************************************
//
//
//**********************************************************************
class CStringLayer : public CLayer {
public:
  // Functions
	CStringLayer();
	virtual                    ~CStringLayer();
	string                     getValue(int RowIndex, int ColIndex);
	void                       validate();
	void                       build() { };

protected:
  // Variables
  string                     **pGrid;
};

#endif /*CSTRINGLAYER_H_*/
