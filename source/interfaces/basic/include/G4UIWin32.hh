// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4UIWin32.hh,v 2.5 1998/10/23 14:39:02 barrand Exp $
// GEANT4 tag $Name: geant4-00 $
//
#ifndef G4UIWin32_h
#define G4UIWin32_h 

#if defined(G4UI_BUILD_WIN32_SESSION) || defined(G4UI_USE_WIN32)

#include <rw/tvhdict.h>

#include "G4VBasicShell.hh"
#include "G4VInteractiveSession.hh"

#include "G4Win32.hh"

class G4VInteractorManager;

class G4UIWin32 : public G4VBasicShell, public G4VInteractiveSession {
public:
  G4UIWin32 (HINSTANCE,HINSTANCE,LPSTR,int);
  ~G4UIWin32 ();

  G4UIsession* SessionStart      ();
  void Prompt (G4String);
  void SessionTerminate ();
  void PauseSessionStart (G4String);
  G4int ReceiveG4cout(G4String);
  G4int ReceiveG4cerr(G4String);
  void ApplyShellCommand (G4String);
  void AddMenu (const char*,const char*);
  void AddButton (const char*,const char*,const char*);
  G4String GetCommand (int);
  void TextAppendString(char*);
private:
  void SecondaryLoop (G4String);
  void ExecuteCommand (G4String);
  void ShowCurrent (G4String);
  void ChangeDirectoryCommand (G4String);
  void ListDirectory (G4String);
  G4VInteractorManager* interactorManager;
  HWND mainWindow;
  HWND textWindow,editWindow;
  HMENU menuBar,defaultMenu;
  RWTValHashDictionary<int,G4String> commands;
  void* textBuffer;
  int textRows,textCols;
  static LRESULT CALLBACK MainWindowProc(HWND,UINT,WPARAM,LPARAM);
  static LRESULT CALLBACK TextWindowProc(HWND,UINT,WPARAM,LPARAM);
};

#endif

#endif
