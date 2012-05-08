//============================================================================
// Name        : CParamParser.h
// Author      : S.Rasmussen
// Date        : 27/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CPARAMPARSER_H_
#define CPARAMPARSER_H_

// Local Headers
#include "../BaseClasses/CBaseObject.h"

//**********************************************************************
//
//
//**********************************************************************
class CParamParser : public CBaseObject {
public:
  // Functions
  CParamParser();
  virtual                    ~CParamParser();
  double*                    parseCommand(string Command);

protected:
  // Functions
  void                      parseAbsoluteCommand();
  void                      convertAbsoluteCommand();

  // Variables
  string                     sCommand;
  double                     *pRet;
};

#endif /*CPARAMPARSER_H_*/
