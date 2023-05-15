#include <iostream>

//G4-headers
#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4RunManagerFactory.hh"
#include "QGSP_BIC_HP.hh"
#include "FTFP_BERT_HP.hh"
#include "G4ScoringManager.hh"

//Headers
#include "construction.hh"
#include "physics.hh"
#include "action.hh"

int main(int argc, char** argv)
{
	
	#ifdef G4MULTITHREADED
		G4RunManager *runManager = new G4MTRunManager();
	#else	
		G4RunManager *runManager = new G4RunManager();
	#endif
	
	G4ScoringManager* scoringManager = G4ScoringManager::GetScoringManager();
	
	runManager -> SetUserInitialization(new MyDetectorConstruction());
	//runManager -> SetUserInitialization(new MyPhysicsList());
	//runManager -> SetUserInitialization(new QGSP_BIC_HP());
	auto physicsList = new FTFP_BERT_HP;
	runManager -> SetUserInitialization(physicsList);
	runManager -> SetUserInitialization(new MyActionInitialization());
	
	//runManager -> Initialize();
	
	G4UIExecutive *ui = 0;	
	if(argc == 1)
	{
		ui = new G4UIExecutive(argc, argv);
	}
	//G4UIExecutive *ui = new G4UIExecutive(argc, argv);
	
	G4VisManager *visManager = new G4VisExecutive();
	visManager->Initialize();
	
	G4UImanager *UImanager = G4UImanager::GetUIpointer();
	
	if(ui)
	{	
		UImanager->ApplyCommand("/control/execute vis.mac");
		ui->SessionStart();
	}
	else
	{
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager->ApplyCommand(command+fileName);	
	}
	//UImanager->ApplyCommand("/control/execute vis.mac");
	//ui->SessionStart();

	return 0;
}
