//============================================================================
// Name        : GammaDiff.cpp
// Author      : S.Rasmussen
// Date        : 21/08/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global Headers
#include <math.h>
#include <iomanip>

// Local Headers
#include "GammaDiff.h"
#include "FMM.h"

// Namespace
using namespace std;

//**********************************************************************
// GammaDiff::GammaDiff()
// Default Constructor
//**********************************************************************
GammaDiff::GammaDiff() : CBaseObject(0) {
}

//**********************************************************************
// void GammaDiff::condassign( double &res, const double &cond, const double &arg1, const double &arg2 ) {
// Conditional Assignment
//**********************************************************************
void GammaDiff::condAssign(double &res, const double &cond, const double &arg1, const double &arg2) {
  res = (cond) > 0 ? arg1 : arg2;
}

//**********************************************************************
// void GammaDiff::condassign( double &res, const double &cond, const double &arg)
// Conditional Assignment
//**********************************************************************
void GammaDiff::condAssign(double &res, const double &cond, const double &arg) {
  res = (cond) > 0 ? arg : res;
}

//**********************************************************************
// double GammaDiff::boundp(const double& xx, double fmin, double fmax, double& fpen) {
// Boundary Pin
//**********************************************************************
double GammaDiff::unScaleValue(const double& value, double min, double max) {
  // courtesy of AUTODIF - modified to correct error -
  // penalty on values outside [-1,1] multiplied by 100 as of 14/1/02.
  double t = 0.0;
  double y = 0.0;

  t = min + (max - min) * (sin(value * 1.57079633) + 1) / 2;
  this->condAssign(y, -.9999 - value, (value + .9999) * (value + .9999), 0);
  dPenalty += y;
  this->condAssign(y, value - .9999, (value - .9999) * (value - .9999), 0);
  dPenalty += y;
  this->condAssign(y, -1 - value, 1e5 * (value + 1) * (value + 1), 0);
  dPenalty += y;
  this->condAssign(y, value - 1, 1e5 * (value - 1) * (value - 1), 0);
  dPenalty += y;

  return (t);
}

//**********************************************************************
// double GammaDiff::boundpin(double y, double fmin, double fmax)
// Boundary Pin
//**********************************************************************
double GammaDiff::scaleValue(double value, double min, double max) {
  if (isSame(value, min))
    return -1;
  else if (isSame(value, max))
    return 1;

  return asin(2 * (value - min) / (max - min) - 1) / 1.57079633;
}

//**********************************************************************
// void GammaDiff::buildScaledValues()
// Build our scaled values in relation to our bounds
//**********************************************************************
void GammaDiff::buildScaledValues() {

  for (int i = 0; i < (int)vStartValues.size(); ++i) {
    // Check
    if (vStartValues[i] < vLowerBounds[i])
      throw string(GAMMADIFF_LESS_START_LOWER_BOUND);
    if (vStartValues[i] > vUpperBounds[i])
      throw string(GAMMADIFF_GREATER_START_UPPER_BOUND);

    // Boundary-Pinning
    if (isSame(vLowerBounds[i], vUpperBounds[i]))
      vScaledValues[i] = 0.0;
    else
      vScaledValues[i] = scaleValue(vStartValues[i], vLowerBounds[i], vUpperBounds[i]);
  }
}

//**********************************************************************
// void GammaDiff::buildCurrentValues()
// Build the current test values from our scaled values
//**********************************************************************
void GammaDiff::buildCurrentValues() {

  for (int i = 0; i < (int)vStartValues.size(); ++i) {
    if (isSame(vLowerBounds[i], vUpperBounds[i]))
      vCurrentValues[i] = vLowerBounds[i];
    else
      vCurrentValues[i] = unScaleValue(vScaledValues[i], vLowerBounds[i], vUpperBounds[i]);
  }
}

//**********************************************************************
// double GammaDiff::optimise_finite_differences(CGammaDiffCallback& objective, vector<double>& StartValues, vector<double>& LowerBounds,
//   vector<double>& UpperBounds, int& convergence, bool bPrint, int& iMaxIter, int& iMaxFunc, double dGradTol,
//   double **pOptimiseHessian, int untransformedHessians, double dStepSize)
// Optimise our function
//**********************************************************************
double GammaDiff::optimise_finite_differences(CGammaDiffCallback& objective, vector<double>& StartValues, vector<double>& LowerBounds,
    vector<double>& UpperBounds, int& convergence, bool bPrint, int& iMaxIter, int& iMaxFunc, double dGradTol,
    double **pOptimiseHessian, int untransformedHessians, double dStepSize) {

  // Variables
  int       iVectorSize   = (int)StartValues.size();
  double    dScore        = 0.0;

  // Assign Our Vectors
  vStartValues.assign(StartValues.begin(), StartValues.end());
  vLowerBounds.assign(LowerBounds.begin(), LowerBounds.end());
  vUpperBounds.assign(UpperBounds.begin(), UpperBounds.end());

  vScaledValues.resize(iVectorSize);
  vCurrentValues.resize(iVectorSize);
  vGradientValues.resize(iVectorSize);

  // Validate
  if ((int)LowerBounds.size() != iVectorSize)
    throw string(GAMMADIFF_SIZE_LOWER_BOUND_START_VALUE);
  if ((int)UpperBounds.size() != iVectorSize)
    throw string(GAMMADIFF_SIZE_UPPER_BOUND_START_VALUE);

  // Create our Minimiser
  FMM clMinimiser(iVectorSize, iMaxFunc, iMaxIter, dGradTol, bPrint);

  // Build our Scaled Values
  buildScaledValues();

  // Loop through our Minimiser now
  while (clMinimiser.getResult() >= 0) {
    // Do we need to evaluate objective function again?
    if ((clMinimiser.getResult() == 0) || (clMinimiser.getResult() == 2)) {
      // Reset Variables
      dPenalty = 0.0;

      buildCurrentValues();
      dScore = objective(vCurrentValues);
      dScore += dPenalty;
    }

    // Gradient Required
    // This will loop through each variable changing it once
    // to see how the other variables change.
    // There-by generating our co-variance
    if (clMinimiser.getResult() >= 1) { // 1 = Gradient Required
      long double dOrigValue;
      long double dStepSizeI;
      long double dScoreI;

      for (int i = 0; i < iVectorSize; ++i) {
        if (isSame(vLowerBounds[i], vUpperBounds[i])) {
          vGradientValues[i] = 0.0;

        } else {
          // Workout how much to change the variable by
          dStepSizeI  = dStepSize * ((vScaledValues[i] > 0) ? 1 : -1);

          // Backup Orig Value, and Assign New Var
          dOrigValue        = vScaledValues[i];
          vScaledValues[i]  += dStepSizeI;
          dStepSizeI        = vScaledValues[i] - dOrigValue;

          dPenalty = 0.0;
          buildCurrentValues();

          dScoreI = objective(vCurrentValues);
          dScoreI += dPenalty;

          // Populate Gradient, and Restore Orig Value
          vGradientValues[i]  = (dScoreI - dScore) / dStepSizeI;
          vScaledValues[i]     = dOrigValue;
        }
      }
      // Gradient Finished
    }
    // Call our Function Minimiser
    clMinimiser.fMin(vScaledValues, dScore, vGradientValues);
  }

  if (clMinimiser.getResult() == -3)
    cout << GAMMADIFF_CONVERGENCE_UNCLEAR << endl;
  else if (clMinimiser.getResult() == -2)
    cout << GAMMADIFF_EVALUATIONS_MAX << endl;
  else if (clMinimiser.getResult() == -1)
    cout << GAMMADIFF_CONVERGENCE << endl;
  else
    cout << GAMMADIFF_RETURN_VALUE_UNKNOWN << clMinimiser.getResult() << endl;

  for (int i = 0; i < iVectorSize; ++i) {
    vCurrentValues[i] = unScaleValue(vScaledValues[i], vLowerBounds[i], vUpperBounds[i]);
  }

  for (int i = 0; i < iVectorSize; ++i) {
    vStartValues[i] = vCurrentValues[i];
    StartValues[i] = vCurrentValues[i];
  }

  dScore = objective(vCurrentValues);

  // Generate our Hessian
  if (pOptimiseHessian != 0) {
    double **L              = new double*[iVectorSize];
    double **LT             = new double*[iVectorSize];

    for (int i = 0; i < iVectorSize; ++i) {
      L[i]  = new double[iVectorSize];
      LT[i] = new double[iVectorSize];
    }

    for (int i = 0; i < iVectorSize; ++i) {
      for (int j = 0; j < iVectorSize; ++j) {
        L[i][j] = 0.0;
        LT[i][j] = 0.0;
      }
    }

    for (int i = 0; i < iVectorSize; ++i) {
      for (int j = 0; j <= i; ++j) {
        L[i][j] = LT[j][i] = clMinimiser.getHessianValue(i, j);
      }
    }

    for (int i = 0; i < iVectorSize; ++i) {
      for (int j = 0; j < iVectorSize; ++j) {
        double dMulti = 0.0;

        // Loop Through
        for (int k = 0; k < iVectorSize; ++k)
          dMulti += (L[i][k] * LT[k][j]);

        pOptimiseHessian[i][j] = dMulti;
      }
    }

    if (untransformedHessians) {
      double *dGradBoundP = new double[iVectorSize];
      for (int i = 0; i < iVectorSize; ++i)
        dGradBoundP[i] = 0.0;

      for (int i = 0; i < iVectorSize; ++i) {
        double dDiv   = ((vStartValues[i]-vLowerBounds[i]) / (vUpperBounds[i]-vLowerBounds[i]));
        double dProd  = (2 * dDiv - 1) * (2 * dDiv - 1);
        double dSqrt  = sqrt(1-dProd);
        double dProd2 = (vUpperBounds[i] - vLowerBounds[i]) * dSqrt;
        dGradBoundP[i] = (4/3.14159265)/dProd2;
      }

      for (int i = 0; i < iVectorSize; ++i) {
        if (dGradBoundP[i] != dGradBoundP[i]) // NaN
          dGradBoundP[i] = 0.0;
      }

      for (int i = 0; i < iVectorSize; ++i)
        for (int j = 0; j < iVectorSize; ++j) {
          pOptimiseHessian[i][j] *= dGradBoundP[i];
          pOptimiseHessian[j][i] *= dGradBoundP[i];
        }

      delete [] dGradBoundP;
    }

    for (int i = 0; i < iVectorSize; ++i) {
      delete [] L[i];
      delete [] LT[i];
    }

    delete [] L;
    delete [] LT;
  }

  convergence = clMinimiser.getResult() + 2;
  iMaxIter    = clMinimiser.getIters();
  iMaxFunc    = clMinimiser.getEvals();

  return dScore;
}

//**********************************************************************
// GammaDiff::~GammaDiff()
// Default Destructor
//**********************************************************************
GammaDiff::~GammaDiff() {
}
