#include "ConfigurationManager.hh"
#include "ConfigurationManagerMessenger.hh"
#include "G4SystemOfUnits.hh"
using namespace std;

ConfigurationManager* ConfigurationManager::instance = 0;

ConfigurationManager::ConfigurationManager() {
    confMessenger = new ConfigurationManagerMessenger(this);
    doAnalysis = true;
    stepLimit = false;
    limitval = 0.1 * cm;
}

ConfigurationManager* ConfigurationManager::getInstance() {
    if (instance == 0) instance = new ConfigurationManager;
    return instance;
}
