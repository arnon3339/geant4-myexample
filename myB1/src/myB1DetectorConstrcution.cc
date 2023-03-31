#include "myB1DetectorConstrcution.hh"

#include "G4VisAttributes.hh"
#include "G4Color.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"
#include "G4PVParameterised.hh"
#include "G4VPhysicalVolume.hh"
#include "globals.hh"
#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4STRead.hh"
#include "CADMesh.hh"

namespace myb1
{
    G4VPhysicalVolume* MyB1DetectorConstruction::Construct(){
        G4bool checkOverlaps = true;
        // define world size
        G4double worldX = 50.0*cm;
        G4double worldY = 50.0*cm;
        G4double worldZ = 50.0*cm;

        // instantiate nist to get Nist material standard
        G4NistManager* nist = G4NistManager::Instance();

        // choose world material
        auto* worldMaterial = nist->FindOrBuildMaterial("G4_AIR");

        // define world solid
        G4Box* worldSolid = new G4Box(
            "World", // name
            0.5*worldX, 0.5*worldY, 0.5*worldZ // dimension
        );

        G4LogicalVolume* worldLV = new G4LogicalVolume(
            worldSolid, // solid 
            worldMaterial, // material
            "World" // name
        );

        auto* physWorld = new G4PVPlacement(nullptr, // rotation
            G4ThreeVector(0, 0, 0), // position
            worldLV,        // logical volum
            "World",        // name
            nullptr,        // mother volum
            false,          // no boolean operation
            0,              // copy number
            checkOverlaps   // check overlaps
            );

        auto mesh = CADMesh::TessellatedMesh::FromSTL("skull_ascii.stl"); 
        G4LogicalVolume* logSkull = new G4LogicalVolume(
            mesh->GetSolid(),
            nist->FindOrBuildMaterial("G4_BONE_CORTICAL_ICRP"),
            "Skull"
        );
        mesh->SetScale(30000.0);

        G4VisAttributes* visAtt = new G4VisAttributes();
        visAtt->SetColor(G4Color::Blue());
        visAtt->SetVisibility(true);
        visAtt->SetForceSolid(true);
        logSkull->SetVisAttributes(visAtt);
        auto* physSkull = new G4PVPlacement(nullptr, // rotation
            G4ThreeVector(0, 0, 0), // position
            logSkull,        // logical volum
            "World",        // name
            worldLV,        // mother volum
            false,          // no boolean operation
            0,              // copy number
            checkOverlaps   // check overlaps
            );

        return physWorld;
    }
} // namespace myb1
