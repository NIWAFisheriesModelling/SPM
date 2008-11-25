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

//**********************************************************************
//
//
//**********************************************************************
class CNaturalMortalityProcess : public CProcess {
public:
  // Functions
	CNaturalMortalityProcess(CNaturalMortalityProcess *Process = 0);
	virtual                    ~CNaturalMortalityProcess();
	void                       setM(double value) { dM = value; }
	double                     getM() { return dM; }
	CProcess*                  clone() { return (new CNaturalMortalityProcess(this)); }
	void                       validate();
	void                       build();
	void                       rebuild();
	void                       execute();

protected:
  // Variables
  double                     dM;
  CWorldSquare               **pGrid;
};

#endif /*CNATURALMORTALITYPROCESS_H_*/
