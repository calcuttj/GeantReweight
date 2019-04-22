Note: This branch is to store the edits that were made to geant4 (within source) to introduce variations to geant4 and implement them in G4Sim/



# GeantReweight
Repository for implementing reweighting in Geant4

# Building
cmake -DCMAKE_INSTALL_PREFIX=/path/to/GeantReweight-install/ -DUSE_FHICL=1 -DGeant4_DIR=/path/to/geant4-install/lib64/Geant4-<version>/ relative/path/to/GeantReweight/
