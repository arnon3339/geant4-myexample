cmake_minimum_required(VERSION 3.16...3.21)
project(MYB1)

option(WITH_GEANT4_UIVIS "Build my example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
    find_package(Geant4 REQUIRED ui_all vis_all)
else()
    find_package(Geant4 REQUIRED)
endif()

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)


file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)


add_executable(myB1 myB1.cc ${sources} ${headers})
target_link_libraries(myB1 ${Geant4_LIBRARIES})


set(MYB1_SCRIPTS
    myB1.in
    myB1.out
    init_vis.mac
    run1.mac
    run2.mac
    vis.mac
    tsg_offscreen.mac
    skull.stl
    skull_ascii.stl
)

foreach(_script ${MYB1_SCRIPTS})
    configure_file(
        ${PROJECT_SOURCE_DIR}/${_script}
        ${PROJECT_BINARY_DIR}/${_script}
        COPYONLY
    )
endforeach()

# add_custom_target(myB1 DEPENDS myB1)

install(TARGETS myB1 DESTINATION bin)