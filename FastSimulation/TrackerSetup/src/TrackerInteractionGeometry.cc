//Framework Headers
#include "FWCore/Utilities/interface/Exception.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

//CMSSW Headers
#include "DataFormats/GeometrySurface/interface/Surface.h"
#include "DataFormats/GeometrySurface/interface/BoundCylinder.h"
#include "DataFormats/GeometrySurface/interface/SimpleCylinderBounds.h"
#include "DataFormats/GeometrySurface/interface/BoundDisk.h"
#include "DataFormats/GeometrySurface/interface/SimpleDiskBounds.h"

// Tracker/Tracking Headers
#include "RecoTracker/TkDetLayers/interface/GeometricSearchTracker.h"

#include "FastSimulation/TrackerSetup/interface/TrackerLayer.h"
#include "FastSimulation/TrackerSetup/interface/ForwardTrackerLayer.h"
#include "FastSimulation/TrackerSetup/interface/BarrelTrackerLayer.h"

#include "TrackingTools/DetLayers/interface/DetLayer.h"
#include "TrackingTools/DetLayers/interface/BarrelDetLayer.h"
#include "TrackingTools/DetLayers/interface/ForwardDetLayer.h"

//FAMOS Headers
#include "FastSimulation/TrackerSetup/interface/TrackerInteractionGeometry.h"

#include<iostream>

TrackerInteractionGeometry::TrackerInteractionGeometry(const edm::ParameterSet& trackerMaterial, const GeometricSearchTracker* theGeomSearchTracker)
{
    if (!theGeomSearchTracker) 
        throw cms::Exception("FastSimulation/TrackerInteractionGeometry") 
        << "The pointer to the GeometricSearchTracker was not set"; 

    theDisks_ = trackerMaterial.getParameter<std::vector<edm::ParameterSet>>("disks");
    theBarrels_ = trackerMaterial.getParameter<std::vector<edm::ParameterSet>>("barrels");

    double disk_thickness = 0, disk_innerRadius_offset = 0, disk_outerRadius_offset = 0, disk_length_offset = 0, disk_z_offset = 0;
    std::vector<double> disk_fudgeMin, disk_fudgeMax, disk_fudgeFactor;
    std::vector<double> disk_position;
    std::vector<const DetLayer*> disk_detLayers(2, 0);
    double barrel_thickness = 0, barrel_minRadius_offset = 0, barrel_maxRadius_offset = 0, barrel_length_offset = 0;
    std::vector<double> barrel_fudgeMin, barrel_fudgeMax, barrel_fudgeFactor;
    std::vector<double> barrel_position;
    const DetLayer* barrel_detLayer = 0;

    std::vector<edm::ParameterSet>::const_iterator it_disk = theDisks_.begin();
    std::vector<edm::ParameterSet>::const_iterator it_barrel = theBarrels_.begin();

    while(it_disk != theDisks_.end() || it_barrel != theBarrels_.end()){
        if(it_disk != theDisks_.end()){
            disk_thickness = it_disk->getParameter<double>("thickness");
            disk_innerRadius_offset = it_disk->getParameter<double>("innerRadius_offset");
            disk_outerRadius_offset = it_disk->getParameter<double>("outerRadius_offset");
            disk_length_offset = it_disk->getParameter<double>("length_offset");
            disk_z_offset = it_disk->getParameter<double>("z_offset");
            disk_fudgeMin = it_disk->getParameter<std::vector<double>>("fudgeMin");
            disk_fudgeMax = it_disk->getParameter<std::vector<double>>("fudgeMax");
            disk_fudgeFactor = it_disk->getParameter<std::vector<double>>("fudgeFactor");
            disk_detLayers = getForwardDetLayers(it_disk->getParameter<std::string>("activeLayerName"), theGeomSearchTracker);

            // The previous std::vector must have the same size!
            if (disk_fudgeFactor.size() != disk_fudgeMin.size() || disk_fudgeFactor.size() != disk_fudgeMax.size()){
                throw cms::Exception("FastSimulation/TrackerInteractionGeometry ") 
                    << " WARNING with fudge factors!  You have " 
                    << disk_fudgeMin.size() << " min values, "
                    << disk_fudgeMax.size() << " max values and "
                    << disk_fudgeFactor.size() << " fudge factor values!"
                    << std::endl
                    << "Please make enter the same number of inputs " 
                    << "in FastSimulation/TrackerInteractionGeometry/data/TrackerMaterial.cfi"
                    << std::endl;
            }
        }

        if(it_barrel != theBarrels_.end()){
            barrel_thickness = it_barrel->getParameter<double>("thickness");
            barrel_minRadius_offset = it_barrel->getParameter<double>("minRadius_offset");
            barrel_maxRadius_offset = it_barrel->getParameter<double>("maxRadius_offset");
            barrel_length_offset = it_barrel->getParameter<double>("length_offset");
            barrel_fudgeMin = it_barrel->getParameter<std::vector<double>>("fudgeMin");
            barrel_fudgeMax = it_barrel->getParameter<std::vector<double>>("fudgeMax");
            barrel_fudgeFactor = it_barrel->getParameter<std::vector<double>>("fudgeFactor");
            barrel_detLayer = getBarrelDetLayer(it_barrel->getParameter<std::string>("activeLayerName"), theGeomSearchTracker);

            // The previous std::vector must have the same size!
            if (barrel_fudgeFactor.size() != barrel_fudgeMin.size() || barrel_fudgeFactor.size() != barrel_fudgeMax.size()){
                throw cms::Exception("FastSimulation/TrackerInteractionGeometry ") 
                    << " WARNING with fudge factors!  You have " 
                    << barrel_fudgeMin.size() << " min values, "
                    << barrel_fudgeMax.size() << " max values and "
                    << barrel_fudgeFactor.size() << " fudge factor values!"
                    << std::endl
                    << "Please make enter the same number of inputs " 
                    << "in FastSimulation/TrackerInteractionGeometry/data/TrackerMaterial.cfi"
                    << std::endl;
            }
        }

        // Get position if layer is active
        disk_position = getPosition(disk_detLayers.at(0), true);
        barrel_position = getPosition(barrel_detLayer, false);


        // Construct either disk or barrel: choose smallest radius
        bool add_disk = false;
        if(it_disk != theDisks_.end() && it_barrel != theBarrels_.end()){            
            if(disk_position.at(1) + disk_outerRadius_offset < barrel_position.at(1) + barrel_maxRadius_offset) add_disk = true;
            else add_disk = false;
        }
        else if(it_disk != theDisks_.end() && it_barrel == theBarrels_.end()) add_disk = true;
        else if(it_disk == theDisks_.end() && it_barrel != theBarrels_.end()) add_disk = false;
        else assert(0);

        // ignore layer if thickness=0
        if(disk_thickness < 0.0000001){
            it_disk++;
            continue;
        }
        if(barrel_thickness < 0.0000001){
            it_barrel++;
            continue;
        }


        if(add_disk){
            _mediumProperties.push_back(new MediumProperties(disk_thickness,0.0001));

            const SimpleDiskBounds diskBounds(disk_position.at(0) + disk_innerRadius_offset, disk_position.at(1) + disk_outerRadius_offset, -(disk_position.at(2) + disk_length_offset), +(disk_position.at(2) + disk_length_offset));
            const Surface::PositionType positionType(0.,0.,disk_position.at(3)+disk_z_offset);
            const Surface::RotationType theRotation2(1.,0.,0.,0.,1.,0.,0.,0.,1.);

            BoundDisk* theDisk = new BoundDisk(positionType, theRotation2, diskBounds);
            theDisk->setMediumProperties(*_mediumProperties[_mediumProperties.size() -1]);

            _theCylinders.push_back(std::unique_ptr<ForwardTrackerLayer>(new ForwardTrackerLayer(theDisk, disk_fudgeMin, disk_fudgeMax, disk_fudgeFactor, disk_detLayers.at(0), disk_detLayers.at(1))));
            it_disk++;
        }else{      
            _mediumProperties.push_back(new MediumProperties(barrel_thickness,0.0001));

            const SimpleCylinderBounds cylBounds(barrel_position.at(0) + barrel_minRadius_offset, barrel_position.at(1) + barrel_maxRadius_offset, -(barrel_position.at(2) + barrel_length_offset), +(barrel_position.at(2) + barrel_length_offset));
            const Surface::PositionType thePosition(0.,0.,0.);
            const Surface::RotationType theRotation(1.,0.,0.,0.,1.,0.,0.,0.,1.); 
      
            BoundCylinder* theCylinder = new BoundCylinder(thePosition, theRotation, cylBounds);
            theCylinder->setMediumProperties(*_mediumProperties[_mediumProperties.size() -1]);

            _theCylinders.push_back(std::unique_ptr<BarrelTrackerLayer>(new BarrelTrackerLayer(theCylinder, barrel_fudgeMin, barrel_fudgeMax, barrel_fudgeFactor, barrel_detLayer)));
            it_barrel++;
        }
    }
  

    // Check overall compatibility of cylinder dimensions
    // (must be nested cylinders)
    // Throw an exception if the test fails
    double zin, rin;
    double zout, rout;
    unsigned nCyl=0;
    bool isForwardIn, isForwardOut;

    // Inner cylinder dimensions
    if(Cylinder(0)->forward()) {
        zin = Cylinder(0)->disk()->position().z();
        rin = Cylinder(0)->disk()->outerRadius();
    }else{
        zin = Cylinder(0)->cylinder()->bounds().length()/2.;
        rin = Cylinder(0)->cylinder()->bounds().width()/2.;
    }
    isForwardIn = Cylinder(0)->forward();

    // And loop over all cylinders
    for(int i = 1; i < nCylinders(); i++){
        // Outer cylinder dimensions
        if(Cylinder(i)->forward()){
            zout = Cylinder(i)->disk()->position().z();
            rout = Cylinder(i)->disk()->outerRadius();
        }else{
            zout = Cylinder(i)->cylinder()->bounds().length()/2.;
            rout = Cylinder(i)->cylinder()->bounds().width()/2.;
        }
        isForwardOut = Cylinder(i)->forward();

        nCyl++;
        std::cout.precision(4);
        if(zout < zin || rout < rin){ 
            //std::cout << "z="  << zout << "; " << "r=" << rout << std::endl;
          throw cms::Exception("FastSimulation/TrackerInteractionGeometry ") 
        	<< " WARNING with cylinder number " << nCyl 
        	<< " (isForward:" <<  isForwardIn << ") "
        	<< " has dimensions smaller than previous cylinder " 
            << " (isForward:" <<  isForwardOut << "): "<< std::endl
        	<< " zOuter/zInner=" << zout << "/" << zin << std::endl
        	<< " rOuter/rInner=" << rout << "/" << rin << std::endl;
        }else{
        /*   
          std::cout << " Cylinder number " << nCyl 
        	<< "(Active Layer Number=" <<  cylinderOut->layerNumber() 
        	<< "; isForward:" <<  cylinderOut->forward() << " ) "
        	<< "has dimensions of: " 
        	<< "z="  << zout << "; " 
        	<< "r=" << rout << std::endl;
        */
        }

        // Go to the next cylinder
        // Inner cylinder becomes outer cylinder
        zin = zout;
        rin = rout;
        // End test
    }

}

std::vector<double>
TrackerInteractionGeometry::getPosition(const DetLayer* detLayer, bool isForward){
    // 0: innerRadius
    // 1: outerRadius
    // 2: length/2
    // 3: z
    std::vector<double> position(4, 0.);
    if(detLayer == 0) return position;

    if(!isForward){
        position.at(0) = static_cast<BarrelDetLayer const*>(detLayer)->specificSurface().radius();
        position.at(1) = static_cast<BarrelDetLayer const*>(detLayer)->specificSurface().radius();
        position.at(2) = static_cast<BarrelDetLayer const*>(detLayer)->specificSurface().bounds().length() / 2.;
        position.at(3) = 0.;
    }else{
        position.at(0) = static_cast<ForwardDetLayer const*>(detLayer)->specificSurface().innerRadius();
        position.at(1) = static_cast<ForwardDetLayer const*>(detLayer)->specificSurface().outerRadius();
        position.at(2) = 0.;
        position.at(3) = static_cast<ForwardDetLayer const*>(detLayer)->surface().position().z();
    }
    
    return position;
}

const DetLayer*
TrackerInteractionGeometry::getBarrelDetLayer(std::string layerName, const GeometricSearchTracker* theGeomSearchTracker){

    if(layerName.empty()) return 0;

    const DetLayer *detLayer = 0;

    if (layerName.substr(0,4)=="BPix"){
        int index = std::atoi(layerName.substr(4,1).c_str()) -1;
        if(index < 0) throw cms::Exception("FastSimulation/TrackerInteractionGeometry") << "No valid index in '" << layerName.c_str() << "'";
        if(theGeomSearchTracker->pixelBarrelLayers().size() <= std::abs(index))
            throw cms::Exception("FastSimulation/TrackerInteractionGeometry") << "Layer index out of range: '" << layerName.c_str() << "'";
        detLayer = *(theGeomSearchTracker->pixelBarrelLayers().begin() + index);
    }else if (layerName.substr(0,3)=="TIB"){
        int index = std::atoi(layerName.substr(3,1).c_str()) -1;
        if(index < 0) throw cms::Exception("FastSimulation/TrackerInteractionGeometry") << "No valid index in '" << layerName.c_str() << "'";
        if(theGeomSearchTracker->tibLayers().size() <= std::abs(index))
            throw cms::Exception("FastSimulation/TrackerInteractionGeometry") << "Layer index out of range: '" << layerName.c_str() << "'";
        detLayer = *(theGeomSearchTracker->tibLayers().begin() + index);
    }else if (layerName.substr(0,3)=="TOB"){
        int index = std::atoi(layerName.substr(3,1).c_str()) -1;
        if(index < 0) throw cms::Exception("FastSimulation/TrackerInteractionGeometry") << "No valid index in '" << layerName.c_str() << "'";
        if(theGeomSearchTracker->tobLayers().size() <= std::abs(index))
            throw cms::Exception("FastSimulation/TrackerInteractionGeometry") << "Layer index out of range: '" << layerName.c_str() << "'";
        detLayer = *(theGeomSearchTracker->tobLayers().begin() + index);
    }
    else{
        throw cms::Exception("FastSimulation/TrackerInteractionGeometry")
            << "Bad data naming in tracker layer configuration."
            << "no case sensitive name of ['BPix','TIB',TOB'] matches '"<<layerName.c_str()<<"'";
    }
    
    return detLayer;
}

std::vector<const DetLayer*>
TrackerInteractionGeometry::getForwardDetLayers(std::string layerName, const GeometricSearchTracker* theGeomSearchTracker){

    std::vector<const DetLayer*> detLayers(2, 0);

    if(layerName.empty()) return detLayers;

    if (layerName.substr(0,4)=="FPix"){
        int index = std::atoi(layerName.substr(4,1).c_str()) -1;    
        if(index < 0) throw cms::Exception("FastSimulation/TrackerInteractionGeometry") << "No valid index in '" << layerName.c_str() << "'";
        if(theGeomSearchTracker->posPixelForwardLayers().size() <= std::abs(index))
            throw cms::Exception("FastSimulation/TrackerInteractionGeometry") << "Layer index out of range: '" << layerName.c_str() << "'";
        detLayers.at(0) = *(theGeomSearchTracker->posPixelForwardLayers().begin() + index);
        detLayers.at(1) = *(theGeomSearchTracker->negPixelForwardLayers().begin() + index);
    }else if (layerName.substr(0,3)=="TID"){
        int index = std::atoi(layerName.substr(3,1).c_str()) -1;
        if(index < 0) throw cms::Exception("FastSimulation/TrackerInteractionGeometry") << "No valid index in '" << layerName.c_str() << "'";
        if(theGeomSearchTracker->posTidLayers().size() <= std::abs(index))
            throw cms::Exception("FastSimulation/TrackerInteractionGeometry") << "Layer index out of range: '" << layerName.c_str() << "'";
        detLayers.at(0) = *(theGeomSearchTracker->posTidLayers().begin() + index);
        detLayers.at(1) = *(theGeomSearchTracker->negTidLayers().begin() + index);
    }else if (layerName.substr(0,3)=="TEC"){
        int index = std::atoi(layerName.substr(3,1).c_str()) -1;
        if(index < 0) throw cms::Exception("FastSimulation/TrackerInteractionGeometry") << "No valid index in '" << layerName.c_str() << "'";
        if(theGeomSearchTracker->posTecLayers().size() <= std::abs(index))
            throw cms::Exception("FastSimulation/TrackerInteractionGeometry") << "Layer index out of range: '" << layerName.c_str() << "'";
        detLayers.at(0) = *(theGeomSearchTracker->posTecLayers().begin() + index);
        detLayers.at(1) = *(theGeomSearchTracker->negTecLayers().begin() + index);
    }
    else{
        throw cms::Exception("FastSimulation/TrackerInteractionGeometry")
            << "Bad data naming in tracker layer configuration."
            << "no case sensitive name of ['FPix',TID','TEC'] matches '"<<layerName.c_str()<<"'";
    }
    
    return detLayers;
}

TrackerInteractionGeometry::~TrackerInteractionGeometry()
{
    _theCylinders.clear();
    
    for(unsigned int i = 0; i < _mediumProperties.size(); i++){
        delete _mediumProperties[i];
    }
}
