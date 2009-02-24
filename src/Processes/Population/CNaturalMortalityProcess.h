//============================================================================
// Name        : CNaturalMortalityProcess.h
// Author      : S.Rasmussen
// Date        : 13/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CNATURALMORTALITYPROCESS_H_
#define CNATURALMORTALITYPROCESS_H_

// Local Headers
#include "../CProcess.h"

// Forward-Dec
class CNumericLayer;

//**********************************************************************
//
//
//**********************************************************************
class CNaturalMortalityProcess : public CProcess {
public:
  // Functions
	CNaturalMortalityProcess();
	virtual                    ~CNaturalMortalityProcess();
	CProcess*                  clone() { return new CNaturalMortalityProcess(*this); }
	void                       validate();
	void                       build();
	void                       rebuild();
	void                       execute();

protected:
  // Variables
  double                     dM;
  CWorldSquare               **pGrid;
  CNumericLayer              *pLayer;
  string                     sLayer;
};

#endif /*CNATURALMORTALITYPROCESS_H_*/
