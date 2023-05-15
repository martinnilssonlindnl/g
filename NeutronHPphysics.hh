#ifndef NeutronHPphysics_HH
#define NeutronHPphysics_HH

#include "globals.hh"
#include "G4VPhysicsConstructor.hh"

class G4GenericMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class NeutronHPphysics : public G4VPhysicsConstructor
{
  public:
    NeutronHPphysics(const G4String& name="neutron");
   ~NeutronHPphysics();

  public:
    void ConstructParticle() override { };
    void ConstructProcess() override;
    
  private:
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

