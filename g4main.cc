// Geant 4 headers:
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "Randomize.hh"
#include "G4PhysListFactory.hh"
#include "G4OpticalPhysics.hh"
#include "G4VModularPhysicsList.hh"
#include "G4StepLimiter.hh"
#include "G4StepLimiterPhysics.hh"
#include "G4VPhysicsConstructor.hh"
#include "G4UserSpecialCuts.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
// project headers
#include "ConfigurationManager.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc, char** argv) {

    // Detect interactive mode (if no arguments) and define UI session
    //
    G4UIExecutive* ui = 0;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }


    //choose the Random engine
    G4Random::HepRandom::setTheEngine(new CLHEP::RanecuEngine());
    // Construct the default run manager
    //
#ifdef G4MULTITHREADED
    G4MTRunManager* runManager = new G4MTRunManager;
#else
    G4RunManager* runManager = new G4RunManager;
#endif


    G4PhysListFactory factory;
    G4VModularPhysicsList* phys = NULL;
    G4String physName = "";
    //-----------------------------------------------------
    // Physics List name defined via environmental variable
    // The following 19 physics lists are available:
    //  CHIPS
    //  FTFP_BERT
    //  FTFP_BERT_TRV
    //  FTFP_BERT_HP
    //  FTF_BIC 
    //  LBE
    //  LHEP
    //  QBBC
    //  QGSC_BERT
    //  QGSP
    //  QGSP_BERT
    //  QGSP_BERT_CHIPS
    //  QGSP_BERT_HP
    //  QGSP_BIC
    //  QGSP_BIC_HP
    //  QGSP_FTFP_BERT
    //  QGS_BIC
    //  QGSP_INCLXX
    //  Shielding
    //-----------------------------------------------------
    char* path = getenv("PHYSLIST");
    if (path) {
        physName = G4String(path);
    } else {
        physName = "FTFP_BERT"; // default
    }
    // reference PhysicsList via its name
    if (factory.IsReferencePhysList(physName)) {
        phys = factory.GetReferencePhysList(physName);
    } else {
        phys = factory.GetReferencePhysList("FTFP_BERT");
    }
    //set mandatory initialization classes
    runManager->SetUserInitialization(new DetectorConstruction());
    //StepLimiter? 
    if (ConfigurationManager::getInstance()->GetstepLimit()) {
        phys->RegisterPhysics(new G4StepLimiterPhysics());
    }
    runManager->SetUserInitialization(phys);

    //set user action classes
    runManager->SetUserAction(new PrimaryGeneratorAction());
    runManager->SetUserAction(new RunAction());
    runManager->SetUserAction(new EventAction());
    // Initialize visualization
    //
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();
    //get the pointer to the User Interface manager
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    //
    // Process macro or start UI session
    //
    if (!ui) {
        // batch mode
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    } else {
        // interactive mode
        UImanager->ApplyCommand("/control/execute init_vis.mac");
        ui->SessionStart();
        delete ui;
    }

    // Job termination
    // Free the store: user actions, physics_list and detector_description are
    // owned and deleted by the run manager, so they should not be deleted 
    // in the main() program !

    delete visManager;
    delete runManager;

    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
