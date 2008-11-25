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
  void                      setLabel(string value) { sLabel = value; }
  string                    getLabel() { return sLabel; }
  void                      setType(string value) { sType = value; }
  string                    getType() { return sType; }
  void                      setWidth(int value) { iWidth = value; }
  int                       getWidth() { return iWidth; }
  void                      setHeight(int value) { iHeight = value; }
  int                       getHeight() { return iHeight; }
  void                      setNormalize(bool value) { bNormalize = value; }
  bool                      getNormalize() { return bNormalize; }
  virtual CLayer*           clone() = 0;
  virtual void              validate();
  virtual void              build() = 0;

protected:
  string                    sLabel;
  string                    sType;
  int                       iWidth;
  int                       iHeight;
  bool                      bNormalize;
};

#endif /*CLAYER_H_*/
