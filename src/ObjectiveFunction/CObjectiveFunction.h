//============================================================================
// Name        : CObjectiveFunction.h
// Author      : S.Rasmussen
// Date        : 24/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef COBJECTIVEFUNCTION_H_
#define COBJECTIVEFUNCTION_H_

// Local Headers
#include "../BaseClasses/CBaseExecutableObject.h"

// Structs
struct SScore {
  string Label;
  double Score;
};

//**********************************************************************
//
//
//**********************************************************************
class CObjectiveFunction : public CBaseExecutableObject {
public:
  static CObjectiveFunction* Instance();
  static void                Destroy();

  // Functions
	double                     getScore() { return dScore; }
	int                        getScoreListCount() { return (int)vScoreList.size(); }
	SScore*                    getScore(int Index);
  void                       build();
  void                       execute();
  virtual                    ~CObjectiveFunction();

protected:
  // Functions
  CObjectiveFunction();
  void                       addScore(string Label, double Value);

  // Variables
  double                     dScore;
  vector<SScore>             vScoreList;

private:
  static boost::thread_specific_ptr<CObjectiveFunction> clInstance;
};

#endif /*COBJECTIVEFUNCTION_H_*/
