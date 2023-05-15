#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Material.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"





class MyDetectorConstruction : public G4VUserDetectorConstruction

{
public:
	MyDetectorConstruction();
	~MyDetectorConstruction();
	
	G4LogicalVolume *GetScoringVolume() const {return fScoringVolume;}
	
	virtual G4VPhysicalVolume *Construct();
	
	G4double fuelRadius;
	
private:
	G4Box *solidWorld;
	G4Tubs *cladding, *cool, *fuel, *w_cladding, *w_cool;
	G4LogicalVolume *logicWorld, *logicalCladding, *logicalCool, *logicalFuel, *w_logicalCladding, *w_logicalCool;
	G4VPhysicalVolume *physWorld, *physicalCool, *physicalFuel, *physicalCladding;
	G4Material *zircAlloy2, *UO2, *water, *helium, *w_water;
	G4Isotope *iU235, *iU238;
	G4Element *hydrogen, *oxygen, *chromium, *iron, *nickel, *zirconium, *antimony, *U235, *U238;

	void DefineMaterials();
	void ConstructRod();
	
	G4LogicalVolume *fScoringVolume;
	
};

#endif

