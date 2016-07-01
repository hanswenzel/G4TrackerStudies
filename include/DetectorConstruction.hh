//
// ********************************************************************

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4Material.hh"

class G4LogicalVolume;
class DetectorMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorConstruction : public G4VUserDetectorConstruction {
public:

    DetectorConstruction();
    virtual ~DetectorConstruction();

    G4VPhysicalVolume* Construct();

    void SetWorldMaterial(const G4String&);
    void SetTargetMaterial(const G4String&);

    void SetTargetRadius(G4double val);
    void SetTargetLenght(G4double val);
    void SetMaxStepLength(G4double val);
  
    void UpdateGeometry();
    
private:

    DetectorConstruction & operator=(const DetectorConstruction &right);
    DetectorConstruction(const DetectorConstruction&);

    G4double radius;
    G4double targetZ;
    G4double maxStep;
    
    G4Material* targetMaterial;
    G4Material* worldMaterial;

    G4LogicalVolume* logicTarget;
    G4LogicalVolume* logicWorld;

    DetectorMessenger* detectorMessenger;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

#endif

