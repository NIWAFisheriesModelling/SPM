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
	CProportionsAtAgeObservation();
	virtual                    ~CProportionsAtAgeObservation();
	int                        getProportionCount() { return (int)mvProportionMatrix.size(); }
	string                     getProportionKey(int index);
	int                        getProportionKeyValueCount(string key);
	double                     getProportionValue(string key, int index);
  int                        getNCount() { return mN.size(); }
  string                     getNKey(int index);
  double                     getNValue(string key);
	double                     getNProcessError() { return dNProcessError; }
  int                        getMinAge() { return iMinAge; }
  int                        getMaxAge() { return iMaxAge; }
  bool                       getAgePlus() { return bAgePlus; }
  bool                       getRescale() { return bRescale; }
  double                     getR() { return dR; }
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
