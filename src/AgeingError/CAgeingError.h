//============================================================================
// Name        : CAgeingError.h
// Author      : S.Rasmussen
// Date        : 2/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CAGEINGERROR_H_
#define CAGEINGERROR_H_

// Local Headers
#include "../BaseClasses/CBaseObject.h"

//**********************************************************************
//
//
//**********************************************************************
class CAgeingError : public CBaseObject {
public:
	CAgeingError();
	virtual                    ~CAgeingError();
	void                       setType(string value) { sType = value; }
	string                     getType() { return sType; }
	void                       setC(double value) { dC = value; }
	double                     getC() { return dC; }

protected:
  // Variables
  string                     sType;
  double                     dC;
};

#endif /*CAGEINGERROR_H_*/
