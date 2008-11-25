//============================================================================
// Name        : CObservationManager.h
// Author      : S.Rasmussen
// Date        : 17/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description : This class is responsible for maintaining a list of our
//       Observations. Like all Manager it is responsible for the validate
//       and execute calls to the children.
//
//       In order for the Minimiser (ADOLC) to work correctly, we must
//       provide a score back after each run through our model that relates
//       to how accurate our model was against the observations. This allows
//       the minimiser to change the parameters to find a better fit. The
//       Observations are the main comparison against the results to get this
//       score (Objective Value). Once the model has been completed, the
//       score for each Observation is added (Objective Function) and the
//       result if passed to the minimiser.
//
// $Date$
//============================================================================
#ifndef COBSERVATIONMANAGER_H_
#define COBSERVATIONMANAGER_H_

// Local Headers
#include "BaseClasses/CBaseBuildableObject.h"

// Classes
class CObservation;

//**********************************************************************
//
//
//**********************************************************************
class CObservationManager : public CBaseBuildableObject {
public:
  static CObservationManager* Instance();
  static void                Destroy();

  // Functions
  void                       addObservation(CObservation *pObservation);
  int                        getObservationCount() { return vObservationList.size(); }
  CObservation*              getObservation(int index);
  void                       clone(CObservationManager *Manager);
  void                       validate();
  void                       build();
  void                       execute(int Year, int Step);
  virtual                    ~CObservationManager();

protected:
  // Functions
	CObservationManager();

	// Variables
	vector<CObservation*>      vObservationList;

private:
  static boost::thread_specific_ptr<CObservationManager> clInstance;
};

#endif /*COBSERVATIONMANAGER_H_*/
