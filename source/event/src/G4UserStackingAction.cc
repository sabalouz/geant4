// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4UserStackingAction.cc,v 2.2 1998/07/13 16:50:22 urbi Exp $
// GEANT4 tag $Name: geant4-00 $
//
//
//  Last Modification : 09/Dec/96 M.Asai
//

#include "G4UserStackingAction.hh"
#include "G4Track.hh"
#include "G4ios.hh"

G4UserStackingAction::G4UserStackingAction()
{;}

G4UserStackingAction::~G4UserStackingAction()
{;}

G4ClassificationOfNewTrack G4UserStackingAction::ClassifyNewTrack
(G4Track * const aTrack)
{
  return fUrgent;
}

void G4UserStackingAction::NewStage()
{;}

void G4UserStackingAction::PrepareNewEvent()
{;}

