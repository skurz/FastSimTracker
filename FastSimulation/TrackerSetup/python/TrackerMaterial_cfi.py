import FWCore.ParameterSet.Config as cms

# Material effects to be simulated in the tracker material and associated cuts 
TrackerMaterialBlock = cms.PSet(
    TrackerMaterial = cms.PSet(
        disks = cms.VPSet(
            ########### Pixel Barrel Outside walls and cables (endcap) ###########
            #PIXBOut4
            cms.PSet(
                thickness = cms.double(0.04),
                innerRadius_offset = cms.double(4.2),
                outerRadius_offset = cms.double(16.5),
                length_offset = cms.double(0.5),
                z_offset = cms.double(28.799),
                fudgeMin = cms.vdouble(0.0, 4.2, 5.1, 7.1, 8.2, 10.0, 11.0),
                fudgeMax = cms.vdouble(4.2, 5.1, 7.1, 8.2, 10.0, 11.0, 11.9),
                fudgeFactor = cms.vdouble(0.00, 2.50, 0.00, 2.70, 0.00, 2.80, 0.50),
                activeLayerName = cms.string("")
            ),
            #PIXBOut
            cms.PSet(
                thickness = cms.double(0.012),
                innerRadius_offset = cms.double(3.8),
                outerRadius_offset = cms.double(16.5),
                length_offset = cms.double(0.5),
                z_offset = cms.double(28.8),
                fudgeMin = cms.vdouble(),
                fudgeMax = cms.vdouble(),
                fudgeFactor = cms.vdouble(),
                activeLayerName = cms.string("")
            ),
            ########### Pixel Disks 1-2 ###########
            #PIXD1
            cms.PSet(
                thickness = cms.double(0.058),
                innerRadius_offset = cms.double(-1.0),
                outerRadius_offset = cms.double(+2.0),
                length_offset = cms.double(0.015),
                z_offset = cms.double(0.),
                fudgeMin = cms.vdouble(),
                fudgeMax = cms.vdouble(),
                fudgeFactor = cms.vdouble(),
                activeLayerName = cms.string("FPix1")
            ),
            #PIXD2
            cms.PSet(
                thickness = cms.double(0.058),
                innerRadius_offset = cms.double(-1.0),
                outerRadius_offset = cms.double(2.0002),    # +0.0002 to make sure radius is larger than previous layer
                length_offset = cms.double(0.015),
                z_offset = cms.double(0.),
                fudgeMin = cms.vdouble(),
                fudgeMax = cms.vdouble(),
                fudgeFactor = cms.vdouble(),
                activeLayerName = cms.string("FPix2")
            ),
            ########### Pixel Endcap outside cables ###########
            #PIXBOut6
            cms.PSet(
                thickness = cms.double(0.250),
                innerRadius_offset = cms.double(6.5),
                outerRadius_offset = cms.double(17.61),
                length_offset = cms.double(0.5),
                z_offset = cms.double(65.1),
                fudgeMin = cms.vdouble(0.0, 10.0, 16.0),
                fudgeMax = cms.vdouble(10.0, 11.0, 18.0),
                fudgeFactor = cms.vdouble(1.60, 1.30, 0.70),
                activeLayerName = cms.string("")
            ),
            ########### Tracker Inner Barrel Outside Cables and walls (endcap) ###########
            #TIBEOut
            cms.PSet(
                thickness = cms.double(0.130),
                innerRadius_offset = cms.double(22.5),
                outerRadius_offset = cms.double(53.9),
                length_offset = cms.double(0.05),
                z_offset = cms.double(74.0),
                fudgeMin = cms.vdouble(),
                fudgeMax = cms.vdouble(),
                fudgeFactor = cms.vdouble(),
                activeLayerName = cms.string("")
            ),
            ########### Tracker Inner disks layers 1-3 ###########
            #TID1
            cms.PSet(
                thickness = cms.double(0.04),
                innerRadius_offset = cms.double(-0.5),
                outerRadius_offset = cms.double(+3.5),
                length_offset = cms.double(0.015),
                z_offset = cms.double(0.),
                fudgeMin = cms.vdouble(34.0),
                fudgeMax = cms.vdouble(42.0),
                fudgeFactor = cms.vdouble(2.00),
                activeLayerName = cms.string("TID1")
            ),
            #TID2
            cms.PSet(
                thickness = cms.double(0.04),
                innerRadius_offset = cms.double(-0.5),
                outerRadius_offset = cms.double(+3.5),
                length_offset = cms.double(0.015),
                z_offset = cms.double(0.),
                fudgeMin = cms.vdouble(34.0),
                fudgeMax = cms.vdouble(42.0),
                fudgeFactor = cms.vdouble(2.00),
                activeLayerName = cms.string("TID2")
            ),
            #TID3
            cms.PSet(
                thickness = cms.double(0.055),
                innerRadius_offset = cms.double(-0.5),
                outerRadius_offset = cms.double(+3.5014), # +0.0014 to make sure radius is larger than previous layer
                length_offset = cms.double(0.015),
                z_offset = cms.double(0.),
                fudgeMin = cms.vdouble(34.0),
                fudgeMax = cms.vdouble(42.0),
                fudgeFactor = cms.vdouble(2.00),
                activeLayerName = cms.string("TID3")
            ),
            ########### Tracker Inner Disks Outside Cables and walls (endcap) ###########
            #TIDEOut
            cms.PSet(
                thickness = cms.double(0.074),
                innerRadius_offset = cms.double(22.0),
                outerRadius_offset = cms.double(54.9421), # +0.0014 to make sure radius is larger than previous layer
                length_offset = cms.double(0.5),
                z_offset = cms.double(108.0),
                fudgeMin = cms.vdouble(47.5, 22.0),
                fudgeMax = cms.vdouble(54.0, 24.0),
                fudgeFactor = cms.vdouble(2.50, 1.50),
                activeLayerName = cms.string("")
            ),
            ########### Tracker Outer Barrel Outside Cables and walls (barrel and endcap) ###########
            #TOBEOut
            cms.PSet(
                thickness = cms.double(0.009),
                innerRadius_offset = cms.double(55.0),
                outerRadius_offset = cms.double(111.0),
                length_offset = cms.double(0.5),
                z_offset = cms.double(115.0),
                fudgeMin = cms.vdouble(55.0, 62.0, 78.0),
                fudgeMax = cms.vdouble(60.0, 78.0, 92.0),
                fudgeFactor = cms.vdouble(0.50, 1.50, 1.80),
                activeLayerName = cms.string("")
            ),
            ########### Tracker EndCap disks layers 1-9 ###########
            #TEC1
            cms.PSet(
                thickness = cms.double(0.050),
                innerRadius_offset = cms.double(-1.5),
                outerRadius_offset = cms.double(+2.0),
                length_offset = cms.double(0.015),
                z_offset = cms.double(0.),
                fudgeMin = cms.vdouble(0.0, 24.0, 34.0),
                fudgeMax = cms.vdouble(24.0, 34.0, 39.0),
                fudgeFactor = cms.vdouble(2.0, 0.8, 1.6),
                activeLayerName = cms.string("TEC1")
            ),
            #TEC2
            cms.PSet(
                thickness = cms.double(0.050),
                innerRadius_offset = cms.double(-1.5),
                outerRadius_offset = cms.double(+2.0),
                length_offset = cms.double(0.015),
                z_offset = cms.double(0.),
                fudgeMin = cms.vdouble(0.0, 24.0, 34.0),
                fudgeMax = cms.vdouble(24.0, 34.0, 39.0),
                fudgeFactor = cms.vdouble(2.0, 0.8, 1.6),
                activeLayerName = cms.string("TEC2")
            ),
            #TEC3
            cms.PSet(
                thickness = cms.double(0.050),
                innerRadius_offset = cms.double(-1.5),
                outerRadius_offset = cms.double(+2.0052), # +0.0052 to make sure radius is larger than previous layer
                length_offset = cms.double(0.015),
                z_offset = cms.double(0.),
                fudgeMin = cms.vdouble(0.0, 24.0, 34.0),
                fudgeMax = cms.vdouble(24.0, 34.0, 39.0),
                fudgeFactor = cms.vdouble(2.0, 0.8, 1.6),
                activeLayerName = cms.string("TEC3")
            ),
            #TEC4
            cms.PSet(
                thickness = cms.double(0.050),
                innerRadius_offset = cms.double(-2.5),
                outerRadius_offset = cms.double(+2.0096),   # # +0.0096 to make sure radius is larger than previous layer
                length_offset = cms.double(0.015),
                z_offset = cms.double(0.),
                fudgeMin = cms.vdouble(0.0, 32.0, 41.0),
                fudgeMax = cms.vdouble(32.0, 40.0, 46.0),
                fudgeFactor = cms.vdouble(2.3, 0.6, 1.4),
                activeLayerName = cms.string("TEC4")
            ),
            #TEC5
            cms.PSet(
                thickness = cms.double(0.050),
                innerRadius_offset = cms.double(-2.5),
                outerRadius_offset = cms.double(+2.0076),   # # +0.0076 to make sure radius is larger than previous layer
                length_offset = cms.double(0.015),
                z_offset = cms.double(0.),
                fudgeMin = cms.vdouble(0.0, 32.0, 41.0),
                fudgeMax = cms.vdouble(32.0, 40.0, 46.0),
                fudgeFactor = cms.vdouble(2.3, 0.6, 1.4),
                activeLayerName = cms.string("TEC5")
            ),
            #TEC6
            cms.PSet(
                thickness = cms.double(0.050),
                innerRadius_offset = cms.double(-2.5),
                outerRadius_offset = cms.double(+2.0112),   # # +0.0112 to make sure radius is larger than previous layer
                length_offset = cms.double(0.015),
                z_offset = cms.double(0.),
                fudgeMin = cms.vdouble(0.0, 32.0, 41.0),
                fudgeMax = cms.vdouble(32.0, 40.0, 46.0),
                fudgeFactor = cms.vdouble(2.5, 0.6, 1.4),
                activeLayerName = cms.string("TEC6")
            ),
            #TEC7
            cms.PSet(
                thickness = cms.double(0.050),
                innerRadius_offset = cms.double(-9.5),
                outerRadius_offset = cms.double(+2.0125),   # # +0.0125 to make sure radius is larger than previous layer
                length_offset = cms.double(0.015),
                z_offset = cms.double(0.),
                fudgeMin = cms.vdouble(0.0, 32.0),
                fudgeMax = cms.vdouble(32.0, 60.0),
                fudgeFactor = cms.vdouble(2.7, 0.6),
                activeLayerName = cms.string("TEC7")
            ),
            #TEC8
            cms.PSet(
                thickness = cms.double(0.050),
                innerRadius_offset = cms.double(-9.5),
                outerRadius_offset = cms.double(+2.0097),   # # +0.0097 to make sure radius is larger than previous layer
                length_offset = cms.double(0.015),
                z_offset = cms.double(0.),
                fudgeMin = cms.vdouble(0.0, 32.0),
                fudgeMax = cms.vdouble(32.0, 60.0),
                fudgeFactor = cms.vdouble(3.0, 0.6),
                activeLayerName = cms.string("TEC8")
            ),
            #TEC9
            cms.PSet(
                thickness = cms.double(0.050),
                innerRadius_offset = cms.double(-20.5),
                outerRadius_offset = cms.double(+2.0083),   # # +0.0083 to make sure radius is larger than previous layer
                length_offset = cms.double(0.015),
                z_offset = cms.double(0.),
                fudgeMin = cms.vdouble(0.0, 32.0),
                fudgeMax = cms.vdouble(32.0, 60.0),
                fudgeFactor = cms.vdouble(3.0, 0.6),
                activeLayerName = cms.string("TEC9")
            ),
            ########### Tracker Endcaps Outside Cables and walls (endcaps) ###########
            #TEOut
            cms.PSet(
                thickness = cms.double(0.21),
                innerRadius_offset = cms.double(4.42),
                outerRadius_offset = cms.double(120.001),
                length_offset = cms.double(0.5),
                z_offset = cms.double(300.0),
                fudgeMin = cms.vdouble(4.42, 4.65, 4.84, 7.37, 10.99, 14.70, 16.24, 22.00, 28.50, 31.50, 36.0),
                fudgeMax = cms.vdouble(4.65, 4.84, 7.37, 10.99, 14.70, 16.24, 22.00, 28.50, 31.50, 36.00, 120.0),
                fudgeFactor = cms.vdouble(18.74, 2.30, 0.604, 0.424, 0.327, 0.591, 7.00, 4.40, 3.30, 1.40, 1.60),
                activeLayerName = cms.string("")
            ),
        ),

        barrels = cms.VPSet(
            ########### Beam Pipe ###########
            #PIPE
            cms.PSet(
                thickness = cms.double(0.00240),
                minRadius_offset = cms.double(2.997),
                maxRadius_offset = cms.double(3.003),
                length_offset = cms.double(28.3),
                fudgeMin = cms.vdouble(),
                fudgeMax = cms.vdouble(),
                fudgeFactor = cms.vdouble(),
                activeLayerName = cms.string("")
            ),
            ########### The Pixel Barrel layers 1-3 ###########
            #PIXB1
            cms.PSet(
                thickness = cms.double(0.0217),
                minRadius_offset = cms.double(+0.005),
                maxRadius_offset = cms.double(+0.015),
                length_offset = cms.double(+1.7),
                fudgeMin = cms.vdouble(),
                fudgeMax = cms.vdouble(),
                fudgeFactor = cms.vdouble(),
                activeLayerName = cms.string("BPix1")
            ),
            #PIXB2
            cms.PSet(
                thickness = cms.double(0.0217),
                minRadius_offset = cms.double(-0.005),
                maxRadius_offset = cms.double(+0.005),
                length_offset = cms.double(+1.7),  
                fudgeMin = cms.vdouble(),
                fudgeMax = cms.vdouble(),
                fudgeFactor = cms.vdouble(),
                activeLayerName = cms.string("BPix2")
            ),
            #PIXB3
            cms.PSet(
                thickness = cms.double(0.0217),
                minRadius_offset = cms.double(-0.005),
                maxRadius_offset = cms.double(+0.005),
                length_offset = cms.double(+1.7006), # +0.0006 to make sure length is larger than previous layer
                fudgeMin = cms.vdouble(),
                fudgeMax = cms.vdouble(),
                fudgeFactor = cms.vdouble(),
                activeLayerName = cms.string("BPix3")
            ),
            ########### Pixel Outside walls and cables (barrel) ###########
            #PIXBOut5
            cms.PSet(
                thickness = cms.double(0.050),
                minRadius_offset = cms.double(17.4),
                maxRadius_offset = cms.double(17.6),
                length_offset = cms.double(65.0),
                fudgeMin = cms.vdouble(0.0, 27.5),
                fudgeMax = cms.vdouble(27.5, 32.0),
                fudgeFactor = cms.vdouble(0.27, 1.90),
                activeLayerName = cms.string("")
            ),
            ########### Tracker Inner barrel layers 1-4 ###########
            #TIB1
            cms.PSet(
                thickness = cms.double(0.053),
                minRadius_offset = cms.double(-0.015),
                maxRadius_offset = cms.double(+0.015),
                length_offset = cms.double(0.),
                fudgeMin = cms.vdouble(35.0),
                fudgeMax = cms.vdouble(68.0),
                fudgeFactor = cms.vdouble(1.45),
                activeLayerName = cms.string("TIB1")
            ),
            #TIB2
            cms.PSet(
                thickness = cms.double(0.053),
                minRadius_offset = cms.double(-0.015),
                maxRadius_offset = cms.double(+0.015),
                length_offset = cms.double(0.),
                fudgeMin = cms.vdouble(35.0),
                fudgeMax = cms.vdouble(68.0),
                fudgeFactor = cms.vdouble(1.45),
                activeLayerName = cms.string("TIB2")
            ),
            #TIB3
            cms.PSet(
                thickness = cms.double(0.035),
                minRadius_offset = cms.double(-0.015),
                maxRadius_offset = cms.double(+0.015),
                length_offset = cms.double(+0.4472),  # +0.4472 to make sure length is larger than previous layer
                fudgeMin = cms.vdouble(35.0),
                fudgeMax = cms.vdouble(68.0),
                fudgeFactor = cms.vdouble(1.45),
                activeLayerName = cms.string("TIB3")
            ),
            #TIB4
            cms.PSet(
                thickness = cms.double(0.04),
                minRadius_offset = cms.double(-0.015),
                maxRadius_offset = cms.double(+0.015),
                length_offset = cms.double(0.),
                fudgeMin = cms.vdouble(35.0),
                fudgeMax = cms.vdouble(68.0),
                fudgeFactor = cms.vdouble(1.45),
                activeLayerName = cms.string("TIB4")
            ),
            ########### TOB inside wall (barrel) ###########
            #TOBCIn
            cms.PSet(
                thickness = cms.double(0.009),
                minRadius_offset = cms.double(54.1),
                maxRadius_offset = cms.double(55.1),
                length_offset = cms.double(108.2),
                fudgeMin = cms.vdouble(27.5, 72.0),
                fudgeMax = cms.vdouble(30.5, 110.0),
                fudgeFactor = cms.vdouble(4.00, 5.50),
                activeLayerName = cms.string("")
            ),
            ########### # Tracker Outer barrel layers 1-6 ###########
            #TOB1
            cms.PSet(
                thickness = cms.double(0.03),
                minRadius_offset = cms.double(-0.015),
                maxRadius_offset = cms.double(+0.015),
                length_offset = cms.double(0.),
                fudgeMin = cms.vdouble(0.0, 18.0, 36.0, 55.0),
                fudgeMax = cms.vdouble(18.0, 30.0, 46.0, 108.0),
                fudgeFactor = cms.vdouble(0.70, 2.00, 2.00, 2.00),
                activeLayerName = cms.string("TOB1")
            ),
            #TOB2
            cms.PSet(
                thickness = cms.double(0.03),
                minRadius_offset = cms.double(-0.015),
                maxRadius_offset = cms.double(+0.015),
                length_offset = cms.double(+0.037),   # +0.037 to make sure length is larger than previous layer
                fudgeMin = cms.vdouble(0.0, 18.0, 36.0, 55.0),
                fudgeMax = cms.vdouble(18.0, 30.0, 46.0, 108.0),
                fudgeFactor = cms.vdouble(0.70, 2.00, 2.00, 2.00),
                activeLayerName = cms.string("TOB2")
            ),
            #TOB3
            cms.PSet(
                thickness = cms.double(0.022),
                minRadius_offset = cms.double(-0.015),
                maxRadius_offset = cms.double(+0.015),
                length_offset = cms.double(+0.4582),   # +0.4582 to make sure length is larger than previous layer
                fudgeMin = cms.vdouble(0.0, 18.0, 36.0, 55.0),
                fudgeMax = cms.vdouble(18.0, 30.0, 46.0, 108.0),
                fudgeFactor = cms.vdouble(0.70, 2.00, 2.00, 2.00),
                activeLayerName = cms.string("TOB3")
            ),
            #TOB4
            cms.PSet(
                thickness = cms.double(0.022),
                minRadius_offset = cms.double(-0.015),
                maxRadius_offset = cms.double(+0.015),
                length_offset = cms.double(+0.457),  # +0.457 to make sure length is larger than previous layer
                fudgeMin = cms.vdouble(0.0, 18.0, 36.0, 55.0),
                fudgeMax = cms.vdouble(18.0, 30.0, 46.0, 108.0),
                fudgeFactor = cms.vdouble(0.70, 2.00, 2.00, 2.00),
                activeLayerName = cms.string("TOB4")
            ),
            #TOB5
            cms.PSet(
                thickness = cms.double(0.022),
                minRadius_offset = cms.double(-0.015),
                maxRadius_offset = cms.double(+0.015),
                length_offset = cms.double(+0.4585),  # +0.4585 to make sure length is larger than previous layer
                fudgeMin = cms.vdouble(0.0, 18.0, 36.0, 55.0),
                fudgeMax = cms.vdouble(18.0, 30.0, 46.0, 108.0),
                fudgeFactor = cms.vdouble(0.70, 2.00, 2.00, 2.00),
                activeLayerName = cms.string("TOB5")
            ),
            #TOB6
            cms.PSet(
                thickness = cms.double(0.022),
                minRadius_offset = cms.double(-0.015),
                maxRadius_offset = cms.double(+0.015),
                length_offset = cms.double(+0.4586),  # +0.4586 to make sure length is larger than previous layer
                fudgeMin = cms.vdouble(0.0, 18.0, 36.0, 55.0),
                fudgeMax = cms.vdouble(18.0, 30.0, 46.0, 108.0),
                fudgeFactor = cms.vdouble(0.70, 2.00, 2.00, 2.00),
                activeLayerName = cms.string("TOB6")
            ),
            ########### Tracker Outer Barrel Outside Cables and walls (barrel) ###########
            #TBOut
            cms.PSet(
                thickness = cms.double(0.042),
                minRadius_offset = cms.double(119.0),
                maxRadius_offset = cms.double(120.0),
                length_offset = cms.double(299.9),
                fudgeMin = cms.vdouble(120.0),
                fudgeMax = cms.vdouble(301.0),
                fudgeFactor = cms.vdouble(3.8),
                activeLayerName = cms.string("")
            ),
        ),
    )
)
    
    
