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
#include "../BaseClasses/CBaseBuildableObject.h"

//**********************************************************************
//
//
//**********************************************************************
class CLayer : public CBaseBuildableObject {
public:
	CLayer(CLayer *Layer = 0);
  virtual                   ~CLayer();
  virtual CLayer*           clone() = 0;
  int                       getWidth() { return iWidth; }
  int                       getHeight() { return iHeight; }
  virtual void              validate();
  virtual void              build() = 0;

protected:
  int                       iWidth;
  int                       iHeight;
};

#endif /*CLAYER_H_*/
