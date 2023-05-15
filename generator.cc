#include "generator.hh"
#include "G4Electron.hh"
#include "G4Gamma.hh"

MyPrimaryGenerator::MyPrimaryGenerator(): G4VUserPrimaryGeneratorAction(),
   fParticleGun(0)
{
	//fParticleGun = new G4ParticleGun(1);	
	fParticleGun = new G4GeneralParticleSource();	
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fParticleGun;

}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent) 
{
	//G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	//G4String particleName="proton";
	//G4ParticleDefinition *particle = particleTable ->FindParticle("proton");
	
	
	//PLACE SOURCE RANDOMLY ON A PLANE (z= 0) IN THE FUEL ROD 
	//G4double radius = 4.75*cm;
	//G4double rPoint = radius*G4UniformRand();
	//G4double angPoint = 360.*G4UniformRand();
	//G4double x0 = rPoint*std::cos(angPoint);
	//G4double y0 = rPoint*std::sin(angPoint);
	//G4ThreeVector pos(x0, y0, 0.);
	
	
	//ISOTROPIC
	//G4double pi  = 3.14159265358979323846;
	//G4double cosTheta = 2*G4UniformRand() - 1.;
	//G4double phi = 2*pi*G4UniformRand();
  	//G4double sinTheta = std::sqrt(1. - cosTheta*cosTheta);
  	//G4double ux = sinTheta*std::cos(phi);
        //G4double uy = sinTheta*std::sin(phi);
        //G4double uz = cosTheta;
	//G4ThreeVector mom(ux, uy, uz);
	
	//fParticleGun->SetParticlePosition(pos);
	//fParticleGun->SetParticleMomentumDirection(mom);


	//G4AnalysisManager *man = G4AnalysisManager::Instance();
	//man->OpenFile("gammar.root");
	//double e = man->OpenFile("gammar.root")->GetRandom();
	
	
	
	//G4double kineticEnergy = 10.0*MeV;  
	//fParticleGun->SetParticleEnergy(kineticEnergy);
	//fParticleGun->SetParticleDefinition(G4Gamma::GammaDefinition());
	
	
	
	//fParticleGun->SetParticleMomentum(1.*GeV);
	//fParticleGun->SetParticleDefinition(particle);
	
	//fParticleGun->SetParticleEnergy
	//fParticleGun->SetParticleDefinition(G4Electron::ElectronDefinition());	

	//G4ParticleDefinition *particle = fParticleGun->GetParticleDefinition();
	
	fParticleGun -> GeneratePrimaryVertex(anEvent);
}
