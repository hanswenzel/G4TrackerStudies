#ifndef ConfigurationManagerMessenger_h
#define ConfigurationManagerMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class ConfigurationManager;
class G4UIdirectory;
class G4UIcmdWithABool;
class G4UIcmdWithADoubleAndUnit;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ConfigurationManagerMessenger : public G4UImessenger {
public:

    ConfigurationManagerMessenger(ConfigurationManager*);
    virtual ~ConfigurationManagerMessenger();

    void SetNewValue(G4UIcommand*, G4String);

private:

    ConfigurationManager* mgr;

    G4UIdirectory* testDir;
    G4UIcmdWithABool* anaCmd;
    G4UIcmdWithABool* steplimitCmd;
    G4UIcmdWithADoubleAndUnit* slengthCmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

