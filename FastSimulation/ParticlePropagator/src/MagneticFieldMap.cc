#include "MagneticField/Engine/interface/MagneticField.h"
#include "FastSimulation/ParticlePropagator/interface/MagneticFieldMap.h"
#include "FastSimulation/TrackerSetup/interface/TrackerInteractionGeometry.h"

#include <iostream>

MagneticFieldMap::MagneticFieldMap(const MagneticField* pMF,
				   const TrackerInteractionGeometry* myGeo) : 
  pMF_(pMF), 
  geometry_(myGeo),
  bins(101), 
  fieldBarrelHistos(100,static_cast<std::vector<double> >
		    (std::vector<double>(bins,static_cast<double>(0.)))),
  fieldEndcapHistos(100,static_cast<std::vector<double> > 
		     (std::vector<double>(bins,static_cast<double>(0.)))),
  fieldBarrelBinWidth(100,static_cast<double>(0.)),
  fieldBarrelZMin(100,static_cast<double>(0.)),
  fieldEndcapBinWidth(100,static_cast<double>(0.)),
  fieldEndcapRMin(100,static_cast<double>(0.))

{
  // Prepare the histograms
  // std::cout << "Prepare magnetic field local database for FAMOS speed-up" << std::endl;
  for(int cyl = 0; cyl < geometry_->nCylinders(); cyl++) {
    TrackerLayer* layerPtr = geometry_->Cylinder(cyl);

    // Cylinder bounds
    double zmin = 0.;
    double zmax; 
    double rmin = 0.;
    double rmax; 
    if ( layerPtr->forward() ) {
      zmax = layerPtr->disk()->position().z();
      rmax = layerPtr->disk()->outerRadius();
    } else {
      zmax = layerPtr->cylinder()->bounds().length()/2.;
      rmax = layerPtr->cylinder()->bounds().width()/2.
	   - layerPtr->cylinder()->bounds().thickness()/2.;
    }

    // Histograms
    double step;
    // Index of histograms
    layerPtr->setMagneticFieldIdx(cyl);

    // Disk histogram characteristics
    step = (rmax-rmin)/(bins-1);
    fieldEndcapBinWidth[cyl] = step;
    fieldEndcapRMin[cyl] = rmin;

    // Fill the histo
    int endcapBin = 0;
    for ( double radius=rmin+step/2.; radius<rmax+step; radius+=step ) {
      double field = inTeslaZ(GlobalPoint(radius,0.,zmax));
      fieldEndcapHistos[cyl][endcapBin++] = field;
    }

    // Barrel Histogram characteritics
    step = (zmax-zmin)/(bins-1);
    fieldBarrelBinWidth[cyl] = step;
    fieldBarrelZMin[cyl] = zmin;

    // Fill the histo
    int barrelBin = 0;
    for ( double zed=zmin+step/2.; zed<zmax+step; zed+=step ) {
      double field = inTeslaZ(GlobalPoint(rmax,0.,zed));
      fieldBarrelHistos[cyl][barrelBin++] = field;
    }
  }
}


const GlobalVector
MagneticFieldMap::inTesla( const GlobalPoint& gp) const {

  if (!pMF_) {
    return GlobalVector( 0., 0., 4.);
  } else {
    return pMF_->inTesla(gp);
  }

}

const GlobalVector
MagneticFieldMap::inTesla(const TrackerLayer& aLayer, double coord, int success) const {

  if (!pMF_) {
    return GlobalVector( 0., 0., 4.);
  } else {
    return GlobalVector(0.,0.,inTeslaZ(aLayer,coord,success));
  }

}

const GlobalVector 
MagneticFieldMap::inKGauss( const GlobalPoint& gp) const {
  
  return inTesla(gp) * 10.;

}

const GlobalVector
MagneticFieldMap::inInverseGeV( const GlobalPoint& gp) const {
  
  return inKGauss(gp) * 2.99792458e-4;

} 

double 
MagneticFieldMap::inTeslaZ(const GlobalPoint& gp) const {

    return pMF_ ? pMF_->inTesla(gp).z() : 4.0;

}

double
MagneticFieldMap::inTeslaZ(const TrackerLayer& aLayer, double coord, int success) const 
{

  if (!pMF_) {
    return 4.;
  } else {
    // Find the relevant histo
    double theBinWidth;
    double theXMin;
    unsigned idx = aLayer.getMagneticFieldIdx();
    const std::vector<double>* theHisto;

    if ( success == 1 ) { 
      theHisto = theFieldBarrelHisto(idx);
      theBinWidth = fieldBarrelBinWidth[idx];
      theXMin = fieldBarrelZMin[idx];
    } else {
      theHisto = theFieldEndcapHisto(idx);
      theBinWidth = fieldEndcapBinWidth[idx];
      theXMin = fieldEndcapRMin[idx];
    }
    
    // Find the relevant bin
    double x = fabs(coord);
    unsigned bin = (unsigned) ((x-theXMin)/theBinWidth);
    if ( bin+1 == (unsigned)bins ) bin -= 1; // Add a protection against coordinates near the layer edge
    double x1 = theXMin + (bin-0.5)*theBinWidth;
    double x2 = x1+theBinWidth;      

    // Determine the field
    double field1 = (*theHisto)[bin];
    double field2 = (*theHisto)[bin+1];

    return field1 + (field2-field1) * (x-x1)/(x2-x1);

  }

}

double 
MagneticFieldMap::inKGaussZ(const GlobalPoint& gp) const {

    return inTeslaZ(gp)/10.;

}

double 
MagneticFieldMap::inInverseGeVZ(const GlobalPoint& gp) const {

   return inKGaussZ(gp) * 2.99792458e-4;

}

