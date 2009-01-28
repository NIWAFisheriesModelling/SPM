//============================================================================
// Name        : CProportionsByCategoryObservation.h
// Author      : S.Rasmussen
// Date        : 1/05/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CPROPORTIONSBYCATEGORYOBSERVATION_H_
#define CPROPORTIONSBYCATEGORYOBSERVATION_H_

// Local Headers
#include "../CObservation.h"

//**********************************************************************
//
//
//**********************************************************************
class CProportionsByCategoryObservation : public CObservation {
public:
	CProportionsByCategoryObservation();
	virtual                    ~CProportionsByCategoryObservation();
	int                        getProportionCount() { return (int)mvProportionMatrix.size(); }
	string                     getProportionKey(int index);
	int                        getProportionKeyCount(string key);
	double                     getProportionValue(string key, int index);
  int                        getNCount() { return mvN.size(); }
  string                     getNKey(int index);
  int                        getNKeyValueCount(string key);
  double                     getNValue(string key, int index);
  void                       setNProcessError(double value) { dNProcessError = value; }
  double                     getNProcessError() { return dNProcessError; }
  int                        getPopulationCategoryCount() { return vPopulationCategoryList.size(); }
  string                     getPopulationCategory(int index);
  int                        getMinAge() { return iMinAge; }
  int                        getMaxAge() { return iMaxAge; }
  bool                       getAgePlus() { return bAgePlus; }
  double                     getR() { return dR; }
  int                        getPopulationSelectivityCount() { return vPopulationSelectivityList.size(); }
  string                     getPopulationSelectivity(int index);
  void                       validate();
  void                       build();
  void                       execute();

protected:
  // Variables
  map<string, vector<double> > mvProportionMatrix;
  map<string, vector<double> >  mvN;
  vector<string>             vPopulationCategoryList;
  vector<int>                vPopulationCategoryIndex;
  double                     dR;
  double                     dNProcessError;
  double                     *pAgeResults;
  double                     *pCombinedAgeResults;
  int                        iMinAge;
  int                        iMaxAge;
  int                        iArraySize;
  bool                       bAgePlus;
  vector<string>             vPopulationSelectivityList;
  vector<CSelectivity*>      vPopulationSelectivityIndex;
};

#endif /*CPROPORTIONSBYCATEGORYOBSERVATION_H_*/
