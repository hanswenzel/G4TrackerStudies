
#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class RunAction : public G4UserRunAction
{
public: // Without description

  RunAction();
  ~RunAction();

public: // With description
 
  void BeginOfRunAction(const G4Run*);
  // In this method histogramms are booked

  void EndOfRunAction(const G4Run*);
  // In this method bookHisto method is called in which histogramms are filled
  int nEvts;

};

#endif

