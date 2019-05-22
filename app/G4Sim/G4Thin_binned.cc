#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "ThinDetector.hh"
#include "G4SimPhysicsListBinned.hh"
#include "G4SimActionInitialization.hh"

#include "G4ReweightHist.hh"

#include <utility>
#include <iostream>
#include <fstream>

#include "TH1F.h"
#include "TFile.h"

#include "fhiclcpp/make_ParameterSet.h"
#include "fhiclcpp/ParameterSet.h"

char * n;

std::string macFileName = "../G4Sim/run1.mac";
std::string outFileName = "try.root";
std::string material_fcl_file = "empty";
std::string var_fcl_file = "empty";

bool ParseArgs(int argc, char* argv[]);

int main(int argc, char * argv[]){

  std::cout << "parsing" << std::endl;
  if(!ParseArgs(argc, argv)) {return 0;}
  std::cout << macFileName << " " << outFileName << " " << std::endl;

  G4RunManager * runManager = new G4RunManager;
  
  //Define and create detector volume  
  if( material_fcl_file != "empty" ){
    fhicl::ParameterSet pset = fhicl::make_ParameterSet( material_fcl_file ); 
    fhicl::ParameterSet theMaterial = pset.get< fhicl::ParameterSet >("Material"); 
    runManager->SetUserInitialization(new ThinDetector(theMaterial) );
  }
  else{
    runManager->SetUserInitialization(new ThinDetector);
  }

  if( var_fcl_file == "empty" ){
    std::cout << "Error. Need a valid fcl file for variations" << std::endl;
    return 0;
  }
  fhicl::ParameterSet pset = fhicl::make_ParameterSet( var_fcl_file ); 
  fhicl::ParameterSet inel_bias_par = pset.get< fhicl::ParameterSet >("Inelastic"); 
  std::vector< double > inel_bins = inel_bias_par.get< std::vector< double > >("Bins");
  std::vector< double > inel_vals = inel_bias_par.get< std::vector< double > >("Vals");

  G4ReweightHist inelasticBias("inel","inel",inel_bins);

  for( size_t ib = 0; ib < inel_vals.size(); ++ib ){
    inelasticBias.SetBinContent( ib, inel_vals[ib] );
    std::cout << " " << inelasticBias.GetBinContent(ib) << std::endl;
    std::cout << " " << inelasticBias.GetBinLowEdge(ib) << std::endl;
  }

  fhicl::ParameterSet el_bias_par = pset.get< fhicl::ParameterSet >("Elastic"); 
  std::vector< double > el_bins = el_bias_par.get< std::vector< double > >("Bins");
  std::vector< double > el_vals = el_bias_par.get< std::vector< double > >("Vals");

  G4ReweightHist elasticBias("el","el",el_bins);
  for( size_t ib = 0; ib < el_vals.size(); ++ib ){
    elasticBias.SetBinContent( ib, el_vals[ib] );
  }
  runManager->SetUserInitialization(new G4SimPhysicsListBinned( &inelasticBias, &elasticBias ) );

  //Define the actions taken during various stages of the run
  //i.e. generating particles
  runManager->SetUserInitialization(new G4SimActionInitialization(outFileName));

  G4cout << "Init"<<G4endl;
  runManager->Initialize();
  G4cout << "Done"<< G4endl;


  //read a macro file of commands
  G4UImanager * UI = G4UImanager::GetUIpointer();
  G4String command = "/control/execute ";
  G4String fileName = macFileName;
  G4cout <<"Applying Command" <<G4endl;
  UI->ApplyCommand(command+fileName);
  G4cout <<"Done"<<G4endl;

  delete runManager;
  return 0;
}

bool ParseArgs(int argc, char* argv[]){

  for(int i = 1; i < argc; ++i){
    if( strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0 ){
      std::cout << "Usage: -c macro file -o outfile" << std::endl;
      return false;
    }
    if( strcmp(argv[i], "-c") == 0){
      macFileName = argv[i+1];      
    }
    else if( strcmp(argv[i], "-o") == 0){
      outFileName = argv[i+1];
    }
    else if( strcmp(argv[i], "-m") == 0){
      material_fcl_file = argv[i+1];
    }
    else if( strcmp(argv[i], "-v") == 0){
      var_fcl_file = argv[i+1];
    }

  }
  return true;
}

