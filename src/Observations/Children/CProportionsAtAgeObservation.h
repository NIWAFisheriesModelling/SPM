//============================================================================
// Name        : CProportionsAtAgeObservation.h
// Author      : S.Rasmussen
// Date        : 17/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CPROPORTIONSATAGE_H_
#define CPROPORTIONSATAGE_H_

// Local Headers
#include "../CObservation.h"

//**********************************************************************
//
//
//**********************************************************************
class CProportionsAtAgeObservation : public CObservation {
public:
  // Functions
	CProportionsAtAgeObservation(CProportionsAtAgeObservation *Observation = 0);
	virtual                    ~CProportionsAtAgeObservation();
	void                       addProportion(string Group, double Proportion);
	int                        getProportionCount() { return (int)mvProportionMatrix.size(); }
	string                     getProportionKey(int index);
	int                        getProportionKeyValueCount(string key);
	double                     getProportionValue(string key, int index);
	void                       addN(string key, double value);
  int                        getNCount() { return mN.size(); }
  string                     getNKey(int index);
  double                     getNValue(string key);
	void                       setNProcessError(double value) { dNProcessError = value; }
	double                     getNProcessError() { return dNProcessError; }
  void                       setMinAge(int value) { iMinAge = value; }
  int                        getMinAge() { return iMinAge; }
  void                       setMaxAge(int value) { iMaxAge = value; }
  int                        getMaxAge() { return iMaxAge; }
  void                       setAgePlus(bool value) { bAgePlus = value; }
  bool                       getAgePlus() { return bAgePlus; }
  void                       setRescale(bool value) { bRescale = value; }
  bool                       getRescale() { return bRescale; }
  void                       setR(double value) { dR = value; }
  double                     getR() { return dR; }
  CObservation*              clone() { return (new CProportionsAtAgeObservation(this)); }
	void                       validate();
	void                       build();
	void                       execute();

protected:
  // Variables
  map<string, vector<double> > mvProportionMatrix;
  map<string, double>        mN;
  double                     dNProcessError;
  double                     dR;
  double                     *pAgeResults;
  int                        iMinAge;
  int                        iMaxAge;
  int                        iArraySize;
  bool                       bAgePlus;
  bool                       bRescale;
};

#endif /*CPROPORTIONSATAGE_H_*/
