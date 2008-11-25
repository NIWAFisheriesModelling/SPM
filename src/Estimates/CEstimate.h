//============================================================================
// Name        : CEstimate.h
// Author      : S.Rasmussen
// Date        : 27/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CESTIMATE_H_
#define CESTIMATE_H_

// Local Headers
#include "../BaseClasses/CBaseBuildableObject.h"

// Classes
class CPrior;

//**********************************************************************
//
//
//**********************************************************************
class CEstimate : public CBaseBuildableObject {
public:
	CEstimate(CEstimate *Estimate = 0);
	virtual                    ~CEstimate();
	void                       setParameter(string value) { sParameter = value; }
	string                     getParameter() { return sParameter; }
	void                       setLowerBound(double value) { dLowerBound = value; }
	double                     getLowerBound() { return dLowerBound; }
	void                       setUpperBound(double value) { dUpperBound = value; }
	double                     getUpperBound() { return dUpperBound; }
	void                       setPrior(string value) { sPrior = value; }
	string                     getPrior() { return sPrior; }
	void                       setValue(double value);
	double                     getValue();
	void                       setEnabled(bool value) { bEnabled = value; }
  bool                       getEnabled() { return bEnabled; }
  void                       addSame(string value);
  int                        getSameCount() { return (int)vSameList.size(); }
  string                     getSame(int index);
  void                       addValue(double value);
  int                        getValueCount() { return (int)vValueList.size(); }
  void                       loadValue(int index);
  double                     getPriorScore();
  CEstimate*                 clone() { return (new CEstimate(this)); }
  void                       validate();
	void                       build();

protected:
  // Variables
  string                     sParameter;
  double                     dLowerBound;
  double                     dUpperBound;
  string                     sPrior;
  CPrior                     *pPrior;
  double                     *pTarget;
  bool                       bEnabled;
  vector<string>             vSameList;
  vector<double*>            vSameIndex;
  vector<double>             vValueList;
};

#endif /*CESTIMATE_H_*/
