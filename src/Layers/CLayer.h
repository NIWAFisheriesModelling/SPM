//============================================================================
// Name        : CLayer.h
// Author      : S.Rasmussen
// Date        : 11/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CLAYER_H_
#define CLAYER_H_

// Local Includes
#include "../BaseClasses/CBaseBuild.h"

//**********************************************************************
//
//
//**********************************************************************
class CLayer : public CBaseBuild {
public:
  CLayer();
  virtual                   ~CLayer();
  virtual CLayer*           clone() = 0;
  int                       getWidth() { return iWidth; }
  int                       getHeight() { return iHeight; }
  double                    getCellLength() { return dCellLength; }
  virtual void              validate();

protected:
  double                    dCellLength;
  int                       iWidth;
  int                       iHeight;
};

#endif /*CLAYER_H_*/
