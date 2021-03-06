#include "EventAction.hh"
#include "G4Event.hh"
#include "EventActionMessenger.hh"
#include "Analysis.hh"

#include "G4UImanager.hh"
#include "G4ios.hh"
#include "G4Track.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
using namespace std;
EventAction::EventAction():
  printModulo(100),
  nSelected(0),
  drawFlag("all"),
  debugStarted(false)
{
  eventMessenger = new EventActionMessenger(this);
  UI = G4UImanager::GetUIpointer();
  selectedEvents.clear();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

EventAction::~EventAction()
{
  delete eventMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void EventAction::BeginOfEventAction(const G4Event* evt)
{
  // New event
  G4int nEvt = evt->GetEventID();
  if(nEvt%100000==0)G4cout<<"EventID " <<nEvt<<G4endl;
 if(nSelected>0) {
    for(G4int i=0; i<nSelected; i++) {
      if(nEvt == selectedEvents[i]) {
        UI->ApplyCommand("/random/saveThisEvent");
        UI->ApplyCommand("/tracking/verbose  2");
        debugStarted = true;
        break;
      }
    }
  }

}
void EventAction::EndOfEventAction(const G4Event* evt)
{
  
  if(debugStarted) {
    G4cout<<"End of debug: eventID: "<<(evt->GetEventID())<<G4endl;
    UI->ApplyCommand("/tracking/verbose  0");
    debugStarted = false;
  }

  //Analysis* analysis = Analysis::getInstance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
