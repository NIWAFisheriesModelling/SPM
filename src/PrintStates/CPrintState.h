//============================================================================
// Name        : CPrintState.h
// Author      : S.Rasmussen
// Date        : 14/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CPRINTSTATE_H_
#define CPRINTSTATE_H_

// Global Headers
#include <string>
#include <iostream>
#include <fstream>

// Local headers
#include "../BaseClasses/CBaseExecute.h"

// Namespace
using namespace std;

// Enums
typedef enum EPrintStateType {
  UNKNOWN_TYPE,
  INITIAL,
  CURRENT,
  FINAL,
  OBJECTIVE,
  ESTIMATE,
  ESTIMATE_VALUE
};

//**********************************************************************
//
//
//**********************************************************************
class CPrintState : public CBaseExecute {
public:
  // Functions
	CPrintState();
	virtual                    ~CPrintState();

	void                       setFileName(string value) { sFileName = value; }
	string                     getFileName() { return sFileName; }
  void                       setState(EState value) { eState = value; }
  EState                     getState() { return eState; }
  void                       setOverwrite(bool value) { bOverwrite = value; }
  bool                       getOverwrite() { return bOverwrite; }
  void                       openStream();
  void                       closeStream();
	virtual void               validate();
	virtual void               build();
	virtual void               execute() = 0;
	void                       execute_end();

protected:
  // Variables
  string                     sFileName;
  string                     sFullFileName;
  bool                       bWriteToFile;
  bool                       bOverwrite;
  streambuf*                 sCoutBackup;
  ofstream                   fFile;
  EState                     eState;
};

#endif /*CPRINTSTATE_H_*/
