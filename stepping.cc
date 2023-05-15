#include "stepping.hh"
#include "G4RunManager.hh"
#include "G4Neutron.hh"
#include "G4VProcess.hh"
#include "G4StepPoint.hh"
#include "G4Track.hh"

MySteppingAction::MySteppingAction(MyEventAction *eventAction)
{
	fEventAction = eventAction;
	
}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step *step)
{
	//dont follow fission tracks
	G4String Name;
	if(step->GetTrack()->GetCreatorProcess()){
		Name = step->GetTrack()->GetCreatorProcess()->GetProcessName();	
	if(Name == "nFission"){ 
        	step->GetTrack()->SetTrackStatus(fKillTrackAndSecondaries);//}        
        	}       
        }
        
        
       	//G4String Name2;
	//if(step->GetTrack()->GetCreatorProcess()){
		//Name2 = step->GetTrack()->GetCreatorProcess()->GetProcessName();	
	//if(Name == "nCapture"){ 
        	//G4cout << step->GetTrack()->GetCreatorProcess()->GetProcessName() << G4endl;
        	//G4cout << step->GetTrack()->GetParticleDefinition()->GetParticleName() << G4endl; 
        	//G4cout << step->GetTrack()->GetKineticEnergy()<< G4endl;       
        	//}       
        //}
		
	//KIKAR VILKEN VOLY VI BEFINNER OSS I
	G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();	
	const MyDetectorConstruction *detectorConstruction = static_cast<const	
	MyDetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());	
	G4LogicalVolume *fScoringVolume = detectorConstruction->GetScoringVolume();	
	if(volume != fScoringVolume)
		return;
			
	//samla ihop energideponeringarna
	G4double edep = step-> GetTotalEnergyDeposit();
	fEventAction->AddEdepp(edep);	
	G4StepPoint *postStepPoint = step->GetPostStepPoint();
	G4ThreeVector posPhoton = postStepPoint->GetPosition();
	
	//Tracklength in the water
	if(step->GetTrack()->GetParentID() == 0) {
	G4ThreeVector startPos = step->GetTrack()->GetVertexPosition();
	G4ThreeVector length = posPhoton - startPos;
	G4double X = length.mag();
	fEventAction->SetLen(X);
	}
	
	
	G4StepPoint* postPoint = step->GetPostStepPoint();
	G4String procName = postPoint->GetProcessDefinedStep()->GetProcessName();

	if (step->GetTrack()->GetParticleDefinition()->GetParticleName() == "O16")
	{G4cout << step->GetTrack()->GetCreatorProcess()->GetProcessName() << G4endl;}
	
	
	
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	if (edep != 0.0 || procName != "Envelop" ){
		man->FillNtupleDColumn(0,0,edep);
		man->FillNtupleDColumn(0,1,posPhoton[0]);
		man->FillNtupleDColumn(0,2,posPhoton[1]);
		man->FillNtupleDColumn(0,3,posPhoton[2]);
		man->AddNtupleRow(0);
	
	
	if (step->GetTrack()->GetParticleDefinition()->GetParticleName() == "proton" || step->GetTrack()->GetParticleDefinition()->GetParticleName() == "neutron")
	{
		man->FillNtupleDColumn(1,0,edep);
		man->FillNtupleDColumn(1,1,posPhoton[0]);
		man->FillNtupleDColumn(1,2,posPhoton[1]);
		man->FillNtupleDColumn(1,3,posPhoton[2]);
		man->AddNtupleRow(1);
	
	
	}
	
	if (step->GetTrack()->GetParticleDefinition()->GetParticleName() == "gamma")
	{
		man->FillNtupleDColumn(2,0,edep);
		man->FillNtupleDColumn(2,1,posPhoton[0]);
		man->FillNtupleDColumn(2,2,posPhoton[1]);
		man->FillNtupleDColumn(2,3,posPhoton[2]);
		man->AddNtupleRow(2);	
	}
	
	if (step->GetTrack()->GetParticleDefinition()->GetParticleName() == "e-")
	{
		man->FillNtupleDColumn(3,0,edep);
		man->FillNtupleDColumn(3,1,posPhoton[0]);
		man->FillNtupleDColumn(3,2,posPhoton[1]);
		man->FillNtupleDColumn(3,3,posPhoton[2]);
		man->AddNtupleRow(3);	
	}

	
	}

	
	//if (step->GetTrack()->GetParticleDefinition()->GetParticleName() == "O16")
	//{
	//G4cout << step->GetTrack()->GetParticleDefinition()->GetParticleName() << G4endl;
	//G4cout << edep << G4endl;
	//}
	
	
	

}
