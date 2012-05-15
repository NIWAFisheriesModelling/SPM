//============================================================================
// Name        : CMigrationMovementProcess.h
// Author      : S.Rasmussen
// Date        : 4/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CMIGRATIONMOVEMENTPROCESS_H_
#define CMIGRATIONMOVEMENTPROCESS_H_

// Local Headers
#include "Base/CMovementProcess.h"

//**********************************************************************
//
//
//**********************************************************************
class CMigrationMovementProcess : public CMovementProcess {
public:
  CMigrationMovementProcess();
  virtual                    ~CMigrationMovementProcess();
  CProcess*                  clone() { return (new CMigrationMovementProcess(*this)); }
  int                        getCategoryCount() { return (int)vCategoryNames.size(); }
  int                        getSelectivityCount() { return (int)vSelectivityNames.size(); }
  void                       validate();
  void                       build();
  void                       execute();

protected:
  // Variables
  CNumericLayer                 *pSourceLayer;
  CNumericLayer                 *pSinkLayer;
  vector<string>                vCategoryNames;
  vector<int>                   vCategories;
  vector<string>                vSelectivityNames;
  vector<CSelectivity*>         vSelectivities;
  string                        sSourceLayer;
  string                        sSinkLayer;
};

#endif /*CMIGRATIONMOVEMENTPROCESS_H_*/

