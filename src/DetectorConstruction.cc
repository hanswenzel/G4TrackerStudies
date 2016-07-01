
#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "TrackerSD.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4RunManager.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4StepLimiter.hh"
#include "G4HadronicProcessStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4UserLimits.hh"
#include "G4UnitsTable.hh"
#include "G4ios.hh"

#include "Analysis.hh"
#include "ConfigurationManager.hh"
#include "G4NistManager.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
using namespace std;

DetectorConstruction::DetectorConstruction() {
    logicTarget = 0;
    logicWorld = 0;
    detectorMessenger = new DetectorMessenger(this);

    radius = 0.3 * cm;
    targetZ = 4.0 * 0.5 * cm;
    maxStep = .5 * cm;

    targetMaterial = G4NistManager::Instance()->FindOrBuildMaterial("G4_C");
    worldMaterial = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR");

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction() {
    delete detectorMessenger;
}

G4VPhysicalVolume* DetectorConstruction::Construct() {
    // Cleanup old geometry

    G4GeometryManager::GetInstance()->OpenGeometry();
    G4PhysicalVolumeStore::GetInstance()->Clean();
    G4LogicalVolumeStore::GetInstance()->Clean();
    G4SolidStore::GetInstance()->Clean();

    // Sizes
    G4double worldR = radius + cm;
    G4double worldZ = targetZ + cm;

    //
    // World
    //
    G4Tubs* solidW = new G4Tubs("World", 0., worldR, worldZ, 0., twopi);
    logicWorld = new G4LogicalVolume(solidW, worldMaterial, "World");
    G4VPhysicalVolume* world = new G4PVPlacement(0, G4ThreeVector(),
            logicWorld, "World", 0, false, 0);
    //
    // Target volume
    //
    G4Tubs* solidT = new G4Tubs("Tracker", 0., radius, targetZ, 0., twopi);
    logicTarget = new G4LogicalVolume(solidT, targetMaterial, "Tracker");
    new G4PVPlacement(0, G4ThreeVector(), logicTarget, "Tracker", logicWorld, false, 0);
    G4String SDname = "TrackerSD";
    TrackerSD* aTrackerSD = new TrackerSD(SDname, "HitsCollection");
    // Setting aTrackerSD to all logical volumes with the same name 
    // of "Target".
    SetSensitiveDetector("Tracker", aTrackerSD, true);
    // colors
    G4VisAttributes zero = G4VisAttributes::Invisible;
    logicWorld->SetVisAttributes(&zero);

    G4VisAttributes regCcolor(G4Colour(0., 0.3, 0.7));
    logicTarget->SetVisAttributes(&regCcolor);

    if (ConfigurationManager::getInstance()->GetdoAnalysis()) {
        //for ntuple:
        Analysis* analysis = Analysis::getInstance();
        std::vector<Double_t> vDCinfo;
        vDCinfo.push_back(2. * targetZ);
        vDCinfo.push_back(radius);
        G4double dens = targetMaterial->GetDensity() / (g / cm3);
        G4String nameM = targetMaterial->GetName();
        vDCinfo.push_back(dens);
        //step limits
        if (ConfigurationManager::getInstance()->GetstepLimit()) {
            G4double mxStep = ConfigurationManager::getInstance()->Getlimitval();
            G4UserLimits *fStepLimit = new G4UserLimits(mxStep);
            logicTarget->SetUserLimits(fStepLimit);
        }
        analysis->SetDetConstInfo(vDCinfo, targetMaterial);
    }
    return world;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetTargetMaterial(const G4String& mat) {
    // search the material by its name
    G4Material* material = G4NistManager::Instance()->FindOrBuildMaterial(mat);

    if (material && material != targetMaterial) {
        targetMaterial = material;
        if (logicTarget) logicTarget->SetMaterial(targetMaterial);
        G4RunManager::GetRunManager()->PhysicsHasBeenModified();
    }
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetWorldMaterial(const G4String& mat) {
    // search the material by its name
    G4Material* material = G4NistManager::Instance()->FindOrBuildMaterial(mat);

    if (material && material != worldMaterial) {
        worldMaterial = material;
        if (logicWorld) logicWorld->SetMaterial(worldMaterial);
        G4RunManager::GetRunManager()->PhysicsHasBeenModified();
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::UpdateGeometry() {
    G4RunManager::GetRunManager()->DefineWorldVolume(Construct());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetTargetRadius(G4double val) {
    if (val > 0.0) {
        this->radius = val;
        G4RunManager::GetRunManager()->GeometryHasBeenModified();
    }
}

void DetectorConstruction::SetMaxStepLength(G4double val) {
    if (val > 0.0) {
        this->maxStep = val;
        G4RunManager::GetRunManager()->GeometryHasBeenModified();
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetTargetLenght(G4double val) {
    if (val > 0.0) {
        targetZ = val * 0.5;
        G4RunManager::GetRunManager()->GeometryHasBeenModified();
    }
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
