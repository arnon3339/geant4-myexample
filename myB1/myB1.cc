#include <string>
#include <iostream>
#include "argparse.hpp"

#include "myB1DetectorConstruction.hh"

#include "G4UIExecutive.hh"
#include "G4SteppingVerbose.hh"
#include "G4RunManagerFactory.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UImanager.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VModularPhysicsList.hh"
#include "QBBC.hh"

using namespace myb1;
int main(int argc, char** argv){
    argparse::ArgumentParser program("program_name");
    std::string phantom("");

    program.add_argument("-P", "--phantom")
        .default_value(std::string("sample.obj"));

    try {
        program.parse_args(argc, argv);
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
    phantom = program.get<std::string>("--phantom");

    // std::cout << "XXX " << phantom << " YYY" << std::endl;

    G4VUserDetectorConstruction* detector =
     new MyB1DetectorConstruction(phantom);

    // check if ui is exist, if not instantiate ui with argc, and argv
    G4UIExecutive* ui = nullptr;
    // if (argc == 1) ui = new G4UIExecutive(argc, argv);
    ui = new G4UIExecutive(argc, argv);

    // use G4SteppingVerboseWithUnits
    G4int precision = 4;
    G4SteppingVerbose::UseBestUnit(precision);

    // construct the default run manager
    auto* runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

    // set mandatory initialized classes
    //
    // Detector construction
    runManager->SetUserInitialization(detector);

    // Physics list
    G4VModularPhysicsList *physicsList = new QBBC;
    physicsList->SetVerboseLevel(1);
    runManager->SetUserInitialization(physicsList);
    // initial vaisualization
    G4VisManager* vis = new G4VisExecutive();
    vis->Initialize();

    // get pointer to the user interface manager
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    UImanager->ApplyCommand("/control/execute init_vis.mac");

    // Run the user interface session
    ui->SessionStart();

    delete vis;
    delete runManager;
    delete ui;
    // delete UImanager;

    return 0;
}