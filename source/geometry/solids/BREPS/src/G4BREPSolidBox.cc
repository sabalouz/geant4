//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: G4BREPSolidBox.cc,v 1.11 2008/01/22 16:03:52 tnikitin Exp $
// GEANT4 tag $Name: geant4-09-01-patch-02 $
//
// ----------------------------------------------------------------------
// GEANT 4 class source file
//
// G4BREPSolidBox.cc
//
// ----------------------------------------------------------------------

#include "G4BREPSolidBox.hh"
#include "G4FPlane.hh"
#include "G4Point3DVector.hh"

G4BREPSolidBox::G4BREPSolidBox(const G4String& name,
			       const G4Point3D& Pt1,
			       const G4Point3D& Pt2,
			       const G4Point3D& Pt3,
			       const G4Point3D& Pt4,
			       const G4Point3D& Pt5,
			       const G4Point3D& Pt6,
			       const G4Point3D& Pt7,
			       const G4Point3D& Pt8): G4BREPSolid(name)
{
  nb_of_surfaces=6;
  active=1;PlaneSolid=1;
  SurfaceVec = new G4Surface*[6];
  G4Point3DVector PVec(4);
  G4int sense=0;

  PVec[0] = Pt1;
  PVec[1] = Pt2;
  PVec[2] = Pt3;
  PVec[3] = Pt4;  
  SurfaceVec[0] = new G4FPlane(&PVec);

  PVec[2] = Pt6;
  PVec[3] = Pt5;  
  SurfaceVec[1] = new G4FPlane(&PVec,0,sense);

  PVec[0] = Pt2;
  PVec[1] = Pt6;
  PVec[2] = Pt7;
  PVec[3] = Pt3;  
  SurfaceVec[2] = new G4FPlane(&PVec);

  PVec[0] = Pt3;
  PVec[1] = Pt7;
  PVec[2] = Pt8;
  PVec[3] = Pt4;  
  SurfaceVec[3] = new G4FPlane(&PVec);

  PVec[0] = Pt1;
  PVec[1] = Pt5;
  PVec[2] = Pt8;
  PVec[3] = Pt4;  
  SurfaceVec[4] = new G4FPlane(&PVec,0,sense);

  PVec[0] = Pt5;
  PVec[1] = Pt6;
  PVec[2] = Pt7;
  PVec[3] = Pt8;  
  SurfaceVec[5] = new G4FPlane(&PVec,0,sense);

  // Save the constructor parameters
  constructorParams[0] = Pt1;
  constructorParams[1] = Pt2;
  constructorParams[2] = Pt3;
  constructorParams[3] = Pt4;
  constructorParams[4] = Pt5;
  constructorParams[5] = Pt6;
  constructorParams[6] = Pt7;
  constructorParams[7] = Pt8;
  
  Initialize();
  
}

G4BREPSolidBox::G4BREPSolidBox( __void__& a )
  : G4BREPSolid(a)
{
}

G4BREPSolidBox::~G4BREPSolidBox()
{
}

EInside G4BREPSolidBox::Inside(register const G4ThreeVector& Pt) const
{
  G4Point3D Point(Pt);

  // Get the bounding box extent
  G4Point3D min = bbox->GetBoxMin();
  min += G4Point3D(-0.5*kCarTolerance,-0.5*kCarTolerance,-0.5*kCarTolerance);

  G4Point3D max = bbox->GetBoxMax();
  max += G4Point3D(0.5*kCarTolerance,0.5*kCarTolerance,0.5*kCarTolerance);

  if( (Point.x() < min.x() || Point.x() > max.x()) ||
      (Point.y() < min.y() || Point.y() > max.y()) ||
      (Point.z() < min.z() || Point.z() > max.z())    )
    return kOutside;

  if( (Point.x() > min.x() && Point.x() < max.x())&&
      (Point.y() > min.y() && Point.y() < max.y())&&
      (Point.z() > min.z() && Point.z() < max.z())   )
    return kInside;
  
  return kSurface;
}

// Streams solid contents to output stream.
std::ostream& G4BREPSolidBox::StreamInfo(std::ostream& os) const
{
     G4BREPSolid::StreamInfo( os )
     << "\n"
     << "   Pt1: " << constructorParams[0]
     << "   Pt2: " << constructorParams[1]
     << "   Pt3: " << constructorParams[2]
     << "   Pt4: " << constructorParams[3]
     << "\n   Pt5: " << constructorParams[4]
     << "   Pt6: " << constructorParams[5]
     << "   Pt7: " << constructorParams[6]
     << "   Pt8: " << constructorParams[7]
     << "\n-----------------------------------------------------------\n";

  return os;
}

