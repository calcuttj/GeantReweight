#include "G4SimPhysicsListBinned.hh"

#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4HadronPhysicsQGSP_BERT.hh"
#include "G4HadronPhysicsFTFP_BERT_binned.hh"
#include "G4HadronPhysicsFTFP_BERT.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronElasticPhysics_binned.hh"


G4SimPhysicsListBinned::G4SimPhysicsListBinned(G4ReweightHist * inelasticBias, G4ReweightHist * elasticBias) : G4VModularPhysicsList(){
  SetVerboseLevel(5);

  RegisterPhysics( new G4DecayPhysics );
  RegisterPhysics( new G4RadioactiveDecayPhysics );
  RegisterPhysics( new G4EmStandardPhysics );
  RegisterPhysics( new G4HadronPhysicsFTFP_BERT_binned(1,inelasticBias) );
  RegisterPhysics( new G4HadronElasticPhysics_binned(1,elasticBias) );
  G4cout << "Finished Physics" << G4endl;
}

G4SimPhysicsListBinned::~G4SimPhysicsListBinned(){}

void G4SimPhysicsListBinned::SetCuts(){
  G4cout << "Set Cuts" << G4endl; 
//  G4VUserPhysicsList::SetCuts();
}

