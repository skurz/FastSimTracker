#include "FastSimulation/Tracking/interface/TrajectorySeedHitCandidate.h"

#include "DataFormats/TrackerCommon/interface/TrackerTopology.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "FastSimulation/TrackerSetup/interface/TrackerInteractionGeometry.h"

TrajectorySeedHitCandidate::TrajectorySeedHitCandidate(const FastTrackerRecHit * hit, 
						       const TrackerTopology* tTopo) :
  theHit(hit),
  theRingNumber(0)
{ 
  init(tTopo);
}

void
TrajectorySeedHitCandidate::init(const TrackerTopology *tTopo) { 

  const DetId& theDetId = hit()->geographicalId();
  int subDetId = theDetId.subdetId();
  seedingLayer=TrackingLayer::createFromDetId(theDetId,*tTopo);
  if ( subDetId == StripSubdetector::TIB) { 
    forward = false;
  } else if (subDetId==  StripSubdetector::TOB ) { 
    forward = false;
  } else if ( subDetId ==  StripSubdetector::TID) { 
    theRingNumber = tTopo->tidRing(theDetId);
    forward = true;
  } else if ( subDetId ==  StripSubdetector::TEC ) { 
    theRingNumber = tTopo->tecRing(theDetId);
    forward = true;
  } else if ( subDetId ==  PixelSubdetector::PixelBarrel ) { 
    forward = false;
  } else if ( subDetId ==  PixelSubdetector::PixelEndcap ) { 
    forward = true;
  }
}

bool
TrajectorySeedHitCandidate::isOnRequestedDet(const std::vector<std::vector<TrackingLayer> >& theLayersInSets) const{ 
  
  for(unsigned int i=0; i<theLayersInSets.size(); ++i) {
    if(theLayersInSets[i][0]==seedingLayer) return true;
  }

  return false;
}

bool
TrajectorySeedHitCandidate::isOnRequestedDet(const std::vector<std::vector<TrackingLayer> >& theLayersInSets,  const TrajectorySeedHitCandidate& theSeedHitSecond) const{ 

  for(unsigned int i=0; i<theLayersInSets.size(); ++i){
    if( theLayersInSets[i][0]==seedingLayer && 
        theLayersInSets[i][1]==theSeedHitSecond.getTrackingLayer()
        ) 
        return true;
  }
  return false;
}

bool
TrajectorySeedHitCandidate::isOnRequestedDet(const std::vector<std::vector<TrackingLayer> >& theLayersInSets,  const TrajectorySeedHitCandidate& theSeedHitSecond, const TrajectorySeedHitCandidate& theSeedHitThird) const{ 

  for(unsigned int i=0; i<theLayersInSets.size(); ++i){
    if( theLayersInSets[i][0]==seedingLayer && 
        theLayersInSets[i][1]==theSeedHitSecond.getTrackingLayer() &&
        theLayersInSets[i][2]==theSeedHitThird.getTrackingLayer()  
      ) return true;
  }
  return false;
}


