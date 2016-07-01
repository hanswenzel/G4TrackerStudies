# G4TrackerStudies
Is a stand alone geant 4 application to calculate hadronic cross sections. 

Prerequisites: Geant 4 and ROOT installed and the runtime properly initialized.  
cmake 



Checking the code out from github:
git clone https://hanswenzel@github.com/hanswenzel/G4TrackerStudies.git

Build Instructions:
For an out of source build do:

mkdir G4TrackerStudies-build

cd G4TrackerStudies-build

cmake ../G4TrackerStudies/ -DCMAKE_INSTALL_PREFIX=../G4TrackerStudies-install

make install

to run cd into G4TrackerStudies-install/bin
and type 
./g4main muons.in


