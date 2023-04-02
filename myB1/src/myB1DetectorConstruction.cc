#include "myB1DetectorConstruction.hh"

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
#include "G4VSolid.hh"
#include "myB1Phantom.hh"

#include <vector>

namespace myb1
{
    MyB1DetectorConstruction::MyB1DetectorConstruction(std::string phantomName){
        phantom = new MyB1Phantom(phantomName);
    }

    G4VPhysicalVolume* MyB1DetectorConstruction::Construct(){
        G4bool checkOverlaps = true;
        // define world size
        G4double worldX = 500.0*cm;
        G4double worldY = 500.0*cm;
        G4double worldZ = 500.0*cm;

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
            false   // check overlaps
            );

        // // auto mesh = CADMesh::TessellatedMesh::FromSTL("skull_ascii.stl"); 
        // auto meshes = CADMesh::TessellatedMesh::FromOBJ("phantom_male.obj"); 
        // // meshes->SetScale(100);
        // std::vector<G4VSolid *> meshes_v = meshes->GetSolids();
        // G4cout << "XXXXXXXXXXXXXXXXX" << G4endl;
        // int i = 0;
        // for (auto v: meshes_v)
        // {
        //     G4cout << i << ", " << v->GetName() << G4endl;
        //     ++i;
        // }
        // G4cout << "XXXXXXXXXXXXXXXXX" << G4endl;
        // meshes->SetScale(10);
        // G4LogicalVolume* logSkull = new G4LogicalVolume(
        //     meshes->GetSolid(4),
        //     nist->FindOrBuildMaterial("G4_BONE_CORTICAL_ICRP"),
        //     "Skull"
        // );

        // G4VisAttributes* visAttSkull = new G4VisAttributes();
        // visAttSkull->SetColor(G4Color::Blue());
        // visAttSkull->SetVisibility(true);
        // visAttSkull->SetForceSolid(true);
        // logSkull->SetVisAttributes(visAttSkull);


        // new G4PVPlacement(nullptr, // rotation
        //     G4ThreeVector(0, 0, 0), // position
        //     logSkull,        // logical volum
        //     "Skull",        // name
        //     worldLV,        // mother volum
        //     false,          // no boolean operation
        //     0,              // copy number
        //     checkOverlaps   // check overlaps
        //     );

        // G4LogicalVolume* logBox = new G4LogicalVolume(
        //     new G4Box("Box", 0.2*worldX, 0.2*worldY, 0.2*worldZ),
        //     nist->FindOrBuildMaterial("G4_AIR"),
        //     "Box"
        // );

        // G4VisAttributes* visAttBox = new G4VisAttributes();
        // visAttBox->SetColor(G4Color::Red());
        // visAttBox->SetVisibility(true);
        // visAttBox->SetForceSolid(true);
        // logBox->SetVisAttributes(visAttBox);


        // new G4PVPlacement(nullptr, // rotation
        //     G4ThreeVector(0, 0, 0.2*worldZ), // position
        //     logBox,        // logical volum
        //     "Box",        // name
        //     worldLV,        // mother volum
        //     false,          // no boolean operation
        //     0,              // copy number
        //     checkOverlaps   // check overlaps
        //     );

        for (int i = 0; i < phantom->phantomMap.size(); i++)
        {
            new G4PVPlacement(nullptr, // rotation
                G4ThreeVector(0, 0, 0), // position
                phantom->logPhantoms[i],        // logical volum
                phantom->logPhantoms[i]->GetName(),        // name
                worldLV,        // mother volum
                false,          // no boolean operation
                0,              // copy number
                false   // check overlaps
                );       
        }

        return physWorld;
    }
} // namespace myb1
