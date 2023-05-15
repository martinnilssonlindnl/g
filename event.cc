#include "event.hh"

MyEventAction::MyEventAction(MyRunAction*)
{
	fEdep = 0.0;
	//fTrackL = 0.0;
}

MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event*)
{
	fEdep = 0.0;
	fE = 0.0;
	len = 0.0;
}

void MyEventAction::EndOfEventAction(const G4Event*)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	
	if (fE != 0.0){
	man->FillNtupleDColumn(4,0,fE);
	man->AddNtupleRow(4);
	}
	
	if (len != 0.0){
	man->FillNtupleDColumn(5,0,len);
	man->AddNtupleRow(5);
	}


}
