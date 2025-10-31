#include "construction.hh"
//#include "G4VPhysicalVolume.hh"
//#include "G4VUserDetectorConstruction.hh"

DC::DC()
{}

DC::~DC()
{}

G4VPhysicalVolume *DC::Construct()
{
    G4NistManager *nist = G4NistManager::Instance();

    G4Material *SiO2 = new G4Material("SiO2", 2.201*g/cm3, 2); // mat.name, its density, how many components?
    SiO2->AddElement(nist->FindOrBuildElement("Si"), 1); // 1 part of Si
    SiO2->AddElement(nist->FindOrBuildElement("O"), 2); // 2 parts of oxide

//FindOrBuildElement?
// not FindOrBuilMaterial?


    G4Material *H20 = new G4Material("H20", 1.000*g/cm3, 2); // mat.name, its density, how many components?
    H20->AddElement(nist->FindOrBuildElement("H"), 2); // 1 part of helious
    H20->AddElement(nist->FindOrBuildElement("O"), 1); // 2 parts of oxide

    //G4Element *C = nist->FindOrBuildMaterial("C"); // if so, we cannot convert G4Material* to G4Element
    G4Element *C = nist->FindOrBuildElement("C");  
    G4Material *Aerogel = new G4Material ("Aerogel", 0.200*g/cm3, 3); //3 parts??
    Aerogel->AddMaterial(SiO2, 62.5*perCent);
    Aerogel->AddMaterial(H20, 37.4*perCent);
    Aerogel->AddElement(C, 0.1*perCent);

// works fun; there are no refractive index, so G4 doesnt know how to change the photons' momemtum
// now we are going to define it

    G4double energy[2] = {1.3*eV, 1.4*eV};
    G4double rindexAerogel[2] = {1.4, 1.1};

    G4double rindexWorld[2] = {1.0, 1.0};
    //G4double rindexAerogel[2] = {1.2, 1.1};
    
    G4MaterialPropertiesTable *mpAerogel = new G4MaterialPropertiesTable();
    mpAerogel->AddProperty("RINDEX", energy, rindexAerogel, 2);
// last string gives us the converse between energy and refr.index in our material --> we define refr.index
// linear inter- and extrapolation, i suppose, because of 2 elements in rows
//     

    Aerogel->SetMaterialPropertiesTable(mpAerogel);




    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

    G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
    mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);

    worldMat->SetMaterialPropertiesTable(mptWorld);
// if we wanna see trajectories(the physics) outside the box/tube/etc, we should set MPT(MaterialPropertiesTable) to this volume(to this material properties, that are contained by this volume)



    G4Box *solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 0.5*m); // указываем половинный объем по x,y,z
// так как джант строит по половине в положительном направлении, половину в отрицательном направлении
// если оставить без указания размерности, то отрисует в миллиметрах
    
    
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld"); 
//ссылка на объвление объема, на материал этого объема, а после-название
    

    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);
// это уже физический объем


//optical params; create radiator
// 


    G4Box *solidRadiator = new G4Box("solidRadiator", 0.4*m, 0.4*m, 0.01*m);

    G4LogicalVolume *logicRadiator = new G4LogicalVolume(solidRadiator, Aerogel, "logicRadiator");

    G4VPhysicalVolume *physRadiator = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.25*m), logicRadiator, "physRadiator", logicWorld, false, 0, true);


// define the sensentive detector(SD)
/*
    G4Box *solidDetector = new G4Box("solidDetector", 0.005*m, 0.005*m, 0.01*m);
//logicVolume for SD
    logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicalDetector");
// now we should create the instane of our sensentive detector
// but its more tricky that was earlier, because we need a array of SD(??)


//    for (G4int i=0; i<100; i++)
//    {
//        for (G4int j=0; j<100; j++)
//        {
//
//            G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector(-0.5*m+(i+0.5)*m/100, -0.5*m+(j+0.5)*m/100, 0.49*m), logicDetector, "physDetector", logicWorld, false, j+i*100, true);
//        }
//
//    }
*/

//    G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector(0.49*m, 0.49*m, 0.49*m), logicDetector, "physDetector", logicWorld, false, 0, true);
    




    return physWorld;

}

/*
void DC::ConstructSDandField()
{
    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

    logicDetector->SetSensitiveDetector(sensDet);
}
*/


