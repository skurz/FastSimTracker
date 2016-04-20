#ifndef FastSimulation_TrackerSetup_TrackerInteractionGeometry_H
#define FastSimulation_TrackerSetup_TrackerInteractionGeometry_H
// v0  who ? when ? 
// 11 Dec 2003 Florian Beaudette. Removed the surfaces corresponding to ECAL 
//             This will carried out by the FamosTrajectoryManager
// 12 Oct 2006 Patrick Janot. Removed hardcoded active geometry & rings
//                            Removed RecHit smearing parameterization
// 16 Nov 2007 Patrick Janot. Make the whole thing configurable 

//FAMOS Headers
#include "FastSimulation/TrackerSetup/interface/TrackerLayer.h"
#include "FastSimulation/TrackerSetup/interface/ForwardTrackerLayer.h"
#include "FastSimulation/TrackerSetup/interface/BarrelTrackerLayer.h"

#include <list>
#include <string>
#include <vector>

class MediumProperties;
class GeometricSearchTracker;

namespace edm { 
  class ParameterSet;
}

class TrackerInteractionGeometry
{

public:
  // ATTENTION!!
  // This line has to be removed if all cross-links using the layerNumber are removed!!!
  enum FirstCylinders {PXB=0,PXD=3,TIB=5,TID=9,TOB=12,TEC=18};


  /// Constructor : get the configurable parameters
  TrackerInteractionGeometry(const edm::ParameterSet& trackerMaterial,
			     const GeometricSearchTracker* geomSearchTracker);

  /// Destructor
  ~TrackerInteractionGeometry();

  /// Returns the first pointer in the cylinder list
  inline TrackerLayer* Cylinder(unsigned i) const
    {return _theCylinders.at(i).get();}

  /// Returns the number of cylinders in the Tracker
  inline const int nCylinders() const 
    {return _theCylinders.size();}

private:
  std::vector<double> getPosition(const DetLayer * detLayer, bool isForward);
  const DetLayer* getBarrelDetLayer(std::string layerName, const GeometricSearchTracker* theGeomSearchTracker);
  std::vector<const DetLayer*> getForwardDetLayers(std::string layerName, const GeometricSearchTracker* theGeomSearchTracker);

private:

  /// The list of tracker (sensistive or not) layers
  std::vector<std::unique_ptr<TrackerLayer>> _theCylinders;

  /// Barrels
  std::vector<edm::ParameterSet> theDisks_;
  std::vector<edm::ParameterSet> theBarrels_;

  std::vector<MediumProperties *> _mediumProperties;

};
#endif
