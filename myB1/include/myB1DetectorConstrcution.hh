#include "G4VUserDetectorConstruction.hh"

#ifndef MYB1DETECTORCONSTRUCTION_HH
#define MYB1DETECTORCONSTRUCTION_HH 1

class G4VPhysicalVolume;

namespace myb1
{
    class MyB1DetectorConstruction:public G4VUserDetectorConstruction{
        public:
            MyB1DetectorConstruction() = default;
            ~MyB1DetectorConstruction() override = default;
        
            G4VPhysicalVolume* Construct() override;
    };
    
} // namespace myb1

#endif
