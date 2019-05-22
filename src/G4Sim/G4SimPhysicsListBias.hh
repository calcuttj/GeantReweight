#ifndef G4SimPhysicsListBias_h
#define G4SimPhysicsListBias_h 1

#include "G4VUserPhysicsList.hh"
#include "G4VModularPhysicsList.hh"

#include "G4ReweightHist.hh"

class G4SimPhysicsListBias : public G4VModularPhysicsList
{

  public:
    G4SimPhysicsListBias(double inelasticBias, double elasticBias);
    virtual ~G4SimPhysicsListBias();

  protected:
    virtual void SetCuts(); 
 
};
#endif
