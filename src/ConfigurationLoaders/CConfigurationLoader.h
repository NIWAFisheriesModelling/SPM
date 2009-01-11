//============================================================================
// Name        : CConfigurationLoader.h
// Author      : S.Rasmussen
// Date        : 6/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CCONFIGURATIONLOADER_H_
#define CCONFIGURATIONLOADER_H_

// Global Headers
#include <string>
#include <vector>

// Namespaces
using std::string;
using std::vector;

//**********************************************************************
//
//
//**********************************************************************
class CConfigurationLoader {
public:
  CConfigurationLoader();
  virtual                     ~CConfigurationLoader();
  void                        loadConfigFile();

protected:
  // Functions
  void                        processSection();
  void                        loadConfigIntoCache();

  // Variables
  vector<string>              vLines;
  vector<string>              vCurrentSection;
  string                      sFileName;
  string                      sDirectory;
};

#endif /* CCONFIGURATIONLOADER_H_ */
