#ifndef _ForwardTrackerLayer_H_
#define _ForwardTrackerLayer_H_

#include "FastSimulation/TrackerSetup/interface/TrackerLayer.h"
#include "TrackingTools/DetLayers/interface/DetLayer.h"



class ForwardTrackerLayer : public TrackerLayer{
public:

  ForwardTrackerLayer(BoundSurface* theSurface,
    const std::vector<double>& theMinDim,
    const std::vector<double>& theMaxDim,
    const std::vector<double>& theFudge,
    const DetLayer *posDetLayer = 0,
    const DetLayer *negDetLayer = 0):
      TrackerLayer(theSurface, !(posDetLayer == 0) && !(negDetLayer == 0), true, theMinDim, theMaxDim, theFudge),
      posDetLayer(posDetLayer),
      negDetLayer(negDetLayer)
      {}

  const DetLayer* getDetLayer(double z = 0) const { return z >= 0 ? posDetLayer : negDetLayer; }

  ~ForwardTrackerLayer(){};

private:
  const DetLayer *posDetLayer;
  const DetLayer *negDetLayer;

};

#endif

