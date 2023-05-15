#include "construction.hh"

////CLASS WITH DEFINED variable
MyDetectorConstruction::MyDetectorConstruction()
{
DefineMaterials();
}

MyDetectorConstruction::~MyDetectorConstruction()
{}
//Materials list
void MyDetectorConstruction::DefineMaterials()
{
	G4NistManager *nist = G4NistManager::Instance();
	
	//Detector material
	hydrogen = nist->FindOrBuildElement("H");
	oxygen = nist->FindOrBuildElement("O");	
	water = new G4Material("water", 0.76 * (g / cm3),2);
	water->AddElement(oxygen, 0.8889);
	water->AddElement(hydrogen, 0.1111);
	w_water = nist->FindOrBuildMaterial("G4_WATER");  
	
	
	
	//Contruct the fissile Uranium UO2
	G4double U235Enrichment = 0.024;
	G4double U238Enrichment = 0.976;
	iU235 = new G4Isotope("iU235", 92, 235, 235.053930 * (g / mole));
	iU238 = new G4Isotope("iU238", 92, 238, 238.050788 * (g / mole));
	U235 = new G4Element("U235", "U235", 1);
	U238 = new G4Element("U238", "U238", 1);
	U235->AddIsotope(iU235, 1.0);
	U238->AddIsotope(iU238, 1.0);
	oxygen = nist->FindOrBuildElement("O");
	G4double UO2MolecularWeight = U235->GetA() * U235Enrichment
                                        + U238->GetA() * U238Enrichment
                                        + oxygen->GetA() * 2;
        G4double U235MassFraction = (U235->GetA() * U235Enrichment)
                                      / UO2MolecularWeight;
        G4double U238MassFraction = (U238->GetA() * U238Enrichment)
                                      / UO2MolecularWeight;
        G4double oxygenMassFraction = (oxygen->GetA() * 2)
                                        / UO2MolecularWeight;
        UO2 = new G4Material("UO2", 10.55 * (g / cm3), 3);
	UO2->AddElement(U235, U235MassFraction);
	UO2->AddElement(U238, U238MassFraction);
	UO2->AddElement(oxygen, oxygenMassFraction);
	
	
	//Construct Zircoalloy2
	//oxygen = nist->FindOrBuildElement("O");
	chromium = nist->FindOrBuildElement("Cr");
	iron = nist->FindOrBuildElement("Fe");
	nickel = nist->FindOrBuildElement("Ni");
	zirconium = nist->FindOrBuildElement("Zr");
	antimony = nist->FindOrBuildElement("Sn");
	
	zircAlloy2 = new G4Material("zircAlloy2", 6.56 *(g / cm3), 6);
	zircAlloy2->AddElement(oxygen, 0.001197);
	zircAlloy2->AddElement(chromium, 0.000997);
	zircAlloy2->AddElement(iron, 0.000997);
	zircAlloy2->AddElement(nickel, 0.000499);
	zircAlloy2->AddElement(zirconium, 0.982348);
	zircAlloy2->AddElement(antimony, 0.013962);
	
	//Gap material 
	helium = nist->FindOrBuildMaterial("G4_He");
		
}


//Construct world. 
G4VPhysicalVolume *MyDetectorConstruction::Construct()
{

    G4ThreeVector position;
#ifdef NDEBUG
    G4bool const overlapChecking = false;
#else
    G4bool const overlapChecking = true;
#endif // NDEBUG

	G4double xWorld = 15.0*cm;
	G4double yWorld = 15.0*cm;
	G4double zWorld = 15.0*cm;
		
	solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);
	
	logicWorld = new G4LogicalVolume(solidWorld, water, "logicWorld");
	
	physWorld = new G4PVPlacement(NULL, G4ThreeVector(0.0,0.0,0.0), logicWorld, "physWorld", NULL, false, 0, overlapChecking);
	
	
	//////////RODS
	G4double innerRadius = 0.0*mm;
	G4double outerRadius = 5.5*mm;
	G4double coolerRadius = 4.835*mm;
	G4double fuelRadius = 4.75*mm;
	G4double hz = 15.*cm;
	
	//Cladding volume
	cladding = new G4Tubs("cladding", innerRadius, outerRadius, hz, 0.0 *deg, 360.0* deg);
	logicalCladding = new G4LogicalVolume(cladding, zircAlloy2, "logicalCladding");
	
	//Place cooling layer of helium inside 
	cool = new G4Tubs("cool", innerRadius, coolerRadius, hz, 0.0 *deg, 360.0* deg);
	logicalCool = new G4LogicalVolume(cool, helium, "logicalCool");
	new G4PVPlacement(NULL, G4ThreeVector(0.0,0.0,0.0), logicalCool, "logicalCool", logicalCladding, false, overlapChecking);
	
	//FUEL
	fuel = new G4Tubs("fuel", innerRadius, fuelRadius, hz, 0.0 *deg, 360.0* deg);
	logicalFuel = new G4LogicalVolume(fuel, UO2, "logicalFuel");
	new G4PVPlacement(NULL, G4ThreeVector(0.0,0.0,0.0), logicalFuel, "logicalFuel", logicalCool, false,overlapChecking);
	
	//place The full rod in the water;
	//new G4PVPlacement(NULL, G4ThreeVector(0.0,0.0,0.0), logicalCladding, "logicalCladding", logicWorld, false, overlapChecking);
	

	//VI VILL KOLLA ENDAST PÅ TRÄFFAR I VATTNET
	
	//G4double Spacing = 14.37*mm;
	G4double Spacing = 13*mm;
	
	G4int M = 9; //assembly size e.g. MxM
	
	
	
	if ( M % 2 != 0)
	
	{
		G4int N = (M-1)/2;
		for(double x = 0.0; x<= N*Spacing; x+=Spacing)	
		{
			for(double y = 0.0; y<= N*Spacing; y+=Spacing)
			{
				new G4PVPlacement(NULL, G4ThreeVector(x,y,0.0), logicalCladding, "logicalCladding", logicWorld, false, overlapChecking);
				
				new G4PVPlacement(NULL, G4ThreeVector(x,-y,0.0), logicalCladding, "logicalCladding", logicWorld, false, overlapChecking);
				//PlaceFuelRod(x,y, logicalCladding, logicalWorld);
				//PlaceFuelRod(x,-y,logicalCladding, logicalWorld);
		
				if(x > 0.0)
				{

					new G4PVPlacement(NULL, G4ThreeVector(-x,y,0.0), logicalCladding, "logicalCladding", logicWorld, false, overlapChecking);
					new G4PVPlacement(NULL, G4ThreeVector(-x,-y,0.0), logicalCladding, "logicalCladding", logicWorld, false, overlapChecking);
					//PlaceFuelRod(-x,y, logicalCladding, logicalWorld);
					//PlaceFuelRod(-x,-y,logicalCladding, logicalWorld);
		
				}
		
			}	
		}
	}
	else
	{	
	
		G4int N = M/2;
		for(double x = Spacing/2; x <= (N-1)*Spacing + 0.5*Spacing; x += Spacing)
		{
			for(double y = Spacing/2; y <= (N-1)*Spacing + 0.5*Spacing; y += Spacing)
			{
				//PlaceFuelRod(x,y, logicalCladding, logicalWorld);
				//PlaceFuelRod(x,-y,logicalCladding, logicalWorld);
				
				//PlaceFuelRod(-x,y, logicalCladding, logicalWorld);
				//PlaceFuelRod(-x,-y,logicalCladding, logicalWorld);
				new G4PVPlacement(NULL, G4ThreeVector(x,y,0.0), logicalCladding, "logicalCladding", logicWorld, false, overlapChecking);
				new G4PVPlacement(NULL, G4ThreeVector(x,-y,0.0), logicalCladding, "logicalCladding", logicWorld, false, overlapChecking);
				new G4PVPlacement(NULL, G4ThreeVector(-x,y,0.0), logicalCladding, "logicalCladding", logicWorld, false, overlapChecking);
				new G4PVPlacement(NULL, G4ThreeVector(-x,-y,0.0), logicalCladding, "logicalCladding", logicWorld, false, overlapChecking);				
			}
		
		}
	
	}
	

		
	
	
	
	
	fScoringVolume = logicWorld;
	
	//ConstructRod();
	return physWorld;
}

//Construct one fuel rod in the center 

//void MyDetectorConstruction::ConstructRod(){}




