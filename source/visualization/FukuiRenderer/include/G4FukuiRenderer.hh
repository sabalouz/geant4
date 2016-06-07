// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4FukuiRenderer.hh,v 2.1 1998/11/06 13:41:39 allison Exp $
// GEANT4 tag $Name: geant4-00 $
//
// 
// Satoshi TANAKA
// Fukui Renderer factory.

//=================//
#if defined (G4VIS_BUILD_DAWN_DRIVER) || defined (G4VIS_USE_DAWN)
//=================//

#ifndef G4FUKUI_RENDERER_HH
#define G4FUKUI_RENDERER_HH

#include "G4VGraphicsSystem.hh"
#include "G4FRClientServer.hh"

	//----- prototype
class G4VScene   ;

	//---------------------------------//
	//----- class G4FukuiRenderer -----// 
	//---------------------------------//
class G4FukuiRenderer: public G4VGraphicsSystem {

public:
  G4FukuiRenderer ();
  ~G4FukuiRenderer ();
  G4VScene* CreateScene (const G4String& name = "");
  G4VView*  CreateView  (G4VScene&, const G4String& name = "");

  G4FRClientServer& GetPrimDest() { return fPrimDest ; }

	//----- inter-process communication
  enum { IP_UNIX, IP_INET };
  enum { FR_MAX_PORT_INCR = 10 };
  G4bool IsUnixDomain() const { return (fIPMode == G4FukuiRenderer::IP_UNIX); }
  G4bool IsInetDomain() const { return (fIPMode == G4FukuiRenderer::IP_INET); }
  void                  UseInetDomainAuto();
  void                  UseInetDomain();
  void                  UseBSDUnixDomainAuto();
  void                  ConnectPort( int max_port_incr = FR_MAX_PORT_INCR);

  G4bool	        IsGUIMode   (void) { return flag_use_gui   ; }
  G4bool	        IsConnected (void) { return flag_connected ; }

public:
	//----- inter-process communication
  G4FRClientServer  fPrimDest ;

private:
  int		fIPMode   ;
  G4bool	flag_use_gui ;
  G4int		flag_connected ;
};

#endif
#endif //G4VIS_BUILD_DAWN_DRIVER