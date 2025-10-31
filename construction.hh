#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4Box.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

//#include "detector.hh"

//DC is equal to MyDetectorConstruction

class DC : public G4VUserDetectorConstruction
{
public:
    DC();
    ~DC();

    virtual G4VPhysicalVolume *Construct();

/*private:
    G4LogicalVolume *logicDetector;
    virtual void ConstructSDandField();
*/
};

#endif
