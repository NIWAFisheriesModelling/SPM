//============================================================================
// Name        : CCatchability.h
// Author      : S.Rasmussen
// Date        : 28/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CCATCHABILITY_H_
#define CCATCHABILITY_H_

// Local Headers
#include "../BaseClasses/CBaseExecutableObject.h"

//**********************************************************************
//
//
//**********************************************************************
class CCatchability : public CBaseExecutableObject {
public:
  // Functions
	CCatchability(CCatchability *Catchability = 0);
	virtual                    ~CCatchability();
	void                       setType(string value) { sType = value; }
	string                     getType() { return sType; }
	void                       setQ(double value) { dQ = value; }
	double                     getQ() { return dQ; }
	CCatchability*                        clone() { return (new CCatchability(this)); }
	void                       build() { };
	void                       execute() { };

protected:
  // Variables
  string                     sType;
  double                     dQ;
};

#endif /*CCATCHABILITY_H_*/
