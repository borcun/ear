cmake_minimum_required(VERSION 3.2)
project(face VERSION 0.0.0 DESCRIPTION "face reference library")

include_directories(core ioss psss tss pcss)
add_subdirectory(core)
add_subdirectory(ioss)
add_subdirectory(psss)
add_subdirectory(tss)
add_subdirectory(pcss)

add_library(${PROJECT_NAME} SHARED ioss/ios.cpp psss/psds.cpp psss/pscs.cpp tss/ts.cpp pcss/pcs.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
