//============================================================================
// Name        : CRecruitmentProcess.h
// Author      : S.Rasmussen
// Date        : 13/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CRECRUITMENTPROCESS_H_
#define CRECRUITMENTPROCESS_H_

// Local Headers
#include "../CProcess.h"

// Enum
typedef enum EMethod {
  METHOD_UNKNOWN,
  METHOD_UNIFORM
};

//**********************************************************************
//
//
//**********************************************************************
class CRecruitmentProcess : public CProcess {
public:
  // Functions
	CRecruitmentProcess(CRecruitmentProcess *Process = 0);
	virtual                    ~CRecruitmentProcess();
	void                       addProportion(double value);
	int                        getProportionCount() { return vProportionList.size(); }
	double                     getProportion(int index);
	void                       setR0(double value) { dR0 = value; }
	double                     getR0() { return dR0; }
	void                       setSteepness(double value) { dSteepness = value; }
	double                     getSteepness() { return dSteepness; }
	void                       setSigmaR(double value) { dSigmaR = value; }
	double                     getSigmaR() { return dSigmaR; }
	void                       setRho(double value) { dRho = value; }
	double                     getRho() { return dRho; }
	void                       addAges(int value);
	int                        getAgesCount() { return vAgesList.size(); }
	int                        getAges(int index);
	void                       setMethod(string value) { sMethod = value; }
	string                     getMethod() { return sMethod; }
	CProcess*                  clone() { return (new CRecruitmentProcess(this)); }
	void                       validate();
	void                       build();
	void                       execute();

protected:
  // Variables
  vector<double>             vProportionList;
  double                     dR0;
  double                     dSteepness;
  double                     dSigmaR;
  double                     dRho;
  vector<int>                vAgesList;
  vector<int>                vAgesIndex;
  string                     sMethod;
  EMethod                    eMethod;

};

#endif /*CRECRUITMENTPROCESS_H_*/
