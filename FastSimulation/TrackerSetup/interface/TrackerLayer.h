#ifndef _TrackerLayer_H_
#define _TrackerLayer_H_

#include "DataFormats/GeometrySurface/interface/BoundSurface.h"
#include "DataFormats/GeometrySurface/interface/BoundCylinder.h"
#include "DataFormats/GeometrySurface/interface/BoundDisk.h"

#include "TrackingTools/DetLayers/interface/DetLayer.h"

#include <vector>

/** A class that gives some properties of the Tracker Layers in FAMOS
 */

class TrackerLayer {
public:

  ~TrackerLayer(){};

  /// constructor from private members
  TrackerLayer(BoundSurface* theSurface,
         bool isSensitive,
	       bool isForward,
	       const std::vector<double>& theMinDim,
	       const std::vector<double>& theMaxDim,
	       const std::vector<double>& theFudge) :
    theSurface(theSurface), 
    isSensitive(isSensitive),
    isForward(isForward),
    theDimensionMinValues(theMinDim),
    theDimensionMaxValues(theMaxDim),
    theFudgeFactors(theFudge),
    theNumberOfFudgeFactors(theFudgeFactors.size())
   { 
     if ( isForward ) { 
       theDisk = dynamic_cast<BoundDisk*>(theSurface);
       theDiskInnerRadius = theDisk->innerRadius();
       theDiskOuterRadius = theDisk->outerRadius();
       theCylinder = 0;
     } else {
       theCylinder = dynamic_cast<BoundCylinder*>(theSurface);
       theDisk = 0;
       theDiskInnerRadius = 0.;
       theDiskOuterRadius = 0.;
     }
     magneticFieldIdx = 0;
   }

  // Get associated det layer (purely virtual)
  virtual const DetLayer* getDetLayer(double z = 0) const = 0;

  /// Is the layer sensitive ?
  inline bool sensitive() const { return isSensitive; }

  /// Is the layer forward ?
  inline bool forward() const { return isForward; }

  /// 
  inline void setMagneticFieldIdx(int idx) { magneticFieldIdx =  idx;}

  /// 
  inline unsigned getMagneticFieldIdx() const { return magneticFieldIdx; }

  /// Returns the surface
  inline const BoundSurface& surface() const { return *theSurface; }

  /// Returns the cylinder
  inline BoundCylinder const* cylinder() const { return theCylinder; }

  /// Returns the surface
  inline BoundDisk const* disk() const { return theDisk; }

  /// Returns the inner radius of a disk
  inline double diskInnerRadius() const { return theDiskInnerRadius; }

  /// Returns the outer radius of a disk
  inline double diskOuterRadius() const { return theDiskOuterRadius; }

  /// Get back the fudge factors
  inline unsigned int fudgeNumber() const { return  theNumberOfFudgeFactors; }
  inline double fudgeMin(unsigned iFudge) const { 
    return (iFudge < theNumberOfFudgeFactors) ? theDimensionMinValues[iFudge] : 999.;
  }
  inline double fudgeMax(unsigned iFudge) const { 
    return (iFudge < theNumberOfFudgeFactors) ? theDimensionMaxValues[iFudge] : -999.;
  }
  inline double fudgeFactor(unsigned iFudge) const { 
    return (iFudge < theNumberOfFudgeFactors) ? theFudgeFactors[iFudge] : 0.;
  }

protected:
  BoundSurface* theSurface;
  BoundDisk* theDisk;
  BoundCylinder* theCylinder;
  bool isSensitive;
  bool isForward;
  double theDiskInnerRadius;
  double theDiskOuterRadius;
  unsigned magneticFieldIdx;

  /// These are fudges factors to account for the inhomogeneities of the material
  std::vector<double> theDimensionMinValues;
  std::vector<double> theDimensionMaxValues;
  std::vector<double> theFudgeFactors;
  unsigned int  theNumberOfFudgeFactors;  

};

#endif

