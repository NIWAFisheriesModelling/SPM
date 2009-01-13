//============================================================================
// Name        : CConstantRecruitmentProcess.h
// Author      : S.Rasmussen
// Date        : 13/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CCONSTANTRECRUITMENTPROCESS_H_
#define CCONSTANTRECRUITMENTPROCESS_H_

// Local Headers
#include "../CProcess.h"

//**********************************************************************
//
//
//**********************************************************************
class CConstantRecruitmentProcess : public CProcess {
public:
  // Functions
	CConstantRecruitmentProcess(CConstantRecruitmentProcess *Process = 0);
	virtual                    ~CConstantRecruitmentProcess();
	void                       addProportion(double value);
	int                        getProportionCount() { return vProportionList.size(); }
	double                     getProportion(int index);
	void                       addAges(int value);
	int                        getAgesCount() { return vAgesList.size(); }
	int                        getAges(int index);
	CProcess*                  clone() { return (new CConstantRecruitmentProcess(this)); }
	void                       validate();
	void                       build();
	void                       execute();

protected:
  // Variables
  vector<double>             vProportionList;
  double                     dR0;
  vector<int>                vAgesList;
  vector<int>                vAgesIndex;
};

#endif /*CCONSTANTRECRUITMENTPROCESS_H_*/
