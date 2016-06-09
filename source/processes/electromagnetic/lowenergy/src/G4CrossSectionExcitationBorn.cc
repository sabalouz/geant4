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
// $Id: G4CrossSectionExcitationBorn.cc,v 1.4 2008/07/14 20:47:34 sincerti Exp $
// GEANT4 tag $Name: geant4-09-02 $

#include "G4CrossSectionExcitationBorn.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4CrossSectionExcitationBorn::G4CrossSectionExcitationBorn()
{
  lowEnergyLimit = 500. * keV;
  highEnergyLimit = 10 * MeV;
  table = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4CrossSectionExcitationBorn::~G4CrossSectionExcitationBorn()
{
  delete table;
}
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double G4CrossSectionExcitationBorn::CrossSection(const G4Track& track)
{

  G4double sigma = 0.;

  if (table == 0)
  {
    table = new G4DNACrossSectionDataSet(new G4LogLogInterpolation, eV,(1e-22/3.343)*m*m );
    table->LoadData("dna/sigma_excitation_p_born");
  }

  const G4DynamicParticle* particle = track.GetDynamicParticle();
  G4double k = particle->GetKineticEnergy();

  if (k >= lowEnergyLimit && k <= highEnergyLimit)
  { 
    sigma = table->FindValue(k); 
  }
  return sigma;
}

