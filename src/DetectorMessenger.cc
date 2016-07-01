#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"
using namespace std;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::DetectorMessenger(DetectorConstruction * Det)
:Detector(Det)
{
  testDir = new G4UIdirectory("/TrackerTest/");
  testDir->SetGuidance("G4 TrackerTest stores all steps within the TrackerSD. The test allows to apply step limits.");

  matCmd = new G4UIcmdWithAString("/TrackerTest/TargetMat",this);
  matCmd->SetGuidance("Select Material for the target");
  matCmd->SetParameterName("tMaterial",false);
  matCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  mat1Cmd = new G4UIcmdWithAString("/TrackerTest/WorldMat",this);
  mat1Cmd->SetGuidance("Select Material for world");
  mat1Cmd->SetParameterName("wMaterial",false);
  mat1Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  rCmd = new G4UIcmdWithADoubleAndUnit("/TrackerTest/TargetRadius",this);
  rCmd->SetGuidance("Set radius of the target");
  rCmd->SetParameterName("radius",false);
  rCmd->SetUnitCategory("Length");
  rCmd->SetRange("radius>0");
  rCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  stepCmd = new G4UIcmdWithADoubleAndUnit("/TrackerTest/MaxStepLength",this);
  stepCmd->SetGuidance("Set Maximum Step Length");
  stepCmd->SetParameterName("maxStep",false);
  stepCmd->SetUnitCategory("Length");
  stepCmd->SetRange("maxStep>0");
  stepCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  lCmd = new G4UIcmdWithADoubleAndUnit("/TrackerTest/TargetLength",this);
  lCmd->SetGuidance("Set length of the target");
  lCmd->SetParameterName("length",false);
  lCmd->SetUnitCategory("Length");
  lCmd->SetRange("length>0");
  lCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  updateCmd = new G4UIcmdWithoutParameter("/TrackerTest/Update",this);
  updateCmd->SetGuidance("Update geometry.");
  updateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
  updateCmd->SetGuidance("if you changed geometrical value(s)");
  updateCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::~DetectorMessenger()
{
  delete matCmd;
  delete mat1Cmd;
  delete rCmd;
  delete lCmd;
  delete updateCmd;
  delete testDir;
  delete stepCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  if( command == matCmd )
   Detector->SetTargetMaterial(newValue);
  else if( command == mat1Cmd )
   Detector->SetWorldMaterial(newValue);
  else if( command == rCmd ) 
    Detector->SetTargetRadius(rCmd->GetNewDoubleValue(newValue));
  else if( command == stepCmd ) 
    Detector->SetMaxStepLength(stepCmd->GetNewDoubleValue(newValue));
  else if( command == lCmd ) 
    Detector->SetTargetLenght(rCmd->GetNewDoubleValue(newValue));
  else if( command == updateCmd )
    Detector->UpdateGeometry();
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

