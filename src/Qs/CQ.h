//============================================================================
// Name        : CQ.h
// Author      : S.Rasmussen
// Date        : 28/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CQ_H_
#define CQ_H_

// Local Headers
#include "../BaseClasses/CBaseExecutableObject.h"

//**********************************************************************
//
//
//**********************************************************************
class CQ : public CBaseExecutableObject {
public:
  // Functions
	CQ(CQ *Q = 0);
	virtual                    ~CQ();
	void                       setType(string value) { sType = value; }
	string                     getType() { return sType; }
	void                       setQ(double value) { dQ = value; }
	double                     getQ() { return dQ; }
	CQ*                        clone() { return (new CQ(this)); }
	void                       build() { };
	void                       execute() { };

protected:
  // Variables
  string                     sType;
  double                     dQ;
};

#endif /*CQ_H_*/
