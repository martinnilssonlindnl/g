
#include "NeutronHPphysics.hh"
#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessTable.hh"


#include "G4HadronElasticProcess.hh"
#include "G4ParticleHPElasticData.hh"
#include "G4ParticleHPThermalScatteringData.hh"
#include "G4ParticleHPElastic.hh"
#include "G4ParticleHPThermalScattering.hh"

#include "G4HadronInelasticProcess.hh"
#include "G4ParticleHPInelasticData.hh"
#include "G4ParticleHPInelastic.hh"

#include "G4NeutronCaptureProcess.hh"
#include "G4ParticleHPCaptureData.hh"
#include "G4ParticleHPCapture.hh"

#include "G4NeutronFissionProcess.hh"
#include "G4ParticleHPFissionData.hh"
#include "G4ParticleHPFission.hh"

NeutronHPphysics::NeutronHPphysics(const G4String& name)
:  G4VPhysicsConstructor(name)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NeutronHPphysics::~NeutronHPphysics()
{}
void NeutronHPphysics::ConstructProcess()
{
  	G4ParticleDefinition* neutron = G4Neutron::Neutron();
  	G4ProcessManager* pManager = neutron->GetProcessManager();
   
  // delete all neutron processes if already registered
  //
  	G4VProcess* process = 0;
 	process = pManager->GetProcess("hadElastic");
  	if (process) pManager->RemoveProcess(process);
  //
  	process = pManager->GetProcess("neutronInelastic");
 	if (process) pManager->RemoveProcess(process);
  //
  	process = pManager->GetProcess("nCapture");      
  	if (process) pManager->RemoveProcess(process);
  	
	process = pManager->GetProcess("nFission");      
	if (process) pManager->RemoveProcess(process);
	
		
  	
  	
  
  	G4HadronElasticProcess* process1 = new G4HadronElasticProcess();
  	pManager->AddDiscreteProcess(process1);
   	G4ParticleHPElastic*  model1a = new G4ParticleHPElastic();
  	process1->RegisterMe(model1a);
   	process1->AddDataSet(new G4ParticleHPElasticData());
  
   	G4HadronInelasticProcess* process2 =
    	new G4HadronInelasticProcess( "neutronInelastic", G4Neutron::Definition() );
  	pManager->AddDiscreteProcess(process2);  
    	G4ParticleHPInelastic* model2 = new G4ParticleHPInelastic();
  	process2->RegisterMe(model2); 
    	G4ParticleHPInelasticData* dataSet2 = new G4ParticleHPInelasticData();
  	process2->AddDataSet(dataSet2);
  
    	G4NeutronCaptureProcess* process3 = new G4NeutronCaptureProcess();
 	pManager->AddDiscreteProcess(process3);
     	G4ParticleHPCapture* model3 = new G4ParticleHPCapture();
  	process3->RegisterMe(model3);
    	G4ParticleHPCaptureData* dataSet3 = new G4ParticleHPCaptureData();
  	process3->AddDataSet(dataSet3);
  	
  	G4NeutronFissionProcess* process4 = new G4NeutronFissionProcess();
	pManager->AddDiscreteProcess(process4);
	G4ParticleHPFissionData* dataSet4 = new G4ParticleHPFissionData();
	process4->AddDataSet(dataSet4);                               
	G4ParticleHPFission* model4 = new G4ParticleHPFission();
	process4->RegisterMe(model4);
  	  	
  }
