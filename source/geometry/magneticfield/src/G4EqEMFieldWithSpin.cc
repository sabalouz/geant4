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
// $Id: G4EqEMFieldWithSpin.cc,v 1.1.2.1 2008/04/24 12:43:57 gcosmo Exp $
// GEANT4 tag $Name: geant4-09-01-patch-02 $
//
//
//  This is the standard right-hand side for equation of motion.
//
//  The only case another is required is when using a moving reference
//  frame ... or extending the class to include additional Forces,
//  eg an electric field
//
//  30.08.2007 Chris Gong, Peter Gumplinger
//
// -------------------------------------------------------------------

#include "G4EqEMFieldWithSpin.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"

G4EqEMFieldWithSpin::G4EqEMFieldWithSpin(G4ElectroMagneticField *emField )
      : G4EquationOfMotion( emField ) { anomaly = 1.165923e-3; }

void  
G4EqEMFieldWithSpin::SetChargeMomentumMass(G4double particleCharge, // e+ units
		                            G4double MomentumXc,
                                            G4double particleMass)
{
   fElectroMagCof =  eplus*particleCharge*c_light ;
   fMassCof = particleMass*particleMass ;

   omegac = 0.105658387*GeV/particleMass * 2.837374841e-3*(rad/cm/kilogauss);

   ParticleCharge = particleCharge;

   E = std::sqrt(sqr(MomentumXc)+sqr(particleMass));
   beta  = MomentumXc/E;
   gamma = E/particleMass;
}



void
G4EqEMFieldWithSpin::EvaluateRhsGivenB(const G4double y[],
			                const G4double Field[],
				              G4double dydx[] ) const
{

   // Components of y:
   //    0-2 dr/ds, 
   //    3-5 dp/ds - momentum derivatives 

   G4double pSquared = y[3]*y[3] + y[4]*y[4] + y[5]*y[5] ;

   G4double Energy   = std::sqrt( pSquared + fMassCof );
   G4double cof2     = Energy/c_light ;

   G4double pModuleInverse  = 1.0/std::sqrt(pSquared) ;

   //  G4double inverse_velocity = Energy * c_light * pModuleInverse;
   G4double inverse_velocity = Energy * pModuleInverse / c_light;

   G4double cof1     = fElectroMagCof*pModuleInverse ;

   //  G4double vDotE = y[3]*Field[3] + y[4]*Field[4] + y[5]*Field[5] ;


   dydx[0] = y[3]*pModuleInverse ;                         
   dydx[1] = y[4]*pModuleInverse ;                         
   dydx[2] = y[5]*pModuleInverse ;                        

   dydx[3] = cof1*(cof2*Field[3] + (y[4]*Field[2] - y[5]*Field[1])) ;
   
   dydx[4] = cof1*(cof2*Field[4] + (y[5]*Field[0] - y[3]*Field[2])) ; 
 
   dydx[5] = cof1*(cof2*Field[5] + (y[3]*Field[1] - y[4]*Field[0])) ;  
   
   dydx[6] = dydx[8] = 0.;//not used

   // Lab Time of flight
   dydx[7] = inverse_velocity;
   
   G4ThreeVector BField(Field[0],Field[1],Field[2]);

   G4ThreeVector u(y[3], y[4], y[5]);
   u *= pModuleInverse;

   G4double udb = anomaly*beta*gamma/(1.+gamma) * (BField * u);
   G4double ucb = (anomaly+1./gamma)/beta;

   G4ThreeVector Spin(y[9],y[10],y[11]);
   G4ThreeVector dSpin;

   dSpin = ParticleCharge*omegac*(ucb*(Spin.cross(BField))-udb*(Spin.cross(u)));

   dydx[ 9] = dSpin.x();
   dydx[10] = dSpin.y();
   dydx[11] = dSpin.z();

   return ;
}
