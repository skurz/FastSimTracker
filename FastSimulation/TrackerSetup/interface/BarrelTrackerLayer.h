#ifndef _BarrelTrackerLayer_H_
#define _BarrelTrackerLayer_H_

#include "FastSimulation/TrackerSetup/interface/TrackerLayer.h"
#include "TrackingTools/DetLayers/interface/DetLayer.h"



class BarrelTrackerLayer : public TrackerLayer{
public:

  BarrelTrackerLayer(BoundSurface* theSurface,
    const std::vector<double>& theMinDim,
    const std::vector<double>& theMaxDim,
    const std::vector<double>& theFudge,
    const DetLayer *detLayer = 0):
      TrackerLayer(theSurface, !(detLayer == 0), false, theMinDim, theMaxDim, theFudge),
      detLayer(detLayer)
      {}

  const DetLayer* getDetLayer(double z = 0) const { return detLayer; }

  ~BarrelTrackerLayer(){};

private:
  const DetLayer *detLayer;

};

#endif

