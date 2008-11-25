//============================================================================
// Name        : CPenalty.h
// Author      : S.Rasmussen
// Date        : 16/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CPENALTY_H_
#define CPENALTY_H_

// Local
#include "../BaseClasses/CBaseBuildableObject.h"

//**********************************************************************
//
//
//**********************************************************************
class CPenalty : public CBaseBuildableObject {
public:
  // Functions
	CPenalty(CPenalty *Penalty = 0);
	virtual                    ~CPenalty();
	void                       setLogScale(bool value){ bLogScale = value; }
	bool                       getLogScale() { return bLogScale; }
	void                       setMultiplier(double value) { dMultiplier = value; }
	double                     getMultiplier() { return dMultiplier; }
	CPenalty*                  clone() { return (new CPenalty(this)); }
	void                       validate();
	void                       build();
	void                       execute(string Label, double Value);

protected:
  // Variables
  bool                       bLogScale;
  double                     dMultiplier;
};

#endif /*CPENALTY_H_*/
