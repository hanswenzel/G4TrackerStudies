
#ifndef EventActionMessenger_h
#define EventActionMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class EventAction;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class EventActionMessenger: public G4UImessenger
{
public:

  EventActionMessenger(EventAction*);
  virtual ~EventActionMessenger();
    
  void SetNewValue(G4UIcommand*, G4String);
    
private:

  EventAction*          eventAction;   
  G4UIcmdWithAString*   drawCmd;
  G4UIcmdWithAnInteger* printCmd;    
  G4UIcmdWithAnInteger* dCmd;    

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
