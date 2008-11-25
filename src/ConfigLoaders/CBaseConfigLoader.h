//============================================================================
// Name        : CBaseConfigLoader.h
// Author      : S.Rasmussen
// Date        : 13/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CBASECONFIGLOADER_H_
#define CBASECONFIGLOADER_H_

// Local Header
#include "../CWorld.h"
#include "../CConfiguration.h"
#include "../CLayerManager.h"
#include "../CRuntimeController.h"

// Defines
#define MIN_PARAMS 0
#define MAX_PARAMS 99999

//**********************************************************************
//
//
//**********************************************************************
class CBaseConfigLoader {
public:
	CBaseConfigLoader();
	virtual void              processConfigFile() = 0;
	void                      setFileName(string value) { sFileName = value; }
	string                    getFileName() { return sFileName; }
	void                      setDirectory(string value) { sDirectory = value; }
	string                    getDirectory() { return sDirectory; }
  virtual                   ~CBaseConfigLoader();

protected:
  // Functions
  void                      loadConfigFile();
  void                      loadFileLines(string FileName);
  void                      populateParameters(string find = " ");
  bool                      checkLine(string Match, int MinParams = 1, int MaxParams = 1);
  string                    getWildCardMatch(string Match);
  double                    getDoubleValue(int ParameterNumber, bool AllowZero = false);
  int                       getIntValue(int ParameterNumber, bool AllowZero = false);
  bool                      getBoolValue(int ParameterNumber);
  string                    upperToLower(string Input);
  string                    getLabel();
  bool                      newSection();

  // Variables
  CWorld                    *pWorld;
  CConfiguration            *pConfig;
  CRuntimeController        *pRuntimeController;
  CLayerManager             *pLayerManager;
  string                    sFileName;
  string                    sDirectory;
  vector<string>            vConfigList;
  vector<string>::iterator  vConfigPtr;
  vector<string>            vParameterList;

};

#endif /*CBASECONFIGLOADER_H_*/
