#include "run.hh"	


MyRunAction::MyRunAction()
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	

	man->CreateNtuple("Scoring", "Scoring");
	man->CreateNtupleDColumn("fEdep");
	man->CreateNtupleDColumn("fX");
	man->CreateNtupleDColumn("fY");
	man->CreateNtupleDColumn("fZ");
	man->FinishNtuple(0);
	
	man->CreateNtuple("n_pro_ne", "n_pro_ne");
	man->CreateNtupleDColumn("fEdep");
	man->CreateNtupleDColumn("fX");
	man->CreateNtupleDColumn("fY");
	man->CreateNtupleDColumn("fZ");
	man->FinishNtuple(1);
	
	man->CreateNtuple("n_gam", "n_gam");
	man->CreateNtupleDColumn("fEdep");
	man->CreateNtupleDColumn("fX");
	man->CreateNtupleDColumn("fY");
	man->CreateNtupleDColumn("fZ");
	man->FinishNtuple(2);
		
	man->CreateNtuple("n_el", "n_el");
	man->CreateNtupleDColumn("fEdep");
	man->CreateNtupleDColumn("fX");
	man->CreateNtupleDColumn("fY");
	man->CreateNtupleDColumn("fZ");
	man->FinishNtuple(3);
	

	
	
	man->CreateNtuple("Total_energy", "Total_energy");
	man->CreateNtupleDColumn("fE");
	man->FinishNtuple(4);
	
	man->CreateNtuple("Length", "Length");
	man->CreateNtupleDColumn("len");
	man->FinishNtuple(5);
	
	
	
	

	
}
MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
	
	G4AnalysisManager *man = G4AnalysisManager::Instance();	
	
	G4int runID = run->GetRunID();
	man->SetNtupleMerging(true);
	
	std::stringstream strRunID;
	strRunID << runID;
	//man->OpenFile("et5" + strRunID.str() + ".root");
	man->OpenFile("test4.root");
}
void MyRunAction::EndOfRunAction(const G4Run*)
{

	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	//SKRIV UT FILEN 
	man->Write();
	man->CloseFile();

}
