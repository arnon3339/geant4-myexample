#include "myB1Phantom.hh"

#include <array>
#include <boost/algorithm/string.hpp>
#include <iostream>

#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "CADMesh.hh"


namespace myb1
{
  MyB1Phantom::~MyB1Phantom(){
    delete logPhantoms[0];
    delete[] logPhantoms;
    delete[] isInUses;
    
  }


  MyB1Phantom::MyB1Phantom(std::string phantom){

    G4VisAttributes* visAtt = new G4VisAttributes();
    G4NistManager* nist = G4NistManager::Instance();

    auto meshes = std::shared_ptr<CADMesh::TessellatedMesh>();
    if (!std::string("male").compare(boost::algorithm::to_lower_copy(phantom)))
      meshes = CADMesh::TessellatedMesh::FromOBJ("./phantoms/phantom_male.obj");
    else if (!std::string("female").compare(boost::algorithm::to_lower_copy(phantom)))
      meshes = CADMesh::TessellatedMesh::FromOBJ("./phantoms/phantom_female.obj");
    else
      meshes = CADMesh::TessellatedMesh::FromOBJ(std::string("./phantoms/").append(phantom));
    meshes->SetScale(10);
    auto meshes_v = meshes->GetSolids();
    logPhantoms = new G4LogicalVolume*[meshes_v.size()];
    isInUses = new bool[meshes_v.size()];
    int meshIndex = 0;
    for (auto mesh: meshes_v)
    {
      phantomMap[std::string(mesh->GetName())] = meshIndex;
      logPhantoms[meshIndex] = new G4LogicalVolume(
        meshes->GetSolid(meshIndex),
        nist->FindOrBuildMaterial("G4_AIR"),
        mesh->GetName()
      );
      visAtt->SetColor(G4Color::Blue());
      visAtt->SetVisibility(true);
      visAtt->SetForceSolid(true);
      logPhantoms[meshIndex]->SetVisAttributes(visAtt);
      ++meshIndex;
    }
  }
} // namespace myb1
