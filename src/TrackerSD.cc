#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4VProcess.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"

#include "Analysis.hh"

#include "TrackerSD.hh"
using namespace std;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackerSD::TrackerSD(const G4String& name,
        const G4String& hitsCollectionName)
: G4VSensitiveDetector(name) {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackerSD::~TrackerSD() {
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackerSD::Initialize(G4HCofThisEvent* hce) {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool TrackerSD::ProcessHits(G4Step* aStep,
        G4TouchableHistory*) {
    //
    // we only care about the first elastic or inelastic interaction of the primary particle
    // (geant4 version 4.10 and up) )
    //  

    //            Analysis* analysis = Analysis::getInstance();



    G4double edep = aStep->GetTotalEnergyDeposit();

    if (edep == 0.) return false;
    //    G4cout << "Edep: " << edep << " x: "
    //            << aStep->GetTrack()->GetPosition().x() << " y: "
    //            << aStep->GetTrack()->GetPosition().y() << " z: "
    //            << aStep->GetTrack()->GetPosition().z() 
    //            << " step length: " << aStep->GetStepLength() << G4endl;
    Analysis* analysis = Analysis::getInstance();
  
    analysis->FillEvent(edep,
            aStep->GetTrack()->GetPosition().x(),
            aStep->GetTrack()->GetPosition().y(),
            aStep->GetTrack()->GetPosition().z(),
            aStep->GetStepLength(),
            G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID());
    //G4cout << "eventID: " << G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID() << G4endl;//" x: " << pos.getX() << " y: " << pos.getY() << " z: " << pos.getZ() << " step length: " << aStep->GetStepLength() << G4endl;
    return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackerSD::EndOfEvent(G4HCofThisEvent*) {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
