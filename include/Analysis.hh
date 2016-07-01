
#ifndef ANALYSIS_HH
#define ANALYSIS_HH

#include "globals.hh"

//root
#include "TSystem.h"

//G4
#include "G4ios.hh"
#include "G4TrajectoryContainer.hh"
#include "G4ParticleDefinition.hh"
#include "G4Element.hh"
#include "G4Material.hh"

#include <map>
#include <vector>


class G4ParticleDefinition;
class G4Step;
class TFile;
class TTree;
class G4Track;
class G4VTrajectory;

//class ProdTuple_t;

class Analysis {
public:

    Analysis();
    ~Analysis();

    void book(G4long, G4long);
  //    void FillNtuple(std::vector<TrackInfo_t>);

    void FillEvent(Double_t edep,
            Double_t x,
            Double_t y,
            Double_t z,
            Double_t StepLength,
            G4int eventID);
    void WriteEvent();
    void WriteNtuple();
    void WriteHeader();
    void SetDetConstInfo(std::vector<Double_t> DCinfo, G4Material* mat);
    void SetPrimGenInfo(Double_t enerPrim, G4ParticleDefinition* Part);
    void SetRunActInfo(Int_t nevt);
    static Analysis* getInstance();
    void finish();

 
private:
    static Analysis* instance;

    char NtupleFileName[50];
    TFile* FileNtuple;
    //   TTree* ProdTree;
    TTree* HeaderTree;
    TTree* EventTree;
  //    ProdTuple_t g4Proddata;
    //info for header:
    Double_t thickness;
    Double_t radius;
    Double_t rho;
    Double_t aweight;
    Double_t edep;
    Double_t x;
    Double_t y;
    Double_t z;
    Double_t StepLength;
    G4int eventID;
    G4Material* mate;
    std::string material;
    Double_t enerPrimGen;
    std::string namePrim;
    G4ParticleDefinition* particle;
    std::string PartName;
    Int_t numberEvts;
};

#endif 
