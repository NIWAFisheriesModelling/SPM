//============================================================================
// Name        : CDirectedMovementProcess.h
// Author      : S.Rasmussen
// Date        : 4/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CDIRECTEDMOVEMENTPROCESS_H_
#define CDIRECTEDMOVEMENTPROCESS_H_

// Local Headers
#include "Base/CMovementProcess.h"

// Classes
class CPreferenceFunction;

//**********************************************************************
//
//
//**********************************************************************
class CDirectedMovementProcess : public CMovementProcess {
public:
  CDirectedMovementProcess();
  virtual                    ~CDirectedMovementProcess();
  void                       addDirectedProcess(string value);
  int                        getDirectedProcessCount() { return (int)vDirectedProcessList.size(); }
  string                     getDirectedProcess(int index);
  CProcess*                  clone() { return (new CDirectedMovementProcess(*this)); }
  void                       validate();
  void                       build();
  void                       execute();

protected:
  // Variables
  vector<string>             vDirectedProcessList;
  vector<CPreferenceFunction*>  vDirectedProcessIndex;
  double                     dRunningTotal;
};

#endif /*CDIRECTEDMOVEMENTPROCESS_H_*/
